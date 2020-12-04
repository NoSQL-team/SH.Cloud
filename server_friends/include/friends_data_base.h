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

    // Добавить данные в таблице
    virtual void insert(std::map<std::string, std::string>& request);

    // Взять данные из таблицы
    virtual std::string select(std::map<std::string, std::string>& request);

    int add_friend(int user_1, int user_2);

    std::vector<int> get_all_friends(int user_id);

    // Обновить данные в таблице
    virtual void update();

    bool is_opened();

    std::string make_request(std::string& request);

private:
    // Table friends_;
    pqxx::connection database_;
};

#endif //NOSKOOL_FRIENDS_DATA_BASE_H
