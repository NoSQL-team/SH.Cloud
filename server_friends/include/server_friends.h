//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_SERVER_FRIENDS_H
#define NOSKOOL_SERVER_FRIENDS_H

#include "connection.h"
#include <unordered_map>
#include <string>

namespace tcp_network {

    class ServerFriends : public IServer{
    public:
        ServerFriends(const std::string& ip, uint16_t port);

        ~ServerFriends() noexcept;

        // Добавит в БД информацию о двух новых друзьях
        void add_friend(std::string request);

        // Приходит "что-то определяющее пользователя",
        // возвращает "что-то" представляющее собой список друзей пользовател
        std::string find_friends(int id);

        // Приходит первых аргементов что-то определяющее пользователя,
        // вторым пользователя, которого нужно удалить из друзей
        void delete_friends(int person_id, int friend_to_del);

    private:
        Socket listenfd_;
        Socket epoll_;
        std::unordered_map<int, Connection> сonnections_;
    };

}

#endif //NOSKOOL_SERVER_FRIENDS_H
