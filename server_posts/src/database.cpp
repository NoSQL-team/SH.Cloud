//
// Created by steve on 04.12.2020.
//
#include "../include/database.h"

PostsDataBase::PostsDataBase() :
        database_("dbname=db_posts host=localhost user=amartery password=amartery") {}

PostsDataBase::~PostsDataBase() {
    database_.disconnect();
}


std::string PostsDataBase::create_post(int user_id, Post& post) {
    std::string sql_request("INSERT INTO Posts VALUES(");

}
std::string PostsDataBase::update_post(int user_id, Post& updated) {

}
std::string PostsDataBase::delete_post(int user_id, int post_id) {

}

std::vector<Post> PostsDataBase::get_all_posts() {

}
std::vector<Post> PostsDataBase::get_user_posts(int user_id) {

}
std::vector<Post> PostsDataBase::get_posts_for_user(int fuser_id) {

}
Post& PostsDataBase::get_one_post(int post_id) {

}

bool PostsDataBase::is_opened() {
    if (database_.is_open()) {
        std::cout << "Соединение с бд открыто" << std::endl;
        return true;
    }
    std::cout << "Соединение с бд закрыто" << std::endl;
    return false;
}


