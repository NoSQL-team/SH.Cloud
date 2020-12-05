//
// Created by lerakry on 04.12.2020.
//

#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../includes/HandlerUser.h"

using std::string;
using boost::property_tree::ptree;

std::map<string, string> HandlerUser::parser_json(std::stringstream& request) {
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
void HandlerUser::handle_request(string& request) {
    std::stringstream stream_request(request);
    int number_request, priority;
    string method;
    stream_request >> number_request;
    stream_request >> priority;
    stream_request >> method;
    std::map<string, string> parse_request = parser_json(stream_request);
    string str;
    if (method == "create") {
        create_user(parse_request);
    }
    else if (method == "data") {
        auto id = std::atoi(parse_request["id"].c_str());
        data_user(id);
    }
    else if (method == "all") {
        all_users();
    }
    else if (method == "delete") {
        auto id = std::atoi(parse_request["id"].c_str());
        delete_user(id);
    }
    else if (method == "change") {
        change_user_data(parse_request);
    }
}
void HandlerUser::create_user(std::map<string, string>& data_user) {
    data_base_.insert_user(data_user);
}
void HandlerUser::data_user(int id) {
    data_base_.data_user(id);
}
void HandlerUser::all_users() {
    data_base_.all_users();
}
void HandlerUser::delete_user(int id) {
    data_base_.delete_user(id);
}
void HandlerUser::change_user_data(std::map<string, string>& user_data) {
    data_base_.update_data(user_data);
}


