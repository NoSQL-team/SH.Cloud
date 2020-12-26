create table users
(
    id        serial      not null
        constraint users_pkey
            primary key,
    firstname text not null,
    lastname  text not null,
    nickname  text not null,
    email     text not null,
    photo     text,
    status    text,
    ico_status text
);