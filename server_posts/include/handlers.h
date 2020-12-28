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
    std::string popular_posts(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string user_posts(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string one_post(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string delete_post(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string add_like(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string del_like(const std::string& id_request, const std::map<std::string, size_t>& args);



    std::string create_post(const std::string& id_request,
                            const std::map<std::string, size_t>& args,
                            std::string& body);

private:
    PostsDataBase _db;
};

#endif //MAIN_TP_HANDLERS_H
