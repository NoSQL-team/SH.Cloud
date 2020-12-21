//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_UTILITY_H
#define MAIN_TP_UTILITY_H

#include "../include/types.h"
#include "../include/post.h"



Post parse_body(const std::string& body_str);

std::map<std::string, size_t> get_url_parameters(const std::vector<std::string>& vector_parameters);


RequestWithoutBody parse_without_body(const std::vector<std::string>& args);


RequestWithBody parse_with_body(const std::vector<std::string>& args);

std::string one_post_to_str(Post& one_post);

std::string vec_posts_to_str(std::vector<Post>& vec_posts);

std::vector<std::string> split(std::string const& string, const char *drop);

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t");

std::string reduce(std::string& str,
                   const std::string& fill = " ",
                   const std::string& whitespace = " \t");

void print_post(const Post& p);

bool is_authorized(const std::string& user_id);



#endif //MAIN_TP_UTILITY_H
