#include "http-server.hpp"

#include <iostream>

RequesterAuth* RequesterAuth::_objPtr = nullptr;

RequesterAuth *RequesterAuth::getInstance()
{
    std::lock_guard<std::mutex> lock(_requesterAuthMutex);
    return _objPtr;
}

RequesterAuth *RequesterAuth::getInstance(const std::string& addr, const std::string& port)
{
    std::lock_guard<std::mutex> lock(_requesterAuthMutex);
    if (_objPtr == nullptr)
    {
        _objPtr = new RequesterAuth(addr, port);
    }
    return _objPtr;
}

std::string RequesterAuth::getResponse(std::string body) {
    std::lock_guard<std::mutex> lock(_requesterAuthMutex);
    _sock.connect(_ep);
    _body = body;
    write(_sock, boost::asio::buffer(_body, _body.length()));
    boost::asio::streambuf buffer;
    read_until(_sock, buffer, '\r');
    _sock.close();
    return std::string({boost::asio::buffers_begin(buffer.data()), boost::asio::buffers_end(buffer.data())});
}
