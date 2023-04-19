#include <string>
#include <iostream>
#include <pqxx/pqxx> 
#include <conio.h>
#include <ctime>
#include <random>
#include <regex>
//#include <tuple>


std::string register_password()
{
    std::string password;
    char a;
    std::cout << "Password:" << std::endl;
    while ((a = _getch()) != '\r') {
        if (a == '\b') {
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password += a;
            std::cout << '*';
        }
    }
    //std::hash<std::string> hasher;
    //std::string hashed_password = std::to_string(hasher(password));

    return password;
}

bool account_login_db(pqxx::connection& c, std::string &p_email)
{
    system("cls");
    std::string email, password;

    std::cout << "-----------------------------" << std::endl;
    std::cout << "       Login Page" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Email:" << std::endl;
    std::cin >> email;
    password = register_password();
    pqxx::work txn(c);
    pqxx::result result = txn.exec_params("SELECT login_user($1, $2)",
        email,
        password
    );
    bool exists = result[0][0].as<bool>();

    if (exists)
    {
        std::cout << std::endl << "Successfully Logged" << std::endl;
        p_email = email;
    }
    else std::cout << std::endl << "Failed Logging" << std::endl;
    system("pause");
    
    return exists;
}

std::string createAccountNumber()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> letter_distribution(0, 25);
    std::uniform_int_distribution<int> digit_distribution(0, 9);

    std::string result;
    char letter1 = 'A' + letter_distribution(generator);
    char letter2 = 'A' + letter_distribution(generator);
    result += letter1;
    result += letter2;
    result += "-";
    for (int i = 0; i < 10; i++) {
        result += std::to_string(digit_distribution(generator));
    }
    return result;
}

void account_register_db(pqxx::connection& c)
{
    system("cls");
    std::string first_name, last_name, email, account_number, password;
    
    const std::regex email_pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    const std::regex password_pattern(R"((?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9]).{8,})");
    const std::regex name_pattern(R"([a-zA-Z][a-zA-Z'-]*[a-zA-Z])");
    
    try
    {
        account_number = createAccountNumber();

        std::cout << "-----------------------------" << std::endl;
        std::cout << "       Register Page" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "First Name: " << std::endl;
        while (true)
        {
            std::cin >> first_name;
            if (std::regex_match(first_name, name_pattern)) break;
            else std::cout << std::endl << "Invalid first name! Please enter again!" << std::endl;
        }
        std::cout << "Last Name: " << std::endl;
        while (true)
        {
            std::cin >> last_name;
            if (std::regex_match(last_name, name_pattern)) break;
            else std::cout << std::endl << "Invalid first name! Please enter again!" << std::endl;
        }
        std::cout << "Email: " << std::endl;
        while (true)
        {
            std::cin >> email;
            if (std::regex_match(email, email_pattern)) break;
            else std::cout << std::endl << "Invalid email! Please enter again!" << std::endl;   
        }

        do
        {
            password = register_password();
            if (std::regex_match(password, password_pattern) == false)
            {
                std::cout << std::endl << "Password should include at least one lower case character, upper case character, number and a special character! It should also be at least 8 characters long!" << std::endl;
            }
        } while (std::regex_match(password, password_pattern) == false);
        pqxx::work txn(c);
        pqxx::result result = txn.exec_params("SELECT register_user($1, $2, $3, $4, $5)",
            first_name,
            last_name,
            email,
            password,
            account_number
        );
        txn.commit();

        system("cls");
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Your account was successfully created" << std::endl;
        std::cout << "Your account number is: " << account_number << std::endl;
        std::cout << "-----------------------------" << std::endl;
        system("pause");
    }
    catch (const std::exception& e)
    {
        system("cls");
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Failed creating account" << std::endl;
        std::cerr << e.what() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        system("pause");
    }
}