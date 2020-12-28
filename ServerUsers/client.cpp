//
// Created by lerakrya on 09.12.2020.
//

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_service service;
    tcp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 12012);
    tcp::socket socket(service);
    socket.async_connect(end, [&socket] (const boost::system::error_code& err) {
//        std::string example = "123\napi/users/create/\n-1\n\n{\n"
//							 "  \"firstname\": \"lera\",\n"
//							 "  \"lastname\": \"guseva\",\n"
//							 "  \"nickname\": \"lerakrya\",\n"
//							 "  \"email\": \"lerakrya8@gmail.com\",\n"
//							 "  \"photo\": \"lera.png\",\n"
//							 "  \"password\": \"123456\"\n"
//							 "}";
//		std::string example = "123\napi/users/update/\n2\n\n{\n"
//						  "  \"id\": 2,\n"
//						  "  \"lastname\": \"guseva\",\n"
//						  "  \"nickname\": \"lerakrya\",\n"
//							"  \"status\": \"привет всем!!\"\n"
						  "}";
		std::string example = "123\napi/users/2/\n4\n\n\r";

        if(!err) {
            boost::asio::write(socket, boost::asio::buffer(example));
        }
    });
    service.run();

    return 0;
}