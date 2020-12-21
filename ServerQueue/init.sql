create table users
(
    id        serial      not null
        constraint users_pkey
            primary key,
    firstname varchar(30) not null,
    lastname  varchar(30) not null,
    nickname  varchar(35) not null,
    email     varchar(45) not null,
    photo     varchar(150)
);