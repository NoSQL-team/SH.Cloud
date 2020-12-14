//
// Created by steve on 07.12.2020.
//

#ifndef POSTS_HANDLERS_H
#define POSTS_HANDLERS_H

#include "types.h"
#include "database.h"
#include "../include/utility_parser.h"

class Handlers {

public:S
Handlers() : _db() {};

std::string for_user(const std::string& id_request, const std::map<std::string, size_t>& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request +
                         " posts for user with id: " + std::to_string(args.at("user_id"));
    return result;
}

std::string all_posts(const std::string& id_request, const std::map<std::string, size_t>& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request + " all posts\n";

    std::vector<Post> vec_posts = _db.get_all_posts();
    std::string posts = vec_posts_to_str(vec_posts);
    return result + posts;
}

std::string user_posts(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request +
                         " user`s posts with id: " + std::to_string(args.at("user_id"));
    return result;
}

std::string one_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request +
                         " post with id: " + std::to_string(args.at("post_id"));
    return result;
}
std::string delete_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request +
                         " deleting a post with id: " + std::to_string(args.at("post_id")) +
                         " by a user with id: " + std::to_string(args.at("user_id"));
    return result;
}

std::string create_post(std::string const& id_request,
                        std::map<std::string, size_t> const& args,
                        std::string const& body) {
    // TODO: реализовать работу с БД
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
    return result;
}

std::string update_post(std::string const& id_request,
                        std::map<std::string, size_t> const& args,
                        std::string const& body) {
    // TODO: реализовать работу с БД
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

private:
    PostsDataBase _db;

};

#endif //POSTS_HANDLERS_H