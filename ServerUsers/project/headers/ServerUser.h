//
// Created by lerakry on 12.11.2020.
//

#ifndef SERVERUSERS_SERVERUSER_H
#define SERVERUSERS_SERVERUSER_H

#include <memory>

#include "SServer.h"
#include "Parser.h"

namespace tcp_server {
    class ServerUser : public SServer {
    public:
        ServerUser(const std::string& ip, const uint16_t port);
        ~ServerUser() noexcept;

        // распределить задачу по соот. функциям
        void process(std::string request);

        // проверка зарегистрировал ли пользователь
        bool CheckUser();

        // Если пользователь авторизовался, отправляем серверу AUTH
        // сообщение о том, что вот такой пользователь авторизовался
        std::string Send();

        // на вход - имя пользователя и его данные
        // на выход - сообщение об успехе или провале
        std::string CreateUser(std::string user, std::map<std::string, std::string> users_data );

        // на вход - имя пользователи и его данные
        // на выход - сообщение об успехе или провале
        std::string ChangeUserData(std::string user, std::map<std::string, std::string> users_data);

        // на выход - список всех друзей
        std::string AllUsers();

        // на вход - имя пользователя
        // на выход - сообщение об успехе или неудаче
        std::string DeleteUser(std::string user);

        // на вход - имя пользователя
        // на выход - данные пользователя
        std::map<std::string, std::string> UsersData(std::string user);


    private:
        std::map<std::string, std::string> requests_;
        std::unique_ptr<Parser> parser;

        // получить данные из базы данных
        std::string get();

        // удалить данные
        void delete_data();

        // вставить данные
        void insert();
    };

}

#endif //SERVERUSERS_SERVERUSER_H
