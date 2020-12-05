//
// Created by lerakry on 04.12.2020.
//

#include <iostream>
#include <string>
#include <map>
#include "../includes/UsersDatabase.h"

using std::string;

    UsersDatabase::UsersDatabase() : data_base_("dbname=Users host=localhost user=lerakrya password=velvalerches")  {}
    UsersDatabase::~UsersDatabase() {
        data_base_.disconnect();
    }
    string UsersDatabase::insert_user(std::map<string, string>& users_data) {
        string sql_requst("INSERT INTO Users VALUES(");
        bool common = true;
        int i = 0;
        for(auto& string : users_data) {
            if (i != 0)
                sql_requst += ", ";
            if (string.first != "AId") {
                sql_requst += "\'" + string.second + "\'";
            } else {
                sql_requst += string.second;
            }
            i = 1;
        }
        sql_requst += ")";

        pqxx::work W(data_base_);
        W.exec(sql_requst);
        W.commit();

        return "OK";
    }
    string UsersDatabase::data_user(int id) {

    }
    string UsersDatabase::all_users() {

    }
    string UsersDatabase::delete_user(int id) {

    }
    string UsersDatabase::update_data(std::map<string, string> data) {

    }

