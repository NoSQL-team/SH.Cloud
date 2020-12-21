//
// Created by steve on 18.12.2020.
//

//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_UTILITY_H
#define MAIN_TP_UTILITY_H

#include "../include/utility_for_lib.h"
#include "../include/types.h"
#include "../include/post.h"



using separator = boost::char_separator<char>;
using tokenizer = boost::tokenizer<separator>;
// вспомогательная функция, которая разбивает заданную строку на вектор строк
// drop - символ по которому разбивается строка
std::vector<std::string> split(std::string const& string, const char *drop) {
    std::vector<std::string> result;
    for(auto&& str : tokenizer(string, separator(drop))) {
        result.emplace_back(str);
    }
    return result;
}



Post parse_body(const std::string& body_str) {
    std::stringstream ss;
    ss << body_str;

    std::map<std::string, std::string> result;
    ptree pt;
    boost::property_tree::read_json(ss, pt);
    // if (pt.empty()) {std::cout << "bad body" << std::endl;}
    for (ptree::const_iterator it = pt.begin(); it != pt.end(); ++it) {
        result[std::string(it->first)] = it->second.get_value<std::string>();
        // std::cout << std::string(it->first) << ' ' <<  << std::endl;
    }

    Post post(
            boost::lexical_cast<std::uint16_t>(result["user_id"]),
            result["title"],
            result["text"],
            result["attach"]
    );
    return post;
}

std::map<std::string, size_t> get_url_parameters(const std::vector<std::string>& vector_parameters) {
    std::map<std::string, size_t> result;
    if (vector_parameters.size() % 2 != 0) {
        std::cout << "bad vector_parameters" << std::endl;
    }
    for (size_t i = 0; i < vector_parameters.size() - 1; i += 2) {
        result[vector_parameters[i]] = boost::lexical_cast<std::uint16_t>(vector_parameters[i + 1]);
    }
    return result;
}


bool is_authorized(const std::string& user_id) {
    return user_id != "-1";
}

RequestWithoutBody parse_without_body(const std::vector<std::string>& args) {
    std::string id_request = args[0];
    std::string url_request = args[1];
    std::string id_auth = args[2];  // -1 или айди пользователя

    std::vector<std::string> url_param = split(url_request, "?");
    std::string command = url_param[0];
    std::map<std::string, size_t> parameters;

    if (url_param.size() == 2) {  // если query string есть
        std::string query_string = url_param[1];
        parameters = get_url_parameters(split(query_string, "=&"));
    }
    return RequestWithoutBody(id_request, command, is_authorized(id_auth), parameters);
}


RequestWithBody parse_with_body(const std::vector<std::string>& args) {
    std::string id_request = args[0];
    std::string url_request = args[1];
    std::string id_auth = args[2];
    std::string body_request = args[3];

    std::vector<std::string> url_param = split(url_request, "?");
    std::string command = url_param[0];
    std::map<std::string, size_t> parameters;

    if (url_param.size() == 2) {  // если query string есть
        std::string query_string = url_param[1];
        parameters = get_url_parameters(split(query_string, "=&"));
    }
    return RequestWithBody(id_request, command, is_authorized(id_auth), parameters, body_request);
}

std::string one_post_to_str(Post& one_post) {
    boost::format parsed_body = (boost::format(
            "post_id: %1%,\n"
            " creator_id: %2%,\n"
            " creation_date: %3%,\n"
            " title: %4%,\n"
            " text: %5%,\n"
            " attach: %6%\n\n"
    )
                                 % one_post.post_id
                                 % one_post.creator_id
                                 % one_post.creation_date
                                 % one_post.title
                                 % one_post.text
                                 % one_post.attach);
    return boost::str(parsed_body);
}


std::string vec_posts_to_str(std::vector<Post>& vec_posts) {
    std::string res;
    for (auto& i : vec_posts) {
        res += one_post_to_str(i);
    }
    return res;
}


std::string trim(const std::string& str,
                 const std::string& whitespace = " \t") {
    const auto str_begin = str.find_first_not_of(whitespace);
    if (str_begin == std::string::npos){
        return "";
    }
    const auto str_end = str.find_last_not_of(whitespace);
    const auto str_range = str_end - str_begin + 1;

    return str.substr(str_begin, str_range);
}

std::string reduce(std::string& str,
                   const std::string& fill = " ",
                   const std::string& whitespace = " \t") {
    auto result = trim(str, whitespace);
    auto begin_space = result.find_first_of(whitespace);
    while (begin_space != std::string::npos) {
        const auto end_space = result.find_first_not_of(whitespace, begin_space);
        const auto range = end_space - begin_space;

        result.replace(begin_space, range, fill);

        const auto new_start = begin_space + fill.length();
        begin_space = result.find_first_of(whitespace, new_start);
    }

    return result;
}

void print_post(const Post& p) {
    std::cout << "post_id: " << p.post_id << std::endl;
    std::cout << "creator_id: " << p.creator_id << std::endl;
    std::cout << "creation_date: " << p.creation_date << std::endl;
    std::cout << "title: " << p.title << std::endl;
    std::cout << "text: " << p.text << std::endl;
    std::cout << "attach: " << p.attach << std::endl;
    std::cout << "amount_likes: " << p.amount_likes << std::endl;
    std::cout << "liked_users: " << p.liked_users << std::endl << std::endl;
}



//try {
//    dispatch("123 /posts/all/ {}");
//} catch(boost::bad_lexical_cast &) {
//    std::cout << "bad" << std::endl;
//}

#endif //MAIN_TP_UTILITY_H
