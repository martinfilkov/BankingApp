#pragma once

#ifndef BANK_FUNCTIONS_H
#define BANK_FUNCTIONS_H

#include <pqxx/connection.hxx>

void account_summary(pqxx::connection& c, std::string& email);

std::string deposit_funds(pqxx::connection& c, std::string& email);

std::string send_funds(pqxx::connection& c, std::string& email);

#endif