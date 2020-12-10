//
// Created by steve on 07.12.2020.
//

#ifndef POSTS_HANDLERS_H
#define POSTS_HANDLERS_H

#include "types.h"
#include "database.h"



std::string for_user(const std::string& id_request, const std::map<std::string, size_t>& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request +
                         " posts for user with id: " + std::to_string(args.at("user_id"));
    return result;
}

std::string all_posts(const std::string& id_request, const std::map<std::string, size_t>& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request + " all posts";
    return result;
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

std::string create_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request +
                         " creating a post by a user with id: " + std::to_string(args.at("user_id"));
    return result;
}

std::string update_post(std::string const& id_request, std::map<std::string, size_t> const& args) {
    // TODO: реализовать работу с БД
    std::string result = "id_request: " + id_request +
                         " changing a post with id: " + std::to_string(args.at("post_id")) +
                         " by a user with id: " + std::to_string(args.at("user_id"));
    return result;
}

#endif //POSTS_HANDLERS_H
