//
// Created by Andrew Kireev on 06.11.2020.
//

#ifndef NOSKOOL_FRIENDS_DATA_BASE_H
#define NOSKOOL_FRIENDS_DATA_BASE_H

#include <string>
#include <map>

class FriendsDataBase {
public:
    // Конектится к базе данных, создается объет таблицы
    FriendsDataBase();

    ~FriendsDataBase();

    // Добавить данные в таблице
    void insert(std::map<std::string, std::string> request);

    // Взять данные из таблицы
    std::string select();

    // Обновить данные в таблице
    void update();

private:
    // Table friends_;
};

#endif //NOSKOOL_FRIENDS_DATA_BASE_H
