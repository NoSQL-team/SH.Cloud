//
// Created by Andrew Kireev on 06.11.2020.
//

#ifndef NOSKOOL_FRIENDS_DATA_BASE_H
#define NOSKOOL_FRIENDS_DATA_BASE_H

#include <string>
#include <pqxx/pqxx>
#include <map>
#include <iostream>

class FriendsDataBase {
public:
    // Конектится к базе данных, создается объет таблицы
    FriendsDataBase();

    ~FriendsDataBase();

    int add_friend(int user_1, int user_2);

    std::vector<int> get_all_friends(int user_id);

    int delete_friend(int user_1, int user_2);

    bool is_friend(int user_1, int user_2);

    bool is_opened();

private:
    // Table friends_;
    pqxx::connection database_;
};

#endif //NOSKOOL_FRIENDS_DATA_BASE_H
