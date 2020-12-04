//
// Created by Andrew Kireev on 04.12.2020.
//

#include <boost/asio.hpp>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;


int main(int argc, char **argv) {

	io_service service;
	ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"),
						  8081);
	ip::tcp::socket sock(service);
	sock.async_connect(ep, [&sock](const system::error_code& error) {
		if (!error) {
			std::string requst = "5\n"
								 "0\n"
								 "add\n"
								 "\n"
								 "{\n"
								 "  \"user_1\": \"54\",\n"
								 "  \"user_2\": \"555\"\n"
								 "}";

			std::string get_all = "5\n"
								  "0\n"
								  "get_all\n"
								  "\n"
								  "{\n"
								  "  \"user_1\": \"55\"\n"
								  "}";

			std::string delete_user = "5\n"
									  "0\n"
									  "delete\n"
									  "\n"
									  "{\n"
									  "  \"user_1\": \"55\",\n"
									  "  \"user_2\": \"555\"\n"
									  "}";

//					std::istream(&data_) >> requst;
			boost::asio::write(sock, boost::asio::buffer(delete_user.c_str(), delete_user.size()));

//			std::cout << data_ << std::endl;
		}
	});
	service.run();

	return 0;
}
