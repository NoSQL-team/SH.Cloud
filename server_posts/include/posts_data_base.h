//
// Created by amartery on 08.11.2020.
//

#ifndef NOSKOOL_POSTS_DATA_BASE_H
#define NOSKOOL_POSTS_DATA_BASE_H

#include "server_posts.h"
#include <string>
#include <map>
#include <pqxx/pqxx>  // для PostgreSQL

class PostsDataBase {
public:
    // Конект к базе данных, создается объет таблицы
    PostsDataBase();

    ~PostsDataBase();

    // Добавить данные в таблицу
    void insert(std::map<std::string, std::string> request);

    // Взять данные из таблицы
    std::string select();

    // Обновить данные в таблице
    void update();

private:
    // Table posts_;
    // обертак для PostgreSQL
    pqxx::connection database_;
};

#endif  // NOSKOOL_POSTS_DATA_BASE_H