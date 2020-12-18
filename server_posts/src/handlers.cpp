//
// Created by steve on 15.12.2020.
//

#include "../include/handlers.h"
#include "../include/utility_for_lib.h"
#include <map>
#include <vector>


bool is_authorized(int user_id) {
    // TODO: реализовать запрос в auth

    // пока заглушка
    return true;
}


std::string Handlers::for_user(const std::string& id_request, const std::map<std::string, size_t>& args) {
    std::string result = "id_request: "
                            + id_request
                            + " posts for user with id: "
                            + std::to_string(args.at("user_id")) + "\n";

    // TODO: получить need posts oт friends
    // TODO: отправка запроса на сервер friends, ответ которого нужно
    // TODO: нужно преобразовать в вектор из post_id которые нужно достать из БД
    std::vector<int> need_posts;
    std::vector<Post> vec_posts = _db.get_posts_for_user(need_posts);
    std::string posts = vec_posts_to_str(vec_posts);
    return result + posts;
}

std::string Handlers::all_posts(const std::string& id_request, const std::map<std::string, size_t>& args) {
    // TODO: добавить try catch
    std::string result = "id_request: " + id_request + " all posts" + "\n";

    std::vector<Post> vec_posts = _db.get_all_posts();
    std::string posts = vec_posts_to_str(vec_posts);
    return result + posts;
}

std::string Handlers::user_posts(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: добавить try catch
    std::string usr_id = std::to_string(args.at("user_id"));
    std::string result = "id_request: "
                                + id_request
                                + " user`s posts with id: "
                                + usr_id
                                + "\n";

    std::vector<Post> vec_posts = _db.get_user_posts(args.at("user_id"));
    std::string posts = vec_posts_to_str(vec_posts);
    return result + posts;
}

std::string Handlers::one_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: добавить try catch
    std::string result = "id_request: "
                            + id_request
                            + " post with id: "
                            + std::to_string(args.at("post_id")) + "\n";
    Post one = _db.get_one_post(args.at("post_id"));
    return result + one_post_to_str(one);
}
std::string Handlers::delete_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    std::string result = "id_request: " + id_request +
                         " deleting a post with id: " + std::to_string(args.at("post_id")) +
                         " by a user with id: " + std::to_string(args.at("user_id"));
    if (is_authorized(args.at("user_id"))) {
        return _db.delete_post(args.at("post_id"));
    } else {
        return "ERROR";
    }
}

std::string Handlers::create_post(std::string const& id_request,
                        std::map<std::string, size_t> const& args,
                        std::string const& body) {
    // TODO: добавить try catch
    Post new_post = parse_body(body);
    boost::format parsed_body =
            (boost::format(
                    "post_id: %1%,\n"
                    " creator_id: %2%,\n"
                    " creation_date: %3%,\n"
                    " title: %4%,\n"
                    " text: %5%,\n"
                    " attach: %6%\n")
             %new_post.post_id
             %new_post.creator_id
             %new_post.creation_date
             %new_post.title
             %new_post.text
             %new_post.attach);
    std::string body_str = boost::str(parsed_body);
    std::string result = "id_request: "
                         + id_request
                         + " creating a post by a user with id: "
                         + std::to_string(args.at("user_id"))
                         + "\n" + body_str;

    // TODO: запрос к auth авторизирован ли пользователь
    return result;
}

std::string Handlers::update_post(std::string const& id_request,
                        std::map<std::string, size_t> const& args,
                        std::string const& body) {
    // TODO: добавить try catch
    // TODO: запрос к auth авторизирован ли пользователь
    Post for_update = parse_body(body);
    boost::format parsed_body =
            (boost::format(
                    "post_id: %1%,\n"
                    " creator_id: %2%,\n"
                    " creation_date: %3%,\n"
                    " title: %4%,\n"
                    " text: %5%,\n"
                    " attach: %6%\n")
             %for_update.post_id
             %for_update.creator_id
             %for_update.creation_date
             %for_update.title
             %for_update.text
             %for_update.attach);
    std::string body_str = boost::str(parsed_body);
    std::string result = "id_request: "
                         + id_request
                         + " changing a post with id: "
                         + std::to_string(args.at("post_id"))
                         + " by a user with id: "
                         + std::to_string(args.at("user_id"))
                         + "\n" + body_str;;
    return result;
}