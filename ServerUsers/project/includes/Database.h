//
// Created by lerakrya on 11.12.2020.
//

#ifndef SERVERUSERS_DATABASE_H
#define SERVERUSERS_DATABASE_H

#include <string>
#include <map>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <pqxx/pqxx>

class Database {
public:
    Database();
    virtual ~Database() {}
    void insert_(std::string& request);
    pqxx::result select_(std::string& request);

protected:
    std::unique_ptr<pqxx::connection> database_;
};

#endif //SERVERUSERS_DATABASE_H
