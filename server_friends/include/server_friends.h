//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_SERVER_FRIENDS_H
#define NOSKOOL_SERVER_FRIENDS_H

#include "connection.h"

#include "server_interface.h"
#include "friends_data_base.h"
#include <unordered_map>
#include <string>

namespace tcp_network {

    class ServerFriends : public IServer{
    public:
        ServerFriends(const std::string& ip, uint16_t port);

        ServerFriends() = default;

        ~ServerFriends() noexcept;

        // Добавит в БД информацию о двух новых друзьях
        void add_friend(std::map<std::string, std::string>& request);

        // Проверяет есть ли такой друг у пользователя
        std::string is_friends(int id_first, int id_second);

        // Приходит первых аргементов что-то определяющее пользователя,
        // вторым пользователя, которого нужно удалить из друзей
        void delete_friends(int person_id, int friend_to_del);

        // Возвращает список всех друзей пользователя в json
        std::string get_all_friends(int id);

    private:
        std::unique_ptr<FriendsDataBase> database_connector_;
    };

}

#endif //NOSKOOL_SERVER_FRIENDS_H
