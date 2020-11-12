//
// Created by Andrew Kireev on 06.11.2020.
//

#ifndef NOSKOOL_FRIENDS_DATA_BASE_H
#define NOSKOOL_FRIENDS_DATA_BASE_H

#include <string>
#include <pqxx/pqxx>
#include <map>

class FriendsDataBase {
public:
    // Конектится к базе данных, создается объет таблицы
    FriendsDataBase();

    ~FriendsDataBase();

    // Добавить данные в таблице
    virtual void insert(std::map<std::string, std::string>& request);

    // Взять данные из таблицы
    virtual std::string select(std::map<std::string, std::string>& request);

    // Обновить данные в таблице
    virtual void update();

private:
    // Table friends_;
    pqxx::connection database_;
};

#endif //NOSKOOL_FRIENDS_DATA_BASE_H
