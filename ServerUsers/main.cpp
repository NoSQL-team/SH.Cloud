
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>
#include "UsersDatabase.h"

using boost::asio::ip::tcp;
using std::string;
using boost::property_tree::ptree;

using std::string;


std::map<string, string> parser_json(std::stringstream& request) {
    ptree pt;
    if (!request.str().empty()) {
        boost::property_tree::read_json(request, pt);
        std::map<string, string> result;
        ptree::const_iterator end = pt.end();
        char alf = 'A';
        for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
            result[alf + std::string(it->first)] = it->second.get_value<string>();
            alf++;
        }
        return result;
    }
    return {};
}

int insert_user(std::map<string, string>& users_data) {
    string sql_request("INSERT INTO Users VALUES(");
    int i = 0;
    for(auto& string : users_data) {
        if (i != 0)
            sql_request += ", ";
        if (string.first.substr(1) != "Id") {
            sql_request += "\'" + string.second + "\'";
        } else {
            sql_request += string.second;
        }
        i = 1;
    }
    sql_request += ")";
    std::cout << sql_request << std::endl;
    return 200;
}

int update_data(const std::map<string, string>& data) {
    string sql_request("UPDATE Users SET ");

    int i = 0;
    for(const auto& v : data) {
        i++;
        if (i == 1)
            continue;
        if (i != 2 ) {
            sql_request += ", ";
        }
        sql_request += v.first.substr(1) + "=" + v.second;
    }

    sql_request += " WHERE Id=" + data.at("AId");
    std::cout << sql_request << std::endl;
    return 200;
}

void  handle_request(string& request) {
    std::stringstream stream_request(request);
    int number_request, priority;
    string method;
    stream_request >> number_request;
    stream_request >> priority;
    stream_request >> method;
    std::map<string, string> parse_request = parser_json(stream_request);
    string str;
    if (method == "create") {
        str = insert_user(parse_request);
    }
    std::cout << str << std::endl;
}

int main(int argc, char* argv[])
{
   string example = "5\n0\ncreate\n{\n"
                    "  \"id\": 5,\n"
                    "  \"firstname\": \"lera\",\n"
                    "  \"lastname\": \"guseva\",\n"
                    "  \"nickname\": \"lerakrya\",\n"
                    "  \"email\": \"lerakrya8@gmail.com\",\n"
                    "  \"photo\": \"lera.png\"\n"
                    "}";

   std::stringstream stream(example);

//    UsersDatabase database;

    auto m = parser_json(stream);
    int k = insert_user(m);
//    database.insert_user(m);

    return 0;
}

