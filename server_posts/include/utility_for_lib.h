//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_UTILITY_H
#define MAIN_TP_UTILITY_H

#include "../include/types.h"
#include "../include/post.h"
#include <vector>

// десерелизует json
std::map<std::string, std::string> parser_json(std::string& request);

// десерелизует боди из json в объект Post
Post parse_body(std::string& body_str);

// получение параметров из query string
std::map<std::string, size_t> get_url_parameters(const std::vector<std::string>& vector_parameters);

// парсинг запроса без боди
RequestWithoutBody parse_without_body(const std::vector<std::string>& args);

// парсинг запроса с боди
RequestWithBody parse_with_body(const std::vector<std::string>& args);

// сериализация вектора постов в json
std::string vec_posts_to_json(std::vector<Post>& vec_posts);

// сериализация одного поста в json
std::string post_to_json(const Post& p);

// разбивает строку на вектор по символам из переданного множества drop
std::vector<std::string> split(std::string const& string, const char *drop);


// трим алгоритм, убирает пробелы и знаки табуляции в начале и конце строки
std::string trim(const std::string& str,
                 const std::string& whitespace = " \t");


// убирает лишние пробелы и знаки табуляции
std::string reduce(std::string& str,
                   const std::string& fill = " ",
                   const std::string& whitespace = " \t");


// проверяем авторизирован ли пользователь
bool is_authorized(const std::string& user_id);

// проеверяем есть ли право что-либо делать у пользователя
bool check_access(bool required_auth, bool is_authorized);

// получаем вектор из id друзей пользователя user_id
std::vector<std::string> get_friends_id(std::string& user_id);

#endif //MAIN_TP_UTILITY_H
