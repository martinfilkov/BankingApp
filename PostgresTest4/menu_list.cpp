#include <string>
#include <iostream>
#include <pqxx/pqxx> 

#include "login_register.h"
#include "bank_functions.h"

void login_register_menu(pqxx::connection& c, bool &isLogged, std::string &email)
{
    int ch = INT_MIN;
    do
    {
        system("cls");
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Welcome to the Banking app" << std::endl;
        std::cout << "Select Action:" << std::endl;
        std::cout << std::endl;
        std::cout << "1.Login" << std::endl;
        std::cout << "2.Register" << std::endl;
        std::cout << std::endl;
        std::cout << "0.Exit" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << ">";
        std::cin >> ch;
        switch (ch)
        {
        case 1: isLogged = account_login_db(c, email);
            break;
        case 2: account_register_db(c);
            break;
        case 0:
            std::cout << "Exiting application..." << std::endl;
            exit(0);
            break;
        default:
            std::cout << "Invalid Input!" << std::endl;
            system("pause");
            break;
        }
        if (isLogged) break;
    } while (ch != 0);
}

void logged_menu(pqxx::connection& c, bool &isLogged, std::string &email)
{
    if (isLogged)
    {
        int ch = INT_MIN;
        do
        {
            system("cls");
            std::cout << "-----------------------------" << std::endl;
            std::cout << "Welcome to " << c.dbname() << std::endl;
            std::cout << "Select Action:" << std::endl;
            std::cout << std::endl << "1.Look account summary" << std::endl;
            std::cout << "2.Deposit to your account" << std::endl;
            std::cout << "3.Send funds to another account" << std::endl;
            std::cout << std::endl;
            std::cout << "0.Log out" << std::endl;
            std::cout << "-----------------------------" << std::endl;
            std::cout << ">";
            std::cin >> ch;
            switch (ch)
            {
            case 1:
                system("cls");
                account_summary(c, email);
                break;
            case 2:
                system("cls");
                std::cout << deposit_funds(c, email) << std::endl;
                system("pause");
                break;
            case 3:
                system("cls");
                std::cout << send_funds(c, email) << std::endl;
                system("pause");
                break;
            case 0:
                isLogged = false;
                email = "";
                break;
            default:
                std::cout << "Invalid option, please try again!" << std::endl;
                break;
            }
        } while (ch != 0 && isLogged);
    }
}
