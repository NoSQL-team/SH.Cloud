#include "http-server.hpp"

Requester* Requester::_objPtr = nullptr;

Requester *Requester::getInstance()
{
    std::lock_guard<std::mutex> lock(_requesterMutex);
    if (_objPtr == nullptr)
    {
        _objPtr = new Requester();
    }
    return _objPtr;
}

void Requester::sendRequest(std::string body, std::function<void()> fn, size_t number) {
    std::lock_guard<std::mutex> lock(_requesterMutex);
    async_write(
        _sock,
        boost::asio::buffer(body, body.length()),
        [](const error_code& e, std::size_t s) {}
    );
    ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
    responsesHandler->setCallback(fn, number);
}
