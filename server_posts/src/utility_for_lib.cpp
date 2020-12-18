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
    }

    Post post(
            boost::lexical_cast<std::uint16_t>(result["post_id"]),
            boost::lexical_cast<std::uint16_t>(result["user_id"]),
            result["creation_date"],
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


RequestWithoutBody parse_without_body(const std::vector<std::string>& args) {
    std::string id_request = args[0];
    std::string url_request = args[1];

    std::vector<std::string> url_param = split(url_request, "?");
    std::string command = url_param[0];
    std::map<std::string, size_t> parameters;

    if (url_param.size() == 2) {  // если query string есть
        std::string query_string = url_param[1];
        parameters = get_url_parameters(split(query_string, "=&"));
    }
    return RequestWithoutBody(id_request, command, parameters);
}


RequestWithBody parse_with_body(const std::vector<std::string>& args) {
    std::string id_request = args[0];
    std::string url_request = args[1];
    std::string body_request = args[2];

    std::vector<std::string> url_param = split(url_request, "?");
    std::string command = url_param[0];
    std::map<std::string, size_t> parameters;

    if (url_param.size() == 2) {  // если query string есть
        std::string query_string = url_param[1];
        parameters = get_url_parameters(split(query_string, "=&"));
    }
    return RequestWithBody(id_request, command, parameters, body_request);
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




//try {
//    dispatch("123 /posts/all/ {}");
//} catch(boost::bad_lexical_cast &) {
//    std::cout << "bad" << std::endl;
//}

#endif //MAIN_TP_UTILITY_H
