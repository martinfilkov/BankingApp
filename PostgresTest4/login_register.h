#pragma once

#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include <pqxx/connection.hxx>

bool account_login_db(pqxx::connection& c, std::string &p_email);

std::string createAccountNumber();

void account_register_db(pqxx::connection& c);

std::string register_password();

#endif