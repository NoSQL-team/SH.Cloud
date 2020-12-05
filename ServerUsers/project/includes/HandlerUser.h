//
// Created by lerakry on 04.12.2020.
//

#ifndef SERVERUSERS_HANDLERUSER_H
#define SERVERUSERS_HANDLERUSER_H

//
// Created by lerakry on 04.12.2020.
//

#include <iostream>
#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Session.h"
#include "UsersDatabase.h"

using std::string;
using boost::property_tree::ptree;

class HandlerUser {
public:
    explicit HandlerUser(boost::asio::io_service& io_service, Session& session,
                         UsersDatabase& data_base) : session_(session), data_base_(data_base) {}
    ~HandlerUser() {}
    static std::map<string, string> parser_json(std::stringstream& request);
    void handle_request(string& request);
    void create_user(std::map<string, string>& data_user);
    void data_user(int id);
    void all_users();
    void delete_user(int id);
    void change_user_data(std::map<string, string>& user_data);

private:
    Session& session_;
    UsersDatabase& data_base_;
};



#endif //SERVERUSERS_HANDLERUSER_H
