#include "http-server.hpp"

RequesterRouter* RequesterRouter::_objPtr = nullptr;

RequesterRouter *RequesterRouter::getInstance()
{
    std::lock_guard<std::mutex> lock(_requesterMutex);
    return _objPtr;
}

RequesterRouter *RequesterRouter::getInstance(const std::string& addr, const std::string& port)
{
    std::lock_guard<std::mutex> lock(_requesterMutex);
    if (_objPtr == nullptr)
    {
        _objPtr = new RequesterRouter(addr, port);
    }
    return _objPtr;
}

void RequesterRouter::sendRequest(std::string body, std::function<void()> fn, size_t number) {
    std::lock_guard<std::mutex> lock(_requesterMutex);
    _sock.connect(_ep);
    async_write(
        _sock,
        boost::asio::buffer(body, body.length()),
        [](const error_code& e, std::size_t s) {}
    );
    ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
    responsesHandler->setCallback(fn, number);
    _sock.close();
}
