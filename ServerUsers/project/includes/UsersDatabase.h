//
// Created by lerakry on 05.12.2020.
//

#ifndef SERVERUSERS_USERSDATABASE_H
#define SERVERUSERS_USERSDATABASE_H

#include <iostream>
#include <string>
#include <map>
#include <pqxx/pqxx>
#include "Database.h"

class UsersDatabase : public Database {
public:
//    UsersDatabase();
    ~UsersDatabase() override;
    int insert_(const std::map<std::string, std::string>& users_data) override;
    const std::string data_user(int id);
    const std::string all_users();
    int delete_(int id) override;
    int update_(const std::map<std::string, std::string>& data) override;
//private:
//    pqxx::connection data_base_;
};

#endif //SERVERUSERS_USERSDATABASE_H
