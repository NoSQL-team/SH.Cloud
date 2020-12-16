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
    virtual ~Database() {}
    void insert_(std::string& request);
//    virtual bool delete_(int id) = 0;
    pqxx::result select_(std::string& request);

protected:
    pqxx::connection database_;
};

#endif //SERVERUSERS_DATABASE_H
