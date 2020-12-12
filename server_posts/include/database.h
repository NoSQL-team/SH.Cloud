//
// Created by steve on 05.12.2020.
//

#ifndef POSTS_DATABASE_H
#define POSTS_DATABASE_H

#include <string>
#include <pqxx/pqxx>
#include <map>
#include <iostream>
#include <boost/format.hpp>


#include "../include/post.h"
// Класс Post
// id поста
// id пользователя создавшего пост
// дата создания поста
// title поста
// text поста
// attach url картинок

class PostsDataBase {
public:
    // Конектится к базе данных, создается объет таблицы
    PostsDataBase();

    ~PostsDataBase();

    std::string create_post(int user_id, Post& post);
    std::string update_post(int user_id, Post& updated);
    std::string delete_post(int user_id, int post_id);

    std::vector<Post> get_all_posts();
    std::vector<Post> get_user_posts(int user_id);
    std::vector<Post> get_posts_for_user(int fuser_id);
    Post& get_one_post(int post_id);

    bool is_opened();

private:
    // Table Posts_;
    pqxx::connection database_;
    void do_modifying_request(const std::string& sql_request);
    pqxx::result do_select_request(const std::string& sql_request);
};

#endif //POSTS_DATABASE_H
