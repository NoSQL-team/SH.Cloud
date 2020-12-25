//
// Created by lerakry on 04.12.2020.
//

#ifndef SERVERUSERS_HANDLERUSER_H
#define SERVERUSERS_HANDLERUSER_H

//
// Created by lerakry on 04.12.2020.
//

#include <string>
#include <map>
#include "Session.h"
#include "UsersDatabase.h"

class HandlerUser {
public:
    explicit HandlerUser(boost::asio::io_service& io_service, Session& session,
                         UsersDatabase& data_base) : session_(session), data_base_(data_base) {}
    ~HandlerUser() = default;
    static std::map<std::string, std::string> parser_json(std::string& request);
    void handle_request(std::string& request);
    void create_user(int number_request, const std::map<std::string, std::string>& data_user, int user_id) const;
    void data_user(int id, int number_request) const;
    void all_users(int number_request) const;
    void update_data(int number_request, const std::map<std::string, std::string>& data_user, int user_id) const;
    void is_exist(int number_request, int id_user) const;
    void id_by_nick(int number_request, std::string& nickname);

private:
    Session& session_;
    UsersDatabase& data_base_;
};



#endif //SERVERUSERS_HANDLERUSER_H
