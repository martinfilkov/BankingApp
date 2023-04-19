#pragma once

#ifndef MENU_LIST_H
#define MENU_LIST_H

#include <pqxx/connection.hxx>

void login_register_menu(pqxx::connection& c, bool &isLogged, std::string &email);

void logged_menu(pqxx::connection& c, bool &isLogged, std::string &email);

#endif