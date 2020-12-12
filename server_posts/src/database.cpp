//
// Created by steve on 04.12.2020.
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

std::string PostsDataBase::create_post(int user_id, Post& post) {
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


std::string PostsDataBase::update_post(int user_id, Post& updated) {

}

std::string PostsDataBase::delete_post(int user_id, int post_id) {

}


std::vector<Post> PostsDataBase::get_all_posts() {
    std::string sql_request = "select * from posts";
    pqxx::result r = do_select_request(sql_request);
    std::vector<Post> result;
    for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {
        Post temp(
                c[0].as<int>(),
                        c[1].as<int>(),
                                c[2].as<std::string>(),
                                        c[3].as<std::string>(),
                                                c[4].as<std::string>(),
                                                        c[5].as<std::string>());
        result.push_back(temp);
    }
    return result;
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


