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

std::map<std::string, std::string> parser_json(std::string& request) {
    try {
        ptree pt;
        if (!request.empty()) {
            std::stringstream stream_request(request);
            boost::property_tree::read_json(stream_request, pt);
            std::map<std::string, std::string> result;
            for (ptree::const_iterator it = pt.begin(); it != pt.end(); ++it) {
                result[std::string(it->first)] = it->second.get_value<std::string>();
            }
            return result;
        }
        return {};
    }
    catch (std::exception& e) {
        return {};
    }
}


Post parse_body(std::string& body_str) {
    std::map<std::string, std::string> result = parser_json(body_str);
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

std::string post_to_json(const Post& p) {
    try {
        ptree pt;
        pt.put ("post_id", std::to_string(p.post_id));
        pt.put ("creator_id", std::to_string(p.creator_id));
        pt.put ("creation_date", p.creation_date);
        pt.put ("title", p.title);
        pt.put ("text", p.text);
        pt.put ("attach", p.attach);
        pt.put ("amount_likes", std::to_string(p.amount_likes));
        pt.put ("liked_users", p.liked_users);
        std::ostringstream buf;
        write_json (buf, pt, false);
        return buf.str();
    }
    catch (std::exception& e) {
        return "{}";
    }
}


std::string vec_posts_to_json(std::vector<Post>& vec_posts) {
    std::string res;
    for (auto& i : vec_posts) {
        res += post_to_json(i) + "\n";
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


std::vector<std::string> get_friends_id(std::string& user_id) {
    std::vector<std::string> empty_vec(0);
    try {
        std::string request = "5\n"
                              "0\n"
                              "/api/friends/get_all/\n"
                              "\n"
                              "{\n"
                              "  \"user_1\": \"" + user_id +"\"\n}";

        boost::asio::io_service service;


        // указать порт http сервера
        boost::asio::ip::tcp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 9999);
        ip::tcp::socket socket(service);
        socket.connect(end);
        boost::asio::write(socket, boost::asio::buffer(request));
        service.run();

        char response[2048];
        socket.read_some(boost::asio::buffer(response, 2048));
        std::string answer = response;

        // парсинг
        ptree pt;
        std::stringstream stream_request(answer);
        boost::property_tree::read_json(stream_request, pt);

        auto response_from_json = pt.get<std::string>("response");

        if (response_from_json == "true") {
            std::vector<std::string> res;
            for (auto& item : pt.get_child("data")) {
                res.push_back(item.second.get_value<std::string>());
            }
            return res;
        } else {
            return empty_vec;
        }
    }
    catch (std::exception& e) {
        return empty_vec;
    }
}

#endif //MAIN_TP_UTILITY_H
