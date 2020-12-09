#include "auth-server.hpp"

DateBaseConnection* DateBaseConnection::_objPtr= nullptr;;
std::mutex DateBaseConnection::_mutex;

DateBaseConnection *DateBaseConnection::getInstance()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _objPtr;
}

DateBaseConnection *DateBaseConnection::getInstance(
    std::string dbname,
    std::string host,
    std::string user,
    std::string password
) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_objPtr == nullptr)
    {
        _objPtr = new DateBaseConnection(
            dbname,
            host,
            user,
            password
        );
    }
    return _objPtr;
}
