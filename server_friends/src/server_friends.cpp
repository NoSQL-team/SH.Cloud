//
// Created by Andrew Kireev on 02.11.2020.
//

#include "server_friends.h"


namespace tcp_network {

    ServerFriends::~ServerFriends() noexcept {}

    ServerFriends::ServerFriends(const std::string& ip, uint16_t port) {}

    void ServerFriends::add_friend(std::map<std::string, std::string>& request) {}

    std::string ServerFriends::find_friends(int id) {
        return std::string("");
    }

    void ServerFriends::delete_friends(int person_id, int friend_to_del) {}
}