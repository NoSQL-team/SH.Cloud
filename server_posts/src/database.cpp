//
// Created by steve on 15.12.2020.
//

#include "../include/database.h"
#include "../include/utility_for_lib.h"

#include <iostream>
#include <thread>
#include <chrono>


PostsDataBase::PostsDataBase() {}

PostsDataBase::~PostsDataBase() {
//    database_->disconnect();
}

void PostsDataBase::do_modifying_request(const std::string& sql_request) {
    pqxx::connection con("dbname=db_posts host=localhost user=amartery password=password port=27007");
    pqxx::work W(con);
    W.exec(sql_request);
    W.commit();
}

pqxx::result PostsDataBase::do_select_request(const std::string& sql_request) {
    pqxx::connection con("dbname=db_posts host=localhost user=amartery password=password port=27007");
    pqxx::nontransaction N(con);
    auto res = N.exec(sql_request);
    N.commit();
    return res;
}

std::string PostsDataBase::create_post(Post& post) {
    boost::format creating_sql_req =
            (boost::format(
                    "insert into "
                    "posts(creator_id, creation_date, title, text, attach, amount_likes, liked_users) "
                    "values (%1%, now(), '%2%', '%3%', '%4%', 0, 'none')")
             %post.creator_id
             %post.title
             %post.text
             %post.attach);
    std::string sql_req = boost::str(creating_sql_req);
    do_modifying_request(sql_req);

    std::string sql_req_for_post_id = "select max(post_id) from posts";
    pqxx::result r = do_select_request(sql_req_for_post_id);
    auto post_id = r[0][0].as<std::string>();
    return post_id;
}


std::string PostsDataBase::delete_post(std::string& post_id, std::string& user_id) {
    boost::format raw_sql_req =
            (boost::format("select creator_id from posts where post_id = %1%")%post_id);
    std::string sql_req = boost::str(raw_sql_req);

    pqxx::result r = do_select_request(sql_req);
    auto creator_id = r[0][0].as<std::string>();

    boost::format creating_sql_req =
            (boost::format("delete from posts where post_id = %1%")%post_id);
    std::string sql_request = boost::str(creating_sql_req);

    // проверяем является ли пользователь создателем
    if (creator_id == user_id) {
        try {
            // удаляем пост
            do_modifying_request(sql_request);
            return "success";
        } catch (pqxx::sql_error const &e) {
            return "error";
        }
    } else {
        return "error";
    }
}


std::vector<Post> PostsDataBase::get_all_posts() {
    std::string sql_request = "select * from posts";
    pqxx::result r = do_select_request(sql_request);
    std::vector<Post> result;
    for (const auto& row: r) {
        Post temp(
                row[1].as<int>(),
                row[3].as<std::string>(),
                row[4].as<std::string>(),
                row[5].as<std::string>(),
                row[2].as<std::string>(),
                row[0].as<int>(),
                row[6].as<int>(),
                row[7].as<std::string>());
        result.push_back(temp);
    }
    return result;
}


std::vector<Post> PostsDataBase::get_user_posts(std::string user_id) {
    boost::format creating_sql_req =
            (boost::format("select * from posts where creator_id = %1%")%user_id);
    std::string sql_request = boost::str(creating_sql_req);
    pqxx::result r = do_select_request(sql_request);
    std::vector<Post> result;
    for (const auto& row: r) {
        Post temp(
                row[1].as<int>(),
                row[3].as<std::string>(),
                row[4].as<std::string>(),
                row[5].as<std::string>(),
                row[2].as<std::string>(),
                row[0].as<int>(),
                row[6].as<int>(),
                row[7].as<std::string>());
        result.push_back(temp);
    }
    return result;
}


Post PostsDataBase::get_one_post(std::string post_id) {
    boost::format creating_sql_req =
            (boost::format("select * from posts where post_id = %1%")%post_id);
    std::string sql_request = boost::str(creating_sql_req);
    pqxx::result r = do_select_request(sql_request);
    auto row = r.at(0);
    Post result(
            row[1].as<int>(),
            row[3].as<std::string>(),
            row[4].as<std::string>(),
            row[5].as<std::string>(),
            row[2].as<std::string>(),
            row[0].as<int>(),
            row[6].as<int>(),
            row[7].as<std::string>());
    return result;
}


std::vector<Post> PostsDataBase::get_posts_for_user(const std::string& friends_id) {
    boost::format creating_sql_req =
            (boost::format("select * from posts where creator_id in(%1%) order by creation_date desc")%friends_id);
    std::string sql_request = boost::str(creating_sql_req);
    pqxx::result r = do_select_request(sql_request);
    std::vector<Post> result;
    for (const auto& row: r) {
        Post temp(
                row[1].as<int>(),
                row[3].as<std::string>(),
                row[4].as<std::string>(),
                row[5].as<std::string>(),
                row[2].as<std::string>(),
                row[0].as<int>(),
                row[6].as<int>(),
                row[7].as<std::string>());
        result.push_back(temp);
    }
    return result;
}

std::string PostsDataBase::get_likes(const std::string& post_id) {
    std::string sql_req_for_post_id = "select liked_users from posts where post_id = " + post_id;
    pqxx::result r = do_select_request(sql_req_for_post_id);
    auto result = r[0][0].as<std::string>();
    return result;
}

std::string PostsDataBase::add_like_by_id(std::string post_id, const std::string& user_id) {
    std::string likes = get_likes(post_id);
    std::vector<std::string> vec_likes = split(likes, " ");


    auto itr = std::find(vec_likes.begin(), vec_likes.end(), user_id);
    // если такого лайка нет
    if (itr == vec_likes.end()) {
        // обновим поле с id пользователей которые поставили лайк
        std::string updated_likes = likes + " " + user_id;
        boost::format creating_sql_req = (boost::format("update posts "
                                                        "set liked_users = '%1%' "
                                                        "where post_id = %2%")
                                          %updated_likes
                                          %post_id);
        std::string sql_req = boost::str(creating_sql_req);
        do_modifying_request(sql_req);

        // обновим количество лайков, прибавим 1
        std::string sql_req_update_amount = "update posts "
                                            "set amount_likes = amount_likes + 1 "
                                            "where post_id = " + post_id;
        do_modifying_request(sql_req_update_amount);

        return "success";
    } else {
        return "error";
    }
}

std::string PostsDataBase::del_like_by_id(std::string post_id, const std::string& user_id) {
    std::string likes = get_likes(post_id);

    std::vector<std::string> vec_likes = split(likes, " ");
    // если лайк есть
    auto itr = std::find(vec_likes.begin(), vec_likes.end(), user_id);
    if (itr != vec_likes.end()) {
        vec_likes.erase(itr); // удалим лайк

        // преобразуем вектор к строке
        std::ostringstream oss;
        std::copy(vec_likes.begin(), vec_likes.end() - 1,
                  std::ostream_iterator<std::string>(oss, " "));
        oss << vec_likes.back(); // копируем последний символ, чтобы не было пробела в конце
        std::string after_deleting = oss.str();

        boost::format creating_sql_req = (boost::format("update posts "
                                                        "set liked_users = '%1%' "
                                                        "where post_id = %2%")
                                          %after_deleting
                                          %post_id);
        std::string sql_req = boost::str(creating_sql_req);
        do_modifying_request(sql_req);

        // обновим количество лайков, уменьшим на 1
        std::string sql_req_update_amount = "update posts "
                                            "set amount_likes = amount_likes - 1 "
                                            "where post_id = " + post_id;
        do_modifying_request(sql_req_update_amount);

        return "success";
    } else {
        return "error";
    }
}
