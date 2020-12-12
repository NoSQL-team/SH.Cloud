#pragma once

#include <iostream>
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
using namespace std::placeholders;

using boost::property_tree::ptree;

using string_group = std::vector<std::string>;

struct dispatcher_entry {
    std::size_t const args; // количество аргументов
    // bool body_required;
    std::function<std::string (const std::string& , const std::map<std::string, size_t>& )> const handler;
};

struct dispatcher_entry_with_body {
    std::size_t const args; // количество аргументов
    // bool body_required;
    std::function<std::string (const std::string& , const std::map<std::string, size_t>&, const std::string& )> const handler;
};

// map обработчиков команд (название - диспетчер)
using dispatcher_type = std::map<std::string, dispatcher_entry>;
using dispatcher_type_with_body = std::map<std::string, dispatcher_entry_with_body>;


using separator = boost::char_separator<char>;
using tokenizer = boost::tokenizer<separator>;
// вспомогательная функция, которая разбивает заданную строку на вектор строк
// drop - символ по которому разбивается строка
string_group split(std::string const& string, const char *drop) {
    string_group group;
    for(auto&& str : tokenizer(string, separator(drop))) {
        group.emplace_back(str);
    }
    return group;
}
