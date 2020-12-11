//
// Created by lerakrya on 11.12.2020.
//

#ifndef SERVERUSERS_DATABASE_H
#define SERVERUSERS_DATABASE_H

#include <string>
#include <map>
#include <pqxx/pqxx>

class Database {
public:
    Database() : database_("dbname=users host=localhost user=andrewkireev password=") {}
    virtual ~Database() = 0;
    virtual int insert_(const std::map<std::string, std::string>& users_data) = 0;
    virtual int delete_(int id) = 0;
    virtual int update_(const std::map<std::string, std::string>& data) = 0;
protected:
    pqxx::connection database_;
};

#endif //SERVERUSERS_DATABASE_H
