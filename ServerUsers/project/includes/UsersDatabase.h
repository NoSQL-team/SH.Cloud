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
    int insert_user(const std::map<string, string>& users_data);
    const string data_user(int id);
    const string all_users();
    int delete_user(int id);
    int update_data(const std::map<string, string>& data);
private:
    pqxx::connection data_base_;
};

#endif //SERVERUSERS_USERSDATABASE_H
