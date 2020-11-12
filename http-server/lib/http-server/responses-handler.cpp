#include "http-server.hpp"

ResponsesHandler* ResponsesHandler::_objPtr= nullptr;;

ResponsesHandler *ResponsesHandler::getInstance()
{
    // std::lock_guard<std::mutex> lock(_mutex);
    if (_objPtr == nullptr)
    {
        _objPtr = new ResponsesHandler();
    }
    return _objPtr;
}