#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>

#include <fstream>
#include <chrono>
#include <thread>

#include "http-server.hpp"

#define NOT_FOUND "HTTP/1.1 404 Not Found"
#define OK "HTTP/1.1 200 OK"
#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error"
#define BAD_REQUEST "HTTP/1.1 400 Bad Request"
#define METHOD_NOT_ALLOWED "HTTP/1.1 405 Method Not Allowed"

std::string RequestsHandler::getExt(const std::string& st) {
    size_t pos = st.rfind('.');
    if (pos <= 0) return "";
    return st.substr(pos+1, std::string::npos);
}

void RequestsHandler::setMIMEType(const std::string& st) {
    std::string ext = getExt(st);
    if (st == "/") {
        _responseHeaders.insert({"Content-Type", "text/html; charset=UTF-8"});
    } else if (ext == "js") {
        _responseHeaders.insert({"Content-Type", "application/javascript; charset=UTF-8"});
    } else if(ext == "css") {
        _responseHeaders.insert({"Content-Type", "text/css; charset=UTF-8"});
    } else if (ext == "map") {
        _responseHeaders.insert({"Content-Type", "application/json; charset=UTF-8"});
    } else if (ext == "png") {
        _responseHeaders.insert({"Content-Type", "image/png"});
    } else if (ext == "jpeg" || ext == "jpg") {
        _responseHeaders.insert({"Content-Type", "image/jpeg"});
    } else if (ext == "gif") {
        _responseHeaders.insert({"Content-Type", "image/gif"});
    }
    else {
        return;
    }
}

void RequestsHandler::parseHeaders(std::istream& stream) {
    std::vector<std::string> splitVect;
    std::string headerBuffer;
    std::getline(stream, headerBuffer);
    boost::split(splitVect, headerBuffer, boost::is_any_of(" "));
    if (
        splitVect[0] == "GET" ||
        splitVect[0] == "POST" ||
        splitVect[0] == "PUT"
    ) {
        isOurServer = 0;
    } else if (std::all_of(headerBuffer.begin(), headerBuffer.end(), ::isdigit)) {
        isOurServer = 1;
        return;
    } else { 
        isOurServer = -1;
        return;
    }
    _method = splitVect[0];
    _url = splitVect[1];
    _httpVersion = splitVect[2];
    splitVect.clear();
    while(std::getline(stream, headerBuffer)) {
        if (headerBuffer == "\r") {
            break;
        } else {
            boost::split(splitVect, headerBuffer, boost::is_any_of(":"));
            _requestHeaders.insert({splitVect[0], splitVect[1]});
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

std::string RequestsHandler::gzipSStream(std::stringstream& stream) {
    std::stringstream buffer;
    boost::iostreams::filtering_streambuf< boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_compressor());
    in.push(stream);
    boost::iostreams::copy(in, buffer);
    return buffer.str();
}

std::string RequestsHandler::encodeSStream(std::stringstream& stream) {
    if (_requestHeaders.find("Accept-Encoding") != _requestHeaders.end()) {
        if (_requestHeaders.find("Accept-Encoding")->second.find("gzip") != std::string::npos) {
            _responseHeaders.insert({"content-encoding", "gzip"});
            return gzipSStream(stream);
        } else {
            return stream.str();
        }
    }
    return stream.str();
}

std::string RequestsHandler::responseFormation(std::string body = "") {
    std::stringstream buffer;
    buffer << _responseFirstStr << std::endl;
    for (const auto& [header, value] : _responseHeaders) {
        buffer << header << ": " << value << std::endl;
    }
    buffer << std::endl << boost::lexical_cast<std::string>(body);
    return buffer.str();
}

std::string RequestsHandler::readResponseFile(const std::string& staticPath) {
    std::stringstream responseBody;
    std::string filePath;
    if (
        _url == "/" ||
        _url == "/moment" ||
        _url == "/login" ||
        _url == "/profile"
    ) {
        filePath = staticPath + "/index.html";
    } else {
        filePath = staticPath + _url;
    }
    std::ifstream file(filePath);
    if(file.is_open()) {
        responseBody << file.rdbuf();
        _responseStatus = 200;
    } else {
        responseBody << "";
        _responseStatus = 404;
    }
    file.close();
    return encodeSStream(responseBody);
}

void RequestsHandler::logRequest() {
    BOOST_LOG_TRIVIAL(info) << _method << " " << _url << " " << _responseFirstStr;
}

void RequestsHandler::setFirstHeader() {
    switch (_responseStatus)
    {
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

void RequestsHandler::sendRequestToQR() {
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8080);
    ip::tcp::socket sock(service);
    sock.connect(ep);
    std::stringstream request_stream;
    request_stream << "GET " << "/" << " HTTP/1.0\r\n";
    request_stream << "Host: " << "127.0.0.1" << "\r\n";
    request_stream << "Accept: */*\r\n"; // Любой MIME type
    request_stream << "Connection: close\r\n\r\n";
    async_write(
        sock,
        boost::asio::buffer(request_stream.str(), request_stream.str().length()),
        [](const error_code& e, std::size_t s) {
            if (!e) {
                
            }
        }
    );
}

std::string RequestsHandler::getResponse(std::istream& stream, std::map<std::string, std::string> context)
{
    parseHeaders(stream);
    _responseHeaders.insert({"Server", "linuxbox"});
    if (isOurServer == -1) {
        _responseStatus = 405;
        _responseBody = "Method not allowed";
    } else if (isOurServer == 1) {

    } else if (isOurServer == 0) {
        std::stringstream ssOut;
        if(std::strncmp(_url.c_str(), "/api/", 5)) {
            _responseBody = readResponseFile(context["staticPath"]);
        } else {
            // sendRequestToQR();
            std::this_thread::sleep_for(std::chrono::seconds(20));
            ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
        }
    }
    setFirstHeader();
    logRequest();
    _responseHeaders.insert({
        "Content-Length", boost::lexical_cast<std::string>(_responseBody.length())
    });
    return responseFormation(_responseBody);
}
