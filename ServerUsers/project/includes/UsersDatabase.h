//
// Created by lerakry on 05.12.2020.
//

#ifndef SERVERUSERS_USERSDATABASE_H
#define SERVERUSERS_USERSDATABASE_H

#include <iostream>
#include <string>
#include <map>
#include <pqxx/pqxx>

using std::string;

class UsersDatabase {
public:
    UsersDatabase();
    ~UsersDatabase();
    string insert_user(std::map<string, string>& users_data);
    string data_user(int id);
    string all_users();
    string delete_user(int id);
    string update_data(std::map<string, string> data);
private:
    pqxx::connection data_base_;
};

#endif //SERVERUSERS_USERSDATABASE_H
