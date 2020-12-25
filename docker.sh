#!/bin/bash

# RESULT=$(docker images -a -q)
# docker rmi -f $RESULT
# RESULT=$(docker ps -a -q)
# docker rmi -f $RESULT

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

cd ../ServerQueue

mv queue_settings-1.ini queue_settings.ini
docker build -t noskool-queue-1 .
mv queue_settings.ini queue_settings-1.ini

mv queue_settings-2.ini queue_settings.ini
docker build -t noskool-queue-2 .
mv queue_settings.ini queue_settings-2.ini

mv queue_settings-3.ini queue_settings.ini
docker build -t noskool-queue-3 .
mv queue_settings.ini queue_settings-3.ini

cd ..
# # docker-compose down -v
# docker-compose up
