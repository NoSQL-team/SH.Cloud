
#include <iostream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include "UsersDatabase.h"
#include <pqxx/pqxx>

using boost::asio::ip::tcp;
using std::string;
using boost::property_tree::ptree;

using std::string;

class UsersDatabase {
public:
    UsersDatabase();
    ~UsersDatabase();
    string insert_user(std::map<string, string>& users_data);
    string data_user(int id);
    string all_users();
    string delete_user(int id);
    string update_data(std::map<string, string> data);
private:
    pqxx::connection data_base_;
};


//std::map<string, string> parser_json(string& request) {
//    ptree pt;
//    if (!request.empty()){
//        std::stringstream stream(request);
//        boost::property_tree::read_json(stream, pt);
//        std::map<string, string> result;
//        ptree::const_iterator end = pt.end();
//        for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
//            result[std::string(it->first)] = it->second.get_value<string>();
//        }
//        return result;
//    }
//    return {};
//}
//
//int handle_request(string& request) {
//    std::stringstream stream(request);
//    int number_request, priority;
//    string space;
//    stream >> number_request;
//    stream >> priority;
//    stream >> space;
//    return number_request;
//}

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

string insert_user(std::map<string, string>& users_data) {
    string sql_requst("INSERT INTO Users VALUES(");
    int i = 0;
    for(auto& string : users_data) {
        if (i != 0)
            sql_requst += ", ";
        if (string.first != "AId") {
            sql_requst += "\'" + string.second + "\'";
        } else {
            sql_requst += string.second;
        }
        i = 1;
    }
    sql_requst += ")";
    return sql_requst;
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
   string example = "{\n"
                    "  \"Id\": 5,\n"
                    "  \"firstname\": \"lera\",\n"
                    "  \"lastname\": \"guseva\",\n"
                    "  \"nickname\": \"lerakrya\",\n"
                    "  \"email\": \"lerakrya8@gmail.com\",\n"
                    "  \"photo\": \"lera.png\"\n"
                    "}";

   std::stringstream stream(example);
//    handle_request(example);
//    for(auto& v: result) {
//        std::cout << v.first << " " << v.second << std::endl;
//    }

//    string request = "add\nlera";
//    request = insert_user(result);
//    std::cout << request << std::endl;

    UsersDatabase database;

    auto m = parser_json(stream);
    database.insert_user(m);

    return 0;
}

