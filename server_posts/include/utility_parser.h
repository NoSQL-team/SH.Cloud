//
// Created by steve on 09.12.2020.
//

#ifndef SERVER_POSTS_UTILITY_PARSER_H
#define SERVER_POSTS_UTILITY_PARSER_H

#include "../include/types.h"
#include "../include/post.h"




class RequestWithBody {
public:
    RequestWithBody(
            std::string id_request,
            std::string command,
            std::map<std::string, size_t> args,
            Post body) :
            id_request(std::move(id_request)),
            command(std::move(command)),
            args(std::move(args)),
            body(std::move(body)) {}

    std::string id_request;
    std::string command;
    std::map<std::string, size_t> args;
    Post body;
};

class RequestWithoutBody {
public:
    RequestWithoutBody(
            std::string id_request,
            std::string command,
            std::map<std::string, size_t> args
    ) :
            id_request(std::move(id_request)),
            command(std::move(command)),
            args(std::move(args)) {}

    std::string id_request;
    std::string command;
    std::map<std::string, size_t> args;
};



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

std::map<std::string, size_t> get_url_parameters(const string_group& vector_parameters) {
    std::map<std::string, size_t> result;
    if (vector_parameters.size() % 2 != 0) {
        std::cout << "bad vector_parameters" << std::endl;
    }
    for (size_t i = 0; i < vector_parameters.size() - 1; i += 2) {
        result[vector_parameters[i]] = boost::lexical_cast<std::uint16_t>(vector_parameters[i + 1]);
    }
    return result;
}


RequestWithoutBody parse_without_body(const string_group& args) {
    std::string id_request = args[0];
    std::string url_request = args[1];

    string_group url_param = split(url_request, "?");
    std::string command = url_param[0];
    std::map<std::string, size_t> parameters;

    if (url_param.size() == 2) {  // если query string есть
        std::string query_string = url_param[1];
        parameters = get_url_parameters(split(query_string, "=&"));
    }
    return RequestWithoutBody(id_request, command, parameters);
}


RequestWithBody parse_with_body(const string_group& args) {
    std::string id_request = args[0];
    std::string url_request = args[1];
    std::string body_request = args[2];

    string_group url_param = split(url_request, "?");
    std::string command = url_param[0];
    std::map<std::string, size_t> parameters;

    if (url_param.size() == 2) {  // если query string есть
        std::string query_string = url_param[1];
        parameters = get_url_parameters(split(query_string, "=&"));
    }
    return RequestWithBody(id_request, command, parameters, parse_body(body_request));
}

// "123 /posts/upd/?user_id=3&post_id=7"
// "123 /posts/all/"
// "123 /posts/upd/?user_id=3&post_id=7 {\"post_id\":0,\"user_id\":0,\"creation_date\":\"2016-08-29T09:12:33.001Z\",\"title\":\"string\",\"text\":\"string\",\"attach\":\"string\"}"

//try {
//    dispatch("123 /posts/all/ {}");
//} catch(boost::bad_lexical_cast &) {
//    std::cout << "some bad" << std::endl;
//}

#endif //SERVER_POSTS_UTILITY_PARSER_H
