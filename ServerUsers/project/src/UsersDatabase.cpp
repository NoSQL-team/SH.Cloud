//
// Created by lerakry on 04.12.2020.
//

#include <iostream>
#include <string>
#include <map>
#include "UsersDatabase.h"

using std::string;

    UsersDatabase::~UsersDatabase() {}

    int UsersDatabase::insert_(const std::map<string, string>& users_data) {
        string sql_request("INSERT INTO users VALUES(");
        int i = 0;
        for(auto& string : users_data) {
            if (i != 0)
                sql_request += ", ";
            if (string.first.substr(1) != "id") {
                sql_request += "\'" + string.second + "\'";
            } else {
                sql_request += string.second;
            }
            i = 1;
        }
        sql_request += ")";

        if(data_user(atoi(users_data.at("Aid").c_str())) == "No user") {
            pqxx::work W(database_);
            W.exec(sql_request);
            W.commit();
            return 200;
        }
        return 300;
    }


    const string UsersDatabase::data_user(int id) {
        string sql_request("SELECT * FROM Users WHERE id=");
        sql_request += std::to_string(id);

        pqxx::nontransaction N(database_);

        pqxx::result R( N.exec( sql_request ));

        string answer = "{\n";
        "  \"Id\": 5,\n";

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            answer += "  \"firstname\": \"" + c[1].as<string>() + "\" ,\n";
            answer += "  \"lastname\": \"" + c[2].as<string>() + "\" ,\n";
            answer += "  \"nickname\": \"" + c[3].as<string>() + "\" ,\n";
            answer += "  \"email\": \"" + c[4].as<string>() + "\" ,\n";
            answer += "  \"photo\": \"" + c[5].as<string>() + "\" ,\n";
        }
        answer += "}";

        if (answer == "{\n}") {
            return "No user";
        }

        return answer;
    }

    const string UsersDatabase::all_users() {
        string sql_request("SELECT nickname FROM users");

        pqxx::nontransaction N(database_);

        pqxx::result R( N.exec( sql_request ));

        string answer = "{\n";

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            answer += "  \"nickname\": \"" + c[0].as<string>() + "\" ,\n";
        }
        answer += "}";

        if (answer == "{\n}") {
            return "No users";
        }

        return answer;
    }
    int UsersDatabase::delete_(int id) {
        string sql_request("DELETE FROM users WHERE id=");
        sql_request += std::to_string(id);
        std::cout << sql_request << std::endl;

        if (data_user(id) == "No user") {
            return 0;
        }

        pqxx::work W(database_);

        W.exec( sql_request );
        W.commit();

        return 200;
    }

    int UsersDatabase::update_(const std::map<string, string>& data) {
        string sql_request("UPDATE users SET ");

        int i = 0;
        for(const auto& v : data) {
            i++;
            if (i == 1)
                continue;
            if (i != 2 ) {
                sql_request += ", ";
            }
            sql_request += v.first.substr(1) + "=\'" + v.second + "\'";
        }

        sql_request += " WHERE id=" + data.at("Aid");

        if(data_user(atoi(data.at("Aid").c_str())) == "No user") {
            return 0;
        }
        pqxx::work W(database_);

        W.exec( sql_request );
        W.commit();
        return 200;
    }

