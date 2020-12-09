#include "auth-server.hpp"

void Session::start() {
    auto self(shared_from_this());
    asio::async_read_until(
        _socket,
        _buffer,
        '\r', 
        _strand.wrap([this, self](const error_code& e, std::size_t s)
        {
            std::istream stream(&_buffer);
            _responseBuffer = headers.getResponse(stream);
            async_write(
                _socket,
                boost::asio::buffer(_responseBuffer.c_str(), _responseBuffer.length()),
                [this, self](const error_code& e, std::size_t s) {}
            );
        })
    );  
} 