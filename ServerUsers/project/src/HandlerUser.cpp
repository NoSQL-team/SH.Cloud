//
// Created by lerakry on 04.12.2020.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include <boost/log/trivial.hpp>
#include "HandlerUser.h"
#include <iostream>

using std::string;
using boost::property_tree::ptree;

using namespace boost::asio;

std::map<string, string> HandlerUser::parser_json(string& request) {
    try {
        ptree pt;
        if (!request.empty()) {
            std::stringstream stream_request(request);
            boost::property_tree::read_json(stream_request, pt);
            std::map<string, string> result;
            for (ptree::const_iterator it = pt.begin(); it != pt.end(); ++it) {
                string field = std::string(it->first);
                if (std::string(it->first) == "id") {
                    field = "Aid";
                }
                else if (std::string(it->first) == "firstname") {
                    field = "Bfirstname";
                }
                else if (std::string(it->first) == "lastname") {
                    field = "Clastname";
                }
                else if (std::string(it->first) == "nickname") {
                    field = "Dnickname";
                }
                else if (std::string(it->first) == "email") {
                    field = "Eemail";
                }
                else if (std::string(it->first) == "photo") {
                    field = "Fphoto";
                }
                result[field] = it->second.get_value<string>();
            }
            return result;
        }
        return {};
    }
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp parser_json c.16 " << e.what();
    }
    return {};
}

void HandlerUser::handle_request(string& request) {
    // Номер запроса (для отправки ответа)
    auto num = request.find('\n');
    int num_request = atoi(request.substr(0, num).c_str());
    
    auto find_method = request.find('\n', num + 1);
    string api_method = request.substr(num + 1, find_method - num - 1);
    const string str = "/api/users/";
    // название метода или id пользователя или никнейм
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
    }
    method.pop_back();
    int id_user = atoi(request.substr(find_method + 1, request.find("\n\n") - find_method - 1).c_str());

    auto fjson = request.find_first_of('{');
    string json_body = "";
    if (fjson != std::string::npos) {
        json_body = request.substr(fjson);
    }
    
    std::map<string, string> parse_json = parser_json(json_body);
    
    int data_id = atoi(method.c_str());

    if (method == "create") {
        create_user(num_request, parse_json, id_user);
    }
    else if (method == "update") {
        for (const auto& [el, el1] : parse_json) {
            std::cout << el << " " << el1 << std::endl;
        }
        update_data(num_request, parse_json, id_user);
    }
    else if (method == "all") {
        all_users(num_request);
    }
    else if (method == "exists") {
        is_exist(num_request, id_exists);
    }
    else if (data_id != 0) {
        data_user(data_id, num_request);
    }
    else {
        id_by_nick(num_request, method);
    }
}

void HandlerUser::create_user(int number_request, const std::map<string, string>& data_user, int user_id) const {
    try {
    	std::string request = "/api/auth/add/\n\n{\n  \"user_id\": ";
        request += std::to_string(data_base_.get_id());
    	request += ",\n  \"password\": \"" + data_user.at("password") + "\",\n  \"username\": \"" + data_user.at("Dnickname") + "\"\n}\r";

    	boost::asio::io_service service;
		boost::asio::ip::tcp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 9999);
		ip::tcp::socket socket(service);
		socket.connect(end);
		service.run();

        boost::asio::write(socket, boost::asio::buffer(request));
		boost::asio::streambuf response;

        read_until(
            socket,
            response,
            '\r'
        );

        std::string s( (std::istreambuf_iterator<char>(&response)), std::istreambuf_iterator<char>() );
		std::map<string, string> parse_answer = parser_json(s);

		if (parse_answer.at("response") != "ok") {
			string str_result = std::to_string(number_request) + "\n";
			str_result += "{\n  \"response\": true \n}\r";
			session_.send_answer(str_result);
		}
		else {
			int result = data_base_.insert(data_user, user_id);
			string str_result = std::to_string(number_request) + "\n";
			str_result += "{\n \"response\": " + std::to_string(result) + "\n}\r";
			session_.send_answer(str_result);
		}
    }
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp create_user c.110 " << e.what();
    }
}

void HandlerUser::data_user(int id, int number_request) const {
    try {
        data_base_.data_user(id);
        string result = std::to_string(number_request) + "\n";
        string new_result = data_base_.data_user(id);
        if (result == "No user") {
            result += "{\n \"response\": \"false\"\n}";
        } else {
            result += new_result;
        }
        session_.send_answer(result);
    }
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp data_user c.79 " << e.what();
    }
}

void HandlerUser::all_users(int number_request) const {
    try {
        data_base_.all_users();
        string result = std::to_string(number_request) + "\n";
        string new_result = data_base_.all_users();
        if (result == "No users") {
            result += "{\n \"response\": \"false\"\n}";
        } else {
            result += new_result;
        }
        session_.send_answer(result);
    }
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp all_users c.96 " << e.what();
    }
}

void HandlerUser::update_data(int number_request, const std::map<string, string>& data_user, int user_id) const {
    try {
        int result = data_base_.update(data_user, user_id);
        string str_result = std::to_string(number_request) + "\n";
        str_result += "{\n \"response\": " + std::to_string(result) + "\n}";
        session_.send_answer(str_result);
    }
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp change_user_data c.130 " << e.what();
    }
}

void HandlerUser::is_exist(int number_request, int id_user) const {
    try {
        int result = data_base_.exist(id_user);
        string str_result = std::to_string(number_request) + "\n";
        str_result += "{\n \"response\": " + std::to_string(result) + "\n}";
        session_.send_answer(str_result);
    }
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp is_exist c.177 " << e.what();
    }
}

void HandlerUser::id_by_nick(int number_request, string& nickname) {
    try {
        data_base_.all_users();
        string result = std::to_string(number_request) + "\n";
        string new_result = data_base_.all_users();
        if (result == "No user") {
            result += "{\n \"response\": \"false\"\n}";
        } else {
            result += new_result;
        }
        session_.send_answer(result);
    }
    catch (std::exception& e) {
//        BOOST_LOG_TRIVIAL(error) << "HandlerUser.cpp id_by_nick c.189 " << e.what();
    }
}
