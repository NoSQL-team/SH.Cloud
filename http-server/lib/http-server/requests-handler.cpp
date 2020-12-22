#include <boost/algorithm/string.hpp>

#include <boost/lexical_cast.hpp>

#include <boost/log/trivial.hpp>

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>

#include <chrono>
#include <fstream>
#include <thread>
#include <iostream>

#include "http-server.hpp"

const std::string NOT_FOUND = "HTTP/1.1 404 Not Found";
const std::string OK = "HTTP/1.1 200 OK";
const std::string INTERNAL_SERVER_ERROR = "HTTP/1.1 500 Internal Server Error";
const std::string BAD_REQUEST = "HTTP/1.1 400 Bad Request";
const std::string METHOD_NOT_ALLOWED = "HTTP/1.1 405 Method Not Allowed";
const char NON_ANY_SERVER = 10;

const ssize_t OUR_SERVER_RESPONSE = 1;
const ssize_t BAD_METHOD = -1;
const ssize_t STATICT = 2;
const ssize_t HTTP_REQUEST = 0;
const ssize_t API_AUTH_REQUEST = 3;
const ssize_t OUR_SERVER_REQUEST = 4;
const ssize_t API_AUTH_REQUEST_OUR = 5;

extern size_t number;
extern std::mutex ResponsesHandler::_mutex;
extern std::mutex RequesterRouter::_requesterMutex;
extern std::mutex RequesterAuth::_requesterAuthMutex;

std::string RequestsHandler::getExt(const std::string& st)
{
    size_t pos = st.rfind('.');
    if (pos <= 0)
        return "";
    return st.substr(pos + 1, std::string::npos);
}

void RequestsHandler::setMIMEType(const std::string& st)
{
    std::string ext = getExt(st);
    if (st == "/") {
        _responseHeaders.insert({ "Content-Type", "text/html; charset=UTF-8" });
    } else if (ext == "js") {
        _responseHeaders.insert({ "Content-Type", "application/javascript; charset=UTF-8" });
    } else if (ext == "css") {
        _responseHeaders.insert({ "Content-Type", "text/css; charset=UTF-8" });
    } else if (ext == "map") {
        _responseHeaders.insert({ "Content-Type", "application/json; charset=UTF-8" });
    } else if (ext == "png") {
        _responseHeaders.insert({ "Content-Type", "image/png" });
    } else if (ext == "jpeg" || ext == "jpg") {
        _responseHeaders.insert({ "Content-Type", "image/jpeg" });
    } else if (ext == "gif") {
        _responseHeaders.insert({ "Content-Type", "image/gif" });
    } else {
        return;
    }
}

bool RequestsHandler::isOurServerFn(const std::string& header)
{
    bool isOur = true;
    for (size_t i = 0; i < header.size() - 1; i++) {
        if (!isdigit(header[i])) {
            isOur = false;
        }
    }
    _number = isOur ? lexical_cast<size_t>(header) : 0;
    isOurServer = (isOur ? OUR_SERVER_RESPONSE : NON_ANY_SERVER);
    return isOur;
}

void RequestsHandler::parseHeaders(std::istream& stream)
{
    std::vector<std::string> splitVect;
    std::string headerBuffer;
    std::getline(stream, headerBuffer);
    boost::split(splitVect, headerBuffer, boost::is_any_of(" "));
    if (std::strncmp(headerBuffer.c_str(), "/api/", 5) == 0) {
        isOurServer = OUR_SERVER_REQUEST;
        _url = headerBuffer;
        if (std::strncmp(_url.c_str(), "/api/auth/", 10) == 0) {
            isOurServer = API_AUTH_REQUEST_OUR;
        }
        while (std::getline(stream, headerBuffer)) {
            _body += headerBuffer + '\n';
        }
        return;
    } else if (isOurServerFn(headerBuffer)) {
        while (std::getline(stream, headerBuffer)) {
            _body += headerBuffer + '\n';
        }
        return;
    } else if (
        splitVect[0] == "GET" || splitVect[0] == "POST" || splitVect[0] == "PUT") {
        isOurServer = HTTP_REQUEST;
    } else {
        isOurServer = BAD_METHOD;
        return;
    }
    _method = splitVect[0];
    _url = splitVect[1];
    if (std::strncmp(_url.c_str(), "/api/", 5) != 0) {
        isOurServer = STATICT;
    }
    if (std::strncmp(_url.c_str(), "/api/auth/", 10) == 0) {
        isOurServer = API_AUTH_REQUEST;
    }
    _httpVersion = splitVect[2];
    splitVect.clear();
    while (std::getline(stream, headerBuffer)) {
        if (headerBuffer == "\r") {
            break;
        } else {
            boost::split(splitVect, headerBuffer, boost::is_any_of(":"));
            _requestHeaders.insert({ splitVect[0], splitVect[1] });
            splitVect.clear();
        }
    }
    if (_requestHeaders.find("Content-Length") != _requestHeaders.end()) {
        while (std::getline(stream, headerBuffer)) {
            _body += headerBuffer + '\n';
        }
    }
    setMIMEType(_url);
}

std::string RequestsHandler::gzipSStream(std::stringstream& stream)
{
    std::stringstream buffer;
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_compressor());
    in.push(stream);
    boost::iostreams::copy(in, buffer);
    return buffer.str();
}

std::string RequestsHandler::encodeSStream(std::stringstream& stream)
{
    auto encoding = _requestHeaders.find("Accept-Encoding");
    if (encoding != _requestHeaders.end()) {
        if (encoding->second.find("gzip") != std::string::npos) {
            _responseHeaders.insert({ "content-encoding", "gzip" });
            return gzipSStream(stream);
        } else {
            return stream.str();
        }
    }
    return stream.str();
}

std::string RequestsHandler::responseFormation(const std::string& body = "")
{
    std::stringstream buffer;
    if (isOurServer != OUR_SERVER_REQUEST && isOurServer != API_AUTH_REQUEST_OUR) {
        buffer << _responseFirstStr << std::endl;
        for (const auto& [header, value] : _responseHeaders) {
            buffer << header << ": " << value << std::endl;
        }
        buffer << std::endl;
    }
    buffer << boost::lexical_cast<std::string>(body);
    return buffer.str();
}

std::string RequestsHandler::readResponseFile(const std::string& staticPath)
{
    std::stringstream responseBody;
    std::string filePath;
    if (
        _url == "/" || _url == "/moment" || _url == "/login" || _url == "/profile") {
        filePath = staticPath + "/index.html";
    } else {
        filePath = staticPath + _url;
    }
    std::ifstream file(filePath);
    if (file.is_open()) {
        responseBody << file.rdbuf();
        _responseStatus = 200;
    } else {
        responseBody << "";
        _responseStatus = 404;
    }
    file.close();
    return encodeSStream(responseBody);
}

void RequestsHandler::logRequest()
{
    BOOST_LOG_TRIVIAL(info) << _method << " " << _url << " " << _responseFirstStr;
    std::cout << " " << std::endl;
}

void RequestsHandler::logRequestOur()
{
    BOOST_LOG_TRIVIAL(info) << "Our server: " << _number;
    std::cout << " " << std::endl;
}

void RequestsHandler::setFirstHeader()
{
    switch (_responseStatus) {
    case 200:
        _responseFirstStr = OK;
        break;
    case 400:
        _responseFirstStr = BAD_REQUEST;
        break;
    case 404:
        _responseFirstStr = NOT_FOUND;
        break;
    case 405:
        _responseFirstStr = METHOD_NOT_ALLOWED;
        break;
    default:
        _responseFirstStr = INTERNAL_SERVER_ERROR;
    }
}

std::string RequestsHandler::formationRequest()
{
    std::stringstream buffer;
    number++;
    buffer
        << number << "\n"
        << _url << "\n"
        << _user_auth_id << "\n"
        << "\n"
        << _body << "\r";
    return buffer.str();
}

void RequestsHandler::authHandler() {
    if (_requestHeaders.count("Authorization") != 0) {
        RequesterAuth* requesterAuth = RequesterAuth::getInstance();
        std::stringstream buffer;
        std::vector<std::string> splitVect;
        boost::split(splitVect, _requestHeaders.at("Authorization"), boost::is_any_of(" "));
        _ptBuffer.add("user_id", splitVect[1]);
        splitVect[2].pop_back();
        _ptBuffer.add("access_token", splitVect[2]);
        boost::property_tree::write_json(buffer, _ptBuffer);
        std::string res = requesterAuth->getResponse("/api/auth/authRequest/\n\n" + buffer.str() + '\r');
        std::istringstream b(res);
        boost::property_tree::read_json(b, _ptBuffer);
        if (_ptBuffer.get<std::string>("response") == "ok") {
            _user_auth_id = lexical_cast<ssize_t>(splitVect[1]);
        } else {
            _user_auth_id = -1;
        }
    }
}

std::string RequestsHandler::getResponse(std::istream& stream, const std::map<std::string, std::string>& context)
{
    parseHeaders(stream);
    authHandler();
    _responseHeaders.insert({ "Server", "linuxbox" });
    if (isOurServer == BAD_METHOD) {
        _responseStatus = 405;
        _responseBody = "Method not allowed";
    } else if (isOurServer == OUR_SERVER_RESPONSE) {
        ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
        responsesHandler->setResponse(_body, _number);
    } else if (isOurServer == HTTP_REQUEST || isOurServer == OUR_SERVER_REQUEST) {
        RequesterRouter* requester = RequesterRouter::getInstance();
        requester->sendRequest(formationRequest(), [this]() { isResponseReady = true; }, number + 1);
        _number = number;
        while (!isResponseReady) {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
        ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
        _responseBody = responsesHandler->getResponse(_number);
        _responseHeaders.insert({ "Content-Type", "application/json; charset=UTF-8" });
        _responseStatus = 200;
    } else if (isOurServer == STATICT) {
        _responseBody = readResponseFile(context.at("staticPath"));
        _responseStatus = 200;
    } else if (isOurServer == API_AUTH_REQUEST || isOurServer == API_AUTH_REQUEST_OUR) {
        RequesterAuth* requesterAuth = RequesterAuth::getInstance();
        std::stringstream buffer;
        buffer << _url << std::endl << std::endl << _body << "\r";
        _responseBody = requesterAuth->getResponse(buffer.str());
        _responseHeaders.insert({ "Content-Type", "application/json; charset=UTF-8" });
        _responseStatus = 200;
    }
    setFirstHeader();
    _responseHeaders.insert({ "Content-Length", boost::lexical_cast<std::string>(_responseBody.length()) });
    (isOurServer == OUR_SERVER_RESPONSE) ? logRequestOur() : logRequest();
    return (isOurServer == OUR_SERVER_RESPONSE) ? "our" : responseFormation(_responseBody);
}
