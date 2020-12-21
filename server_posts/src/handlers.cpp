//
// Created by steve on 15.12.2020.
//

#include "../include/handlers.h"
#include "../include/utility_for_lib.h"
#include <map>
#include <vector>



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
    // TODO: формирование ответа
    return result + posts;
}

std::string Handlers::all_posts(const std::string& id_request, const std::map<std::string, size_t>& args) {
    // TODO: добавить try catch
    std::string result = "id_request: " + id_request + " all posts" + "\n";

    std::vector<Post> vec_posts = _db.get_all_posts();
    std::string posts = vec_posts_to_str(vec_posts);
    // TODO: формирование ответа
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
    // TODO: формирование ответа
    return result + posts;
}

std::string Handlers::one_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: добавить try catch
    std::string result = "id_request: "
                            + id_request
                            + " post with id: "
                            + std::to_string(args.at("post_id")) + "\n";
    Post one = _db.get_one_post(args.at("post_id"));
    // TODO: формирование ответа
    return result + one_post_to_str(one);
}
std::string Handlers::delete_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    std::string result;
    std::string post_id = std::to_string(args.at("post_id"));
    std::string user_id = std::to_string(args.at("user_id"));
    try {
        std::string status = _db.delete_post(post_id, user_id);
        result = "{'status': '" + status + "'}";
    } catch(std::exception const& e) {
        result = "{'error': 'failed to delete post'}";
    }

    return result;
}

std::string Handlers::create_post(std::string const& id_request,
                        std::map<std::string, size_t> const& args,
                        std::string const& body) {
    std::string result;
    try {
        Post new_post = parse_body(body);
        std::string new_post_id  = _db.create_post(new_post);
        result = "{'new_post_id': '" + new_post_id + "'}";
    } catch(std::exception const& e) {
        result = "{'error': 'failed to create post'}";
    }
    return result;
}

std::string Handlers::add_like(const std::string &id_request, const std::map<std::string, size_t> &args) {
    std::string post_id = std::to_string(args.at("post_id"));
    std::string user_id = std::to_string(args.at("user_id"));
    return _db.add_like_by_id(post_id, user_id);
}

std::string Handlers::del_like(const std::string &id_request, const std::map<std::string, size_t> &args) {
    std::string post_id = std::to_string(args.at("post_id"));
    std::string user_id = std::to_string(args.at("user_id"));
    return _db.del_like_by_id(post_id, user_id);
}

