#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>


#include <cstdlib>
#include <future>

#include "http-server.hpp"

namespace logging = boost::log;

void HTTPServer::getConfFile() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("noskoolHTTP.ini", pt);
    try
    {
        _loggerPath = pt.get<std::string>("logger.path");
        _loggerLevel = pt.get<std::string>("logger.level");
        _context.insert({"staticPath", pt.get<std::string>("server.static_path")});
        _context.insert({"QRAddr", pt.get<std::string>("request-handler.queue-router-addr")});
        _context.insert({"QRPort", pt.get<std::string>("request-handler.queue-router-port")});
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

void HTTPServer::setLoggerLevel() {
    auto level = logging::trivial::warning;
    if (_loggerLevel == "trace") {
        level = logging::trivial::trace;
    } else if (_loggerLevel == "debug") {
        level = logging::trivial::debug;
    } else if (_loggerLevel == "info") {
        level = logging::trivial::info;
    } else if (_loggerLevel == "error") {
        level = logging::trivial::error;
    } else if (_loggerLevel == "fatal") {
        level = logging::trivial::fatal;
    }
    logging::core::get()->set_filter(
        logging::trivial::severity >= level
    );
}

void HTTPServer::initLogger() {
    setLoggerLevel();
}

void HTTPServer::initServer() {
    getConfFile();
    initLogger();
}

void HTTPServer::acceptAndRun()
{
    _acceptor.async_accept(
        _socket,
        [this](const error_code& accept_error) {
            if(!accept_error) {
                std::make_shared<Session>(std::move(_socket))->start(_context);
            }
            acceptAndRun();
        }
    );
}
