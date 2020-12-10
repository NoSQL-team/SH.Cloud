//
// Created by steve on 10.12.2020.
//

#ifndef SERVER_POSTS_POST_H
#define SERVER_POSTS_POST_H


class Post {
public:
    Post(
            int post_id,
            int creator_id,
            std::string creation_date,
            std::string title,
            std::string text,
            std::string attach) : post_id(post_id),
                                  creator_id(creator_id),
                                  creation_date(std::move(creation_date)),
                                  title(std::move(title)),
                                  text(std::move(text)),
                                  attach(std::move(attach)) {}

    int post_id;
    int creator_id;
    std::string creation_date{};
    std::string title{};
    std::string text{};
    std::string attach{};

};

#endif //SERVER_POSTS_POST_H
