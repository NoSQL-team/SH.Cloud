#ifndef HTTTP_SERVER_NOSOOL
#define HTTP_SERVER_NOSKOOL

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <iostream>
#include <vector>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

class RequestsHandler
{
    std::string _method;
    std::string _url;
    std::string _version;
    std::string _body;
    std::string _httpVersion;
    std::string _contentType;
    std::string _responseFirstStr;
    std::map<std::string, std::string> _requestHeaders;
    std::map<std::string, std::string> _responseHeaders;
    int isOurServer = 0;

    void parseHeaders(std::istream& stream);
    std::string readResponseFile(const std::string& staticPath);
    std::string responseFormation(std::string body);
    std::string getExt(const std::string& st);
    void setMIMEType(const std::string& st);
    std::string encodeSStream(std::stringstream& stream);
    std::string gzipSStream(std::stringstream& stream);
    void logRequest();

public:
    RequestsHandler() {};
    std::string getResponse(std::istream& stream, const std::string& staticPath);
};

class Session
{
    asio::streambuf _buffer;
    std::string _responseBuffer;
    RequestsHandler headers;
    
public:
    ip::tcp::socket socket;

    Session(io_service& io_service)
        :socket(io_service)
    {}
    
    static void handleRequest(std::shared_ptr<Session> pThis, std::string staticPath);
};

class ResponsesHandler
{
protected:
    ResponsesHandler() {}

    static ResponsesHandler* _objPtr;
    std::vector<std::map<size_t, std::string>> _responses;
    static std::mutex _mutex;

public:
    ResponsesHandler(ResponsesHandler &other) = delete;
    void operator=(const ResponsesHandler &) = delete;
    static ResponsesHandler* getInstance();
    std::string getResponse(size_t number);
    void setResponse(std::string response);
};

class HTTPServer
{
    uint16_t _port;
    std::string _loggerPath;
    std::string _loggerLevel;
    std::string _staticPath;
    void acceptAndRun(ip::tcp::acceptor& acceptor, io_service& io_service);
    void initServer();
    void getConfFile();
    void initLogger();
    void setLoggerLevel();
public:
    void run();
    HTTPServer() {};
    ~HTTPServer() {};
};

#endif // !HTTTP_SERVER_NOSOOL