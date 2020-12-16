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
    bool insert(const std::map<std::string, std::string>& users_data, int id_user);
    std::string data_user(int id);
    std::string all_users();
//    bool delete_(int id) override;
    bool update(const std::map<std::string, std::string>& data, int id_user);
    bool exist(int id);
    std::string id_by_nick(std::string& nickname);
};

#endif //SERVERUSERS_USERSDATABASE_H
