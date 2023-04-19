#pragma once

#include <string>
#include <iostream>
#include <pqxx/pqxx> 
#include <conio.h>
#include <ctime>
#include <random>

#include "login_register.h"
#include "menu_list.h"


void select_all_users(pqxx::connection& c)
{
    pqxx::nontransaction query(c);

    pqxx::result r = query.exec("SELECT * FROM user_data");

    for (pqxx::result::const_iterator row = r.begin(); row != r.end(); ++row) {
        std::cout << "First Name: " << row[1].as<std::string>() << std::endl;
        std::cout << "Last Name: " << row[2].as<std::string>() << std::endl;
        std::cout << "Email: " << row[3].as<std::string>() << std::endl;
        std::cout << "Account Number: " << row[5].as<std::string>() << std::endl;
        std::cout << "Account Balance: " << row[6].as<double>() << std::endl;
        std::cout << std::endl;
    }
    system("pause");
}


int main()
{
    try {
        pqxx::connection c("dbname=BankingDB user=postgres password=PASSWORD hostaddr=127.0.0.1 port=5432");
        if (c.is_open()) {
            do
            {
                bool isLogged = false;
                std::string email = "";
                login_register_menu(c, isLogged, email);
                logged_menu(c, isLogged, email);
            } while (true);
        }
        else {
            std::cout << "Failed to open database" << std::endl;
            return 1;
        }
        c.close();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

//srand(time(NULL));
//pqxx::work txn(c);
//int num = 0;
//std::string accnum = "BG-";
//for (int i = 0; i < 10; i++)
//{
//    num = rand() % 10;
//    accnum += std::to_string(num);
//}
//return accnum;