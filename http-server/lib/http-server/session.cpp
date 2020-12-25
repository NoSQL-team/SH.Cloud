#include "http-server.hpp"


#include <cstring>

void Session::start(std::map<std::string, std::string> context) {
    auto self(shared_from_this()); 
    for (size_t i = 0; i < 10024; i++) {
        buff[i] = '\0';
    }
    _socket.async_read_some(
        buffer(buff),
        _strand.wrap([this, self, context](const error_code& e, std::size_t s)
        {
            std::istringstream stream(buff);
            _responseBuffer = headers.getResponse(stream, context);
            std::cout << _responseBuffer << std::endl;
            if (!(_responseBuffer == "our")) {
                async_write(
                    _socket,
                    boost::asio::buffer(_responseBuffer.c_str(), _responseBuffer.length()),
                    [this, self](const error_code& e, std::size_t s) {}
                );
            }
        })
    );
}
