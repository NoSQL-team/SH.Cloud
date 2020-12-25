FROM debian:buster

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install cmake -y

RUN apt-get install libboost-all-dev -y && \
    apt-get install libpqxx-dev -y

ADD ./includes /app/includes
ADD ./src /app/src
ADD ./client.cpp /app
ADD ./echo_server.cpp /app
ADD ./http_echo_server.cpp /app
ADD ./main.cpp /app
ADD ./test_db.cpp /app
ADD ./test_server.cpp /app
ADD ./CMakeLists.txt /app

RUN cd /app/ && mkdir tmp && cd tmp && cmake .. && make

CMD ["/bin/sh", "-c", "/app/tmp/test_server >&1"]