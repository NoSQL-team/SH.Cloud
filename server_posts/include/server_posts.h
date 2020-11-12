//
// Created by amartery on 08.11.2020.
//

#ifndef NOSKOOL_SERVER_POSTS_H
#define NOSKOOL_SERVER_POSTS_H

// #include "connection.h"
// #include "server_interface.h"
#include "posts_data_base.h"
#include <string>


namespace tcp_server {

class Post {
public:
    Post(int i, int i1, const char string[1], const char string1[1], const char string2[1], int i2);
    ~Post();
public:
    int id;
    int user_id;
    std::string title;
    std::string description;
    std::string body;
    int time;  // ???
};

    class ServerPosts : public TCPServer {
    public:
        ServerPosts(const std::string& ip, uint16_t port) = default;

        ~ServerPosts() noexcept override;

        /*
        Нахождение постов конкретного пользователя
        принимает id пользователя для выборки его друзей, 
        возвращает посты его друзей ???
        */
        void find_posts_for_user(int id);
            // Запрос auth сервиса аутентифицирован ли пользователь
            // Запрос auth сервиса получения id пользователя для выборки его друзей
            // Запрос в friens сервис друзей пользователя
            // Запрос в БД постов на основе выборки друзей
        

        /*
        Нахождение всех постов всех пользователей
        возвращаются все посты из бд упорядоченные по дате ???
        */
        void all_posts();
            

        /*
        Нахождение постов конкретного пользователя
        принимает id пользователя, возвращает посты созданные ползьзователем???
        */
        void find_user_posts(int id);
            // Запрос в users сервис на id пользователя
            // Запрос в БД постов


        /*
        Созадает пост пользователя id, заполняет класс Post
        и вызывает метод записи в БД
        */
        void create_post(int id, Post& post);
            // Запрос auth сервиса аутентифицирован ли пользователь
            // Запрос auth сервиса получения id пользователя для сохранения его в БД сервиса постов
            // Запрос в БД на создание


        /*
        Проверяет авторизирован ли пользватель, далее заполняем класс Post обновленными значениями
        и делаем перезапись в БД поста с post_id
        */
        void change_post(int id, int post_id, Post& post_updates);
            // Запрос auth сервиса аутентифицирован ли пользователь
            // Запрос auth сервиса получения id пользователя для проверки его ли это пост
            // Запрос на изменение поста в БД


        /*
        Проверяет авторизирован ли пользватель, удаляет пост с post_id
        */
        void delete_post(int id, int post_id);
            // Запрос auth сервиса аутентифицирован ли пользователь
            // Запрос auth сервиса получения id пользователя для проверки его ли это пост
            // Запрос на удаление поста в БД


        /*Возвращает один конкретный пост c post_id*/
        static Post& get_one_post(int post_id);


    private:
        std::unique_ptr<PostsDataBase> database_connector_;
    };

}

#endif  // NOSKOOL_SERVER_POSTS_H