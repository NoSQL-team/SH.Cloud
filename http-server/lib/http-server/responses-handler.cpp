#include "http-server.hpp"

ResponsesHandler* ResponsesHandler::_objPtr = nullptr;

ResponsesHandler *ResponsesHandler::getInstance()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_objPtr == nullptr)
    {
        _objPtr = new ResponsesHandler();
    }
    return _objPtr;
}

void ResponsesHandler::setCallback(std::function<void()> fn, size_t number) {
    std::lock_guard<std::mutex> lock(_mutex);
    _callbacks.insert({number, fn});
}

void ResponsesHandler::setResponse(std::string response, size_t number) {
    std::lock_guard<std::mutex> lock(_mutex);
    _responses.insert({number, response});
    if (_callbacks.count(number) > 0) {
        _callbacks[number]();
        _callbacks.erase(number);
    }
}

std::string ResponsesHandler::getResponse(size_t number) {
    std::lock_guard<std::mutex> lock(_mutex);
    std::string buffer = "";
    if (_responses.count(number) > 0) {
        buffer = _responses[number];
    }
    return buffer;
}
