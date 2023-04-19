#include <string>
#include <iostream>
#include <pqxx/pqxx> 

void account_summary(pqxx::connection& c, std::string& email)
{
	pqxx::nontransaction query(c);

	pqxx::result r = query.exec_params("SELECT * FROM account_summary($1)", email);

    for (pqxx::result::const_iterator row = r.begin(); row != r.end(); ++row) {
        std::cout << "First Name: " << row[0].as<std::string>() << std::endl;
        std::cout << "Last Name: " << row[1].as<std::string>() << std::endl;
        std::cout << "Email: " << row[2].as<std::string>() << std::endl;
        std::cout << "Account Number: " << row[3].as<std::string>() << std::endl;
        std::cout << "Account Balance: " << row[4].as<double>() << '$' << std::endl;
        std::cout << std::endl;
    }
    system("pause");
}


std::string deposit_funds(pqxx::connection& c, std::string& email)
{
    int deposit;
    std::cout << "How much would you like to deposit: " << std::endl;
    while (!(std::cin >> deposit))
    {
        std::cout << "Invalid deposit, please enter again:";
        std::cin.clear();
        std::cin.ignore(999, '\n');
    }

    pqxx::nontransaction query(c);

    pqxx::result r = query.exec_params("SELECT * FROM deposit_funds($1, $2)", email, deposit);
    std::string message = r[0][0].as<std::string>();
    return message;
}


std::string send_funds(pqxx::connection& c, std::string& email)
{
    int funds;
    std::string account_number;
    std::cout << "How much would you like to send: " << std::endl;
    while (!(std::cin >> funds))
    {
        std::cout << "Invalid deposit, please enter again:";
        std::cin.clear();
        std::cin.ignore(999, '\n');
    }
    std::cout << "Account number of the recipient: " << std::endl;
    std::cin >> account_number;

    pqxx::nontransaction query(c);

    pqxx::result r = query.exec_params("SELECT * FROM send_funds($1, $2, $3)", email, account_number, funds);
    std::string message = r[0][0].as<std::string>();
    return message;
}