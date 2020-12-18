//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_POST_H
#define MAIN_TP_POST_H

class Post {
public:
    Post() :
            post_id(0),
            creator_id(0),
            creation_date(""),
            title(""),
            text(""),
            attach("") {}

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

    // конструктор копирования
    Post(const Post& p) : post_id(p.post_id),
                                  creator_id(p.creator_id),
                                  creation_date(p.creation_date),
                                  title(p.title),
                                  text(p.text),
                                  attach(p.attach) {}

    int post_id;
    int creator_id;
    std::string creation_date{};
    std::string title{};
    std::string text{};
    std::string attach{};

};

#endif //MAIN_TP_POST_H
