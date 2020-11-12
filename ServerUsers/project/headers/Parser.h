//
// Created by lerakry on 12.11.2020.
//

#ifndef SERVERUSERS_PARSER_H
#define SERVERUSERS_PARSER_H

#include <iostream>
#include <string>
#include <map>

class Parser {
public:
    Parser() = default;
    std::map<std::string, std::string> parsejson(std::string request);
    std::map<std::string, std::string> get_string();
private:
    std::map<std::string, std::string> request_;
};

#endif //SERVERUSERS_PARSER_H
