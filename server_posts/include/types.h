//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_TYPES_H
#define MAIN_TP_TYPES_H

#include <iostream>
#include <string>
#include <map>
#include <optional>
#include <queue>
#include <functional>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>


namespace io = boost::asio;
namespace ip = io::ip;
using tcp = ip::tcp;
using error_code = boost::system::error_code;
using boost::property_tree::ptree;


struct dispatcher_entry {
    std::size_t const args = 0; // количество аргументов
    bool required_auth;  // нужна ли авторизация
    std::function<std::string (const std::string &, const std::map<std::string, size_t> &)> const handler;


};

struct dispatcher_entry_with_body {
    std::size_t const args = 0; // количество аргументов
    bool required_auth;  // нужна ли авторизация
    std::function<std::string (const std::string &, const std::map<std::string, size_t> &, std::string &)> const handler;
};



class RequestWithBody {
public:
    RequestWithBody(
            std::string id_request,
            std::string command,
            bool is_authorized,
            std::map<std::string, size_t> args,
            std::string body) :
                id_request(std::move(id_request)),
                command(std::move(command)),
                is_authorized(is_authorized),
                args(std::move(args)),
                body(std::move(body)) {}

    std::string id_request;
    std::string command;
    bool is_authorized;
    std::map<std::string, size_t> args;
    std::string body;
};


class RequestWithoutBody {
public:
    RequestWithoutBody(
            std::string id_request,
            std::string command,
            bool is_authorized,
            std::map<std::string, size_t> args) :
                id_request(std::move(id_request)),
                command(std::move(command)),
                is_authorized(is_authorized),
                args(std::move(args)) {}

    std::string id_request;
    std::string command;
    bool is_authorized;
    std::map<std::string, size_t> args;
};

#endif //MAIN_TP_TYPES_H
