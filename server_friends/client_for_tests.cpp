//
// Created by Andrew Kireev on 04.12.2020.
//

#include <boost/asio.hpp>
#include <iostream>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;


class Client {
public:
	Client(std::string& ip, uint16_t port) : ip_(ip), port_(port) {
		set_service(ip_, port_);
	}

	void set_service(std::string& ip, uint16_t port) {
		ip::tcp::endpoint ep( ip::address::from_string(ip),
							  port);

		ip::tcp::socket socket(service);
		connect(socket, ep);
		service.run();
	}

	void connect(ip::tcp::socket& socket, const ip::tcp::endpoint& ep) {
		socket.connect(ep);
		write(socket);
	}

	void write(ip::tcp::socket& socket) {
//		if (!error) {
			std::string request_type;
			std::cin >> request_type;
			if (request_type == "add") {
				int user_1, user_2;
				std::cin >> user_1 >> user_2;

				std::string add_request = "5\n"
									  "/api/auth/add/\n"
		   			                  "5\n"
									  "\n"
									  "{\n"
									  "  \"user_1\": \"" + std::to_string(user_2) + "\",\n"
									  "  \"user_2\": \"" + std::to_string(user_1) + "\"\n"
									  "}";


				boost::asio::write(socket, boost::asio::buffer(add_request.c_str(), add_request.size()));
				std::cout << "Запрос отправлен" << std::endl;
			} else if (request_type == "get_all") {
				int user_id;
				std::cin >> user_id;

				std::string get_all_request = "5\n"
									  "/api/auth/get_all/\n"
		   				              "5\n"
									  "\n"
									  "{\n"
									  "  \"user_1\": \"" + std::to_string(user_id) +"\"\n"
									  "}";

				boost::asio::write(socket, boost::asio::buffer(get_all_request.c_str(), get_all_request.size()));
				std::cout << "Запрос отправлен" << std::endl;
			} else if (request_type == "is_friends") {
				int user_1, user_2;
				std::cin >> user_1 >> user_2;

				std::string is_friends = "5\n"
										 "/api/auth/is_friend/\n"
										 "5\n"
										 "\n"
										 "{\n"
										 "  \"user_1\": \"" + std::to_string(user_1) + "\",\n"
										 "  \"user_2\": \"" + std::to_string(user_2) + "\"\n"
										 "}";

				boost::asio::write(socket, boost::asio::buffer(is_friends.c_str(), is_friends.size()));
				std::cout << "Запрос отправлен" << std::endl;
			} else if (request_type == "delete") {
				int user_1, user_2;
				std::cin >> user_1 >> user_2;

				std::string delete_user = "5\n"
										  "/api/auth/delete/\n"
										  "5\n"
										  "\n"
										  "{\n"
										  "  \"user_1\": \"" + std::to_string(user_1) + "\",\n"
										  "  \"user_2\": \"" + std::to_string(user_2) + "\"\n"
										  "}";

				boost::asio::write(socket, boost::asio::buffer(delete_user.c_str(), delete_user.size()));
				std::cout << "Запрос отправлен" << std::endl;
			}
			if (request_type != "end")
				set_service(ip_, port_);
	}

private:
	std::string& ip_;
	uint16_t port_;

	io_service service;
};


int main(int argc, char **argv) {
	std::string ip = "127.0.0.1";
	Client client(ip, 12013);

	return 0;
}
