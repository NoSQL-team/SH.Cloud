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
    virtual ~UsersDatabase();
    bool insert(const std::map<std::string, std::string>& users_data, int id_user);
	virtual std::string data_user(int id);
	virtual std::string all_users();
    virtual bool update(const std::map<std::string, std::string>& data, int id_user);
	virtual bool exist(int id);
	virtual int get_id();
	virtual std::string id_by_nick(std::string& nickname);
};

#endif //SERVERUSERS_USERSDATABASE_H
