//
// Created by steve on 15.12.2020.
//

#include "../include/database.h"

PostsDataBase::PostsDataBase() :
        database_("dbname=db_posts host=localhost user=amartery password=amartery") {}

PostsDataBase::~PostsDataBase() {
    database_.disconnect();
}

void PostsDataBase::do_modifying_request(const std::string& sql_request) {
    pqxx::work W(database_);
    W.exec(sql_request);
    W.commit();
}

pqxx::result PostsDataBase::do_select_request(const std::string& sql_request) {
    pqxx::nontransaction N(database_);
    return N.exec(sql_request);
}

std::string PostsDataBase::create_post(Post& post) {
    boost::format creating_sql_req =
            (boost::format(
                    "insert into "
                    "posts(post_id, creator_id, creation_date, title, text, attach) "
                    "values (%1%, %2%, '%3%', '%4%', '%5%', '%6%')")
             %post.post_id
             %post.creator_id
             %post.creation_date
             %post.title
             %post.text
             %post.attach);
    std::string sql_req = boost::str(creating_sql_req);
    do_modifying_request(sql_req);
    return "OK";
}


std::string PostsDataBase::update_post(int post_id, Post& updated) {
    std::string res = "OK";
    try {
        delete_post(post_id);
        create_post(updated);
    } catch (pqxx::sql_error const &e) {
        res = "ERROR";
    }
    return res;
}

std::string PostsDataBase::delete_post(int post_id) {
    boost::format creating_sql_req =
            (boost::format("delete from posts where \"post_id\" = %1%")%post_id);
    std::string sql_request = boost::str(creating_sql_req);
    std::string res = "OK";
    try {
        do_modifying_request(sql_request);
    } catch (pqxx::sql_error const &e) {
        res = "ERROR";
    }
    return res;
}


std::vector<Post> PostsDataBase::get_all_posts() {
    std::string sql_request = "select * from posts";
    pqxx::result r = do_select_request(sql_request);
    std::vector<Post> result;
    for (const auto& row: r) {
        Post temp(
                row[0].as<int>(),
                row[1].as<int>(),
                row[2].as<std::string>(),
                row[3].as<std::string>(),
                row[4].as<std::string>(),
                row[5].as<std::string>());
        result.push_back(temp);
    }
    return result;
}


std::vector<Post> PostsDataBase::get_user_posts(int user_id) {
    boost::format creating_sql_req =
            (boost::format("select * from posts where \"creator_id\" = %1%")%user_id);
    std::string sql_request = boost::str(creating_sql_req);
    pqxx::result r = do_select_request(sql_request);
    std::vector<Post> result;
    for (const auto& row: r) {
        Post temp(
                row[0].as<int>(),
                row[1].as<int>(),
                row[2].as<std::string>(),
                row[3].as<std::string>(),
                row[4].as<std::string>(),
                row[5].as<std::string>());
        result.push_back(temp);
    }
    return result;
}


Post PostsDataBase::get_one_post(int post_id) {
    boost::format creating_sql_req =
            (boost::format("select * from posts where \"post_id\" = %1%")%post_id);
    std::string sql_request = boost::str(creating_sql_req);
    pqxx::result r = do_select_request(sql_request);
    auto row = r.at(0);
    Post result(
            row[0].as<int>(),
            row[1].as<int>(),
            row[2].as<std::string>(),
            row[3].as<std::string>(),
            row[4].as<std::string>(),
            row[5].as<std::string>());
    return result;
}


std::vector<Post> PostsDataBase::get_posts_for_user(const std::vector<int>& posts_ids) {
    std::vector<Post> result;
    result.reserve(posts_ids.size());
    for (const auto& id : posts_ids) {
        result.push_back(get_one_post(id));
    }
    return result;
}


bool PostsDataBase::is_opened() {
    if (database_.is_open()) {
        std::cout << "Соединение с бд открыто" << std::endl;
        return true;
    }
    std::cout << "Соединение с бд закрыто" << std::endl;
    return false;
}