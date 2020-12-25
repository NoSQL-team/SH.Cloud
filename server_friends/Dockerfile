FROM debian:buster

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install cmake -y

RUN apt-get install libboost-all-dev -y && \
    apt-get install libpqxx-dev -y

ADD ./include /app/include
ADD ./src /app/src
ADD ./tests /app/tests
ADD ./CMakeLists.txt /app
ADD ./server_friends_test.cpp /app
ADD ./client_for_tests.cpp /app
ADD ./echo_server_for_tests.cpp /app
ADD ./test_bd.cpp /app

RUN cd /app/ && mkdir tmp && cd tmp && cmake .. && make

ADD ./friends_settings.ini /

CMD ["/bin/sh", "-c", "/app/tmp/server_friends_test >&1"]