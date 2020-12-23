//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_POST_H
#define MAIN_TP_POST_H

class Post {
public:

    explicit Post(
            int creator_id,
            std::string title,
            std::string text,
            std::string attach,
            std::string creation_date = std::string(),
            int post_id = 0,
            int amount_likes = 0,
            std::string liked_users = std::string()) :
                                post_id(post_id),
                                creator_id(creator_id),
                                creation_date(std::move(creation_date)),
                                title(std::move(title)),
                                text(std::move(text)),
                                attach(std::move(attach)),
                                amount_likes(amount_likes),
                                liked_users(std::move(liked_users)){}

    // конструктор копирования
    Post(const Post& p) = default;

    int post_id;
    int creator_id;
    std::string creation_date{};
    std::string title{};
    std::string text{};
    std::string attach{};
    int amount_likes;
    std::string liked_users{};
};

#endif //MAIN_TP_POST_H
