//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_DATABASE_H
#define MAIN_TP_DATABASE_H

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

    std::string create_post(Post& post);
    std::string update_post(int post_id, Post& updated);

    std::string delete_post(int post_id);

    std::vector<Post> get_all_posts();
    std::vector<Post> get_user_posts(int user_id);
    std::vector<Post> get_posts_for_user(const std::vector<int>& post_ids);
    Post get_one_post(int post_id);

    bool is_opened();

private:
    pqxx::connection database_;
    void do_modifying_request(const std::string& sql_request);
    pqxx::result do_select_request(const std::string& sql_request);
};

#endif //MAIN_TP_DATABASE_H
