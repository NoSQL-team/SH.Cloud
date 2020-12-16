
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>
#include "UsersDatabase.h"

using boost::asio::ip::tcp;
using std::string;
using boost::property_tree::ptree;

using std::string;


std::map<string, string> parser_json(string& request) {
    try {
        ptree pt;
        if (!request.empty()) {
            std::stringstream stream_request(request);
            boost::property_tree::read_json(stream_request, pt);
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
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp create_user c.62 " << e.what();
    }
}

void  handle_request(string& request) {
    auto num = request.find('\n');
    string num_request = request.substr(0, num);

    auto find_method = request.find('\n', num + 1);
    string api_method = request.substr(num + 1, find_method - num - 1);
    const string str = "api/users/";
    string method;

    int num_slash = std::count(api_method.begin(), api_method.end(), '/');
    int id_exists = -1;
    if (num_slash == 4 ) {
        string find_id = api_method.substr(api_method.find_last_of('/', api_method.size() - 2) + 1);
        find_id.pop_back();
        id_exists = atoi(find_id.c_str());
        method = api_method.substr(str.size(), api_method.find_last_of('/', api_method.size() - 2) - str.size());
    }
    else {
        method = api_method.substr(str.size());
        method.pop_back();
    }

    int id_user = atoi(request.substr(find_method + 1, request.find("\n\n") - find_method - 1).c_str());

    auto fjson = request.find_first_of('{');
    string json_body = "";
    if (fjson != std::string::npos) {
        json_body = request.substr(fjson);
    }

    std::map<string, string> parser = parser_json(json_body);

    int data = atoi(method.c_str());

    std::cout << "num_request: " << num_request << std::endl;
    std::cout << "method: " << method << std::endl;
    std::cout << "user_id: " << id_user << std::endl;
    std::cout << "json_body: " << json_body << std::endl;
    std::cout << "id_exists: " << id_exists << std::endl;
    std::cout << "data: " << data << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
   string example = "123\napi/users/create/\n4\n\n{\n"
                    "  \"id\": 5,\n"
                    "  \"firstname\": \"lera\",\n"
                    "  \"lastname\": \"guseva\",\n"
                    "  \"nickname\": \"lerakrya\",\n"
                    "  \"email\": \"lerakrya8@gmail.com\",\n"
                    "  \"photo\": \"lera.png\"\n"
                    "}";

   string example1 = "123\napi/users/exists/5/\n4\n\n";
   string example2 = "123\napi/users/update/\n4\n\n{\n"
                     "  \"id\": 5,\n"
                     "  \"lastname\": \"guseva\",\n"
                     "  \"nickname\": \"lerakrya\"\n"
                     "}";
   string example3 = "123\napi/users/all/\n4\n\n";
   string example4 = "123\napi/users/5/\n4\n\n";
   string example5 = "123\napi/users/lerakrya/\n4\n\n";

   std::stringstream stream(example);

   handle_request(example);
   handle_request(example1);
   handle_request(example2);
   handle_request(example3);
   handle_request(example4);
   handle_request(example5);


//    UsersDatabase database;

//    auto m = parser_json(stream);
//    database.insert_user(m);

    return 0;
}

