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
    std::string _responseBody;
    size_t _responseStatus;
    std::map<std::string, std::string> _requestHeaders;
    std::map<std::string, std::string> _responseHeaders;
    int isOurServer = 0;

    std::mutex _lockRequest;

    void parseHeaders(std::istream& stream);
    std::string readResponseFile(const std::string& staticPath);
    std::string responseFormation(std::string body);
    std::string getExt(const std::string& st);
    void setMIMEType(const std::string& st);
    std::string encodeSStream(std::stringstream& stream);
    std::string gzipSStream(std::stringstream& stream);
    void logRequest();
    void setFirstHeader();
    void sendRequestToQR(std::string body);
    std::string formationRequest();

public:
    RequestsHandler() {};
    std::string getResponse(std::istream& stream, std::map<std::string, std::string> staticPath);
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

class Session:  public std::enable_shared_from_this<Session>
{
public:
    Session(ip::tcp::socket socket)
        : _socket(std::move(socket))
        ,_strand(_socket.get_io_service()) {}

    void start(std::map<std::string, std::string> context);
private:
    ip::tcp::socket _socket;
    asio::streambuf _buffer;
    std::string _responseBuffer;
    RequestsHandler headers;
    boost::asio::io_service::strand _strand;
};

class HTTPServer
{
    std::string _loggerPath;
    std::string _loggerLevel;
    ip::tcp::acceptor _acceptor;
    ip::tcp::socket _socket;
    std::map<std::string, std::string> _context;
    void acceptAndRun();
    void initServer();
    void getConfFile();
    void initLogger();
    void setLoggerLevel();
public:
    HTTPServer(boost::asio::io_service& io_service, uint16_t port):
        _acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)),
        _socket(io_service)
    {
        initServer();
        acceptAndRun();
    };
    ~HTTPServer() {};
};

#endif // !HTTTP_SERVER_NOSOOL
