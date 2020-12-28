#!/bin/bash

cd http-server
docker build -t noskool-http .
cd ../auth-server
docker build -t noskool-auth .
cd ../server_router
docker build -t noskool-router .
cd ../server_posts
docker build -t noskool-posts .
cd ../ServerUsers
docker build -t noskool-users .
cd ../server_friends
docker build -t noskool-friends .
