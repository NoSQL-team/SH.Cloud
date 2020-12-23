
#ifndef TESTS_MOCK_CLASSES_H
#define TESTS_MOCK_CLASSES_H

#include <gtest/gtest.h>
#include "../lib/auth-server/auth-server.hpp"
#include <gmock/gmock.h>

using std::string;
using std::map;

class MockDateBaseConnection : public DateBaseConnection {
public:
    MockDateBaseConnection() {}
    ~MockDateBaseConnection() {}

    MOCK_METHOD1(select, string(string request));
    MOCK_METHOD1(add_entry, int(string entry));
    MOCK_METHOD1(delete_entry, int(string request));
};

class MockParserJSON : public ParserJSON {
public:
    MockParserJSON() {}

    MOCK_METHOD1(parse, map<string, string>(string str));
    MOCK_METHOD1(jsonfication, string(map<string, string> object));
};

class MockConnection : public Connection {
public:
    MockConnection(uint16_t port, std::string ip)
        :Connection(port, ip) {}

    MOCK_METHOD1(sendRequest, string(string request));
    MOCK_METHOD0(getResponse, string());
};

class MockAuthService : public AuthService {
public:
    MockAuthService() {}

    MOCK_METHOD1(requestHandlerIsAuth, string(string body));
    MOCK_METHOD1(requestHandlerAuth, string(string body));
    MOCK_METHOD1(requestHandlerLogout, string(string body));
    MOCK_METHOD1(requestHandlerAddUser, string(string body));
    MOCK_METHOD2(genToken, string(string body, string email));
    MOCK_METHOD0(sendResponse, void());
    MOCK_METHOD0(getResponse, string());
    MOCK_METHOD0(run, void());
    MOCK_METHOD2(setServerHTTP, void(uint16_t port, string ip));
    MOCK_METHOD2(setServerQueue, void(uint16_t port, string ip));
};

#endif //TESTS_MOCK_CLASSES_H 