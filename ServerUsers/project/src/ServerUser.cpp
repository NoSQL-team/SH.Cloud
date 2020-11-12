//
// Created by lerakry on 12.11.2020.
//

#include "ServerUser.h"
#include "SServer.h"

tcp_server::ServerUser::ServerUser(const std::string& ip, const uint16_t port) {}
tcp_server::ServerUser::~ServerUser() noexcept {}

void tcp_server::ServerUser::process(std::string request) {}

bool tcp_server::ServerUser::CheckUser() {
    return true;
}

std::string tcp_server::ServerUser::Send() {
    return "dkhgdfg";
}

std::string tcp_server::ServerUser::CreateUser(std::string user, std::map<std::string, std::string> users_data ) {
    return "jdhgfdhg";
}

std::string ChangeUserData(std::string user, std::map<std::string, std::string> users_data) {
    return "jsdhfdgs";
}

std::string tcp_server::ServerUser::AllUsers() {
    return "kjdfgyegdsg";
}

std::string tcp_server::ServerUser::DeleteUser(std::string user) {
    return "jdhgwisp";
}

std::map<std::string, std::string> tcp_server::ServerUser::UsersData(std::string user) {
    std::map<std::string, std::string> m;
    m["lpao"] = "qpaknh";
    return m;
}

std::string tcp_server::ServerUser::get() {
    return "kajsdi";
}

void tcp_server::ServerUser::delete_data() {}

void tcp_server::ServerUser::insert() {}



