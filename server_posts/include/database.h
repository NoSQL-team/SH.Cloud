//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_DATABASE_H
#define MAIN_TP_DATABASE_H


#include <pqxx/pqxx>
#include <boost/format.hpp>
#include "../include/post.h"

#include <memory>


class PostsDataBase {
public:
    // Конектится к базе данных, создается объет таблицы
    PostsDataBase();

    ~PostsDataBase();

    std::string create_post(Post& post);
    std::string delete_post(std::string& post_id, std::string& creator_id);

    std::string get_likes(const std::string& post_id);
    std::string add_like_by_id(std::string post_id, const std::string& user_id);
    std::string del_like_by_id(std::string post_id, const std::string& user_id);

    bool post_exist(std::string post_id);

    std::vector<Post> get_all_posts(const std::string& sql_limit, const std::string& sql_offset);
    std::vector<Post> get_popular_posts(const std::string& sql_limit, const std::string& sql_offset);
    std::vector<Post> get_user_posts(std::string user_id, const std::string& sql_limit, const std::string& sql_offset);
    std::vector<Post> get_posts_for_user(const std::string& friends_id, std::string sql_limit, std::string sql_offset);

    Post get_one_post(std::string post_id);

private:
    void do_modifying_request(const std::string& sql_request);
    pqxx::result do_select_request(const std::string& sql_request);
};

#endif //MAIN_TP_DATABASE_H
