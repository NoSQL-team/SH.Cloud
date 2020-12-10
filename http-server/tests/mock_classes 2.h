
#ifndef TESTS_MOCK_CLASSES_H
#define TESTS_MOCK_CLASSES_H

#include <gtest/gtest.h>
#include "../lib/http-server/http-server.hpp"
#include <gmock/gmock.h>

using std::string;
using std::ostream;

class MockConnectionSend : public ConnectionSend {
public:
    MockConnectionSend() {}

    MOCK_METHOD0(close, int());
    MOCK_METHOD0(connect, int());
    MOCK_METHOD1(sendRequest, int(string request));
};

class MockRequestsHandler : public RequestsHandler {
public:
    MockRequestsHandler() {}

    MOCK_METHOD1(parseFirstHeader, void(string line));
    MOCK_METHOD1(parseNextHeaders, void(string line));
    MOCK_METHOD1(parseHeaders, void(ostream& stream));
    MOCK_METHOD2(responseFormation, void(string status, string body));
    MOCK_METHOD1(getResponse, string(ostream& stream));
};

class MockResponsesHandler : public ResponsesHandler {
protected:
    MockResponsesHandler() {}
public:
    MOCK_METHOD1(getResponse, string(size_t number));
    MOCK_METHOD1(setResponse, void(string response));
    MOCK_METHOD0(getInstance, ResponsesHandler*());
};

class MockSession : public Session {
public:
    MOCK_METHOD1(handleRequest, void(std::shared_ptr<Session> pThis));
};

#endif //TESTS_MOCK_CLASSES_H