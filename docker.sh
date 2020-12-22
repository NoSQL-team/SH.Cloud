#!/bin/bash

cd http-server
docker build -t noskool-http .
cd ../auth-server
docker build -t noskool-auth .
cd ../server_router
docker build -t noskool-router .
cd ../ServerQueue
docker build -t noskool-queue-1 .
cd ../ServerUsers
docker build -t noskool-users .
cd ..
docker-compose down -v
docker-compose up
