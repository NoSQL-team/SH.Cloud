//
// Created by Andrew Kireev on 03.12.2020.
//


#include "requst_handler.h"
#include <iostream>

namespace tcp_network {

	RequestHandler::RequestHandler(boost::asio::io_service& io_service, FriendsDataBase& database,
								   std::shared_ptr<Session> session,
								   std::map<std::string, std::string>& request) :
								io_service_(io_service), session_(std::move(session)), database_(database),
								request_(request) {}

	void RequestHandler::handle_request() {
		if (request_.count("type") && request_["type"] == "add") {
			handle_add();
		} else if (request_.count("type") && request_["type"] == "is_friend") {
			handle_is_friend();
		} else if (request_.count("type") && request_["type"] == "delete") {
			handle_delete();
		} else if (request_.count("type") && request_["type"] == "get_all") {
			handle_get_all_friends();
		} else if (request_.count("type") && request_["type"] == "get_stat") {
			handle_get_statistic();
		}
	}

	void RequestHandler::handle_add() {

		bool result = false;
		// if (request_["user_1"] == request_["auth"]) {
			result = database_.add_friend(std::atoi(request_["user_1"].c_str()),
						std::atoi(request_["user_2"].c_str()));
		// }

		std::string response = (request_["number"] + '\n' + form_post_response(result) + '\r');
		session_->send_response(response);
	}

	void RequestHandler::handle_get_all_friends() {
		std::vector<int> all_friends = database_.get_all_friends(
				std::atoi(request_["user_1"].c_str()));

		std::string string_respones = (request_["number"] + '\n' + form_get_fr_response(all_friends) + '\r');
		session_->send_response(string_respones);
	}

	void RequestHandler::handle_delete() {
		bool result = false;
		
		// if (request_["user_1"] == request_["auth"]) {
			result = database_.delete_friend(std::atoi(request_["user_1"].c_str()),
										std::atoi(request_["user_2"].c_str()));
		// }
		
		std::string response = (request_["number"] + '\n' + form_post_response(result) + '\r');
		session_->send_response(response);
	}

	std::string request_are_friends() {
		std::string response = "{"
							   " \"isFriends\": true,"
							   " \"isHeSub\": false,"
							   " \"isWeSub\": false,"
							   " \"isNotConf\": false";

		return response;
	}

	std::string request_isNotConf() {
		std::string response = "{"
							   " \"isFriends\": false,"
							   " \"isHeSub\": false,"
							   " \"isWeSub\": false,"
							   " \"isNotConf\": true";

		return response;
	}

	void RequestHandler::handle_is_friend() {
		int result = database_.is_friend(std::atoi(request_["user_1"].c_str()),
										  std::atoi(request_["user_2"].c_str()));

		std::string response = "{ \"isWeSub\": ";
		if (result == 1 || result == 3)
			response += "true,";
		else
			response += "false,";
		response += " \"isHeSub\": ";
		if (result == 2 || result == 3)
			response += "true,";
		else
			response += "false,";
		response += " \"isFriends\": ";
		response += "false,";
		response += " \"isNotConf\": ";
		response += "false";
		if (result == 3)
			response = request_are_friends();
		if (result == 0)
			response = request_isNotConf();
		response += "\n}";
		std::string final_response = (request_["number"] + '\n' + response + '\r');
		session_->send_response(final_response);
	}

	void RequestHandler::handle_get_statistic() {
		auto result = database_.get_statistic(std::atoi(request_["user_1"].c_str()));
		std::string response = (request_["number"] + '\n' + form_stat_response(result) + '\r');
		session_->send_response(response);
	}

	std::string RequestHandler::form_post_response(int result) {
		std::string response = "{\"response\": ";
		if (result)
			response += "true";
		else
			response += "false";
		response += " }";
		return response;
	}

	std::string RequestHandler::form_stat_response(std::tuple<int, int, int> amount) {
		std::stringstream response;
		response << "{\"response\": ";
		response << "\"true\"";
		response << ", \"friends_amount\": ";
		response << std::get<2>(amount) << ",";
		response << " \"we_subscribed\": ";
		response << std::get<0>(amount) << ",";
		response << " \"he_subscribed\": ";
		response << std::get<1>(amount);

		response << "}";
		return response.str();
	}


	std::string RequestHandler::form_get_fr_response(const std::vector<int>& friends) {
		std::stringstream response;
		response << "{\"response\": ";
		response << "\"true\"";
		response << ", \"data\": [";

		int i = 0;
		for (auto it : friends) {
			if (i != 0)
				response << ", ";
			response << it;
			i = 1;
		}
		response << "]}";
		return response.str();
	}
}
