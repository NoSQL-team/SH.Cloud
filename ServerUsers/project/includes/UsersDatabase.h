//
// Created by lerakry on 05.12.2020.
//

#ifndef SERVERUSERS_USERSDATABASE_H
#define SERVERUSERS_USERSDATABASE_H

#include <string>
#include <map>
#include "Database.h"

class UsersDatabase : public Database {
public:
    ~UsersDatabase() override;
    bool insert_(const std::map<std::string, std::string>& users_data) override;
    std::string data_user(int id);
    std::string all_users();
    bool delete_(int id) override;
    bool update_(const std::map<std::string, std::string>& data) override;
    bool exist(int id);
    std::string id_by_nick(int number_request, std::string& nickname);
};

#endif //SERVERUSERS_USERSDATABASE_H
