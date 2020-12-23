create table posts
(
post_id serial primary key,
creator_id integer not null,
creation_date timestamp without time zone, 
title varchar(512) not null,
text text,
attach text,
amount_likes integer not null,
liked_users text not null
); 
