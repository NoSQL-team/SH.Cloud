//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_HANDLERS_H
#define MAIN_TP_HANDLERS_H


#include "../include/database.h"
#include "../include/types.h"


class Handlers {

public:
    Handlers() : _db() {};

    std::string for_user(const std::string& id_request, const std::map<std::string, size_t>& args);

    std::string all_posts(const std::string& id_request, const std::map<std::string, size_t>& args);

    std::string user_posts(std::string const& id_request, std::map<std::string, size_t> const& args);

    std::string one_post(std::string const& id_request, std::map<std::string, size_t> const& args);
    std::string delete_post(std::string const& id_request, std::map<std::string, size_t> const& args);

    std::string create_post(std::string const& id_request,
                            std::map<std::string, size_t> const& args,
                            std::string const& body);

    std::string update_post(std::string const& id_request,
                            std::map<std::string, size_t> const& args,
                            std::string const& body);

private:
    PostsDataBase _db;

};

#endif //MAIN_TP_HANDLERS_H
