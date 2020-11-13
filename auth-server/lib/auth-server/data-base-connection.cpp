#include "auth-server.hpp"

DateBaseConnection* DateBaseConnection::_objPtr= nullptr;;

DateBaseConnection *DateBaseConnection::getInstance()
{
    // std::lock_guard<std::mutex> lock(_mutex);
    if (_objPtr == nullptr)
    {
        _objPtr = new DateBaseConnection();
    }
    return _objPtr;
} 