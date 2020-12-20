FROM debian:buster

RUN apt-get update && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install wget -y && \
    apt-get install libssl-dev -y
RUN mkdir libtmp && cd libtmp && \
    wget https://github.com/Kitware/CMake/releases/download/v3.19.1/cmake-3.19.1.tar.gz && \
    tar -zxvf cmake-3.19.1.tar.gz && cd cmake-3.19.1 && \
    ./bootstrap && make && make install && cd ..

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

CMD ["/bin/sh", "-c", "/app/src/tmp/server_friends_test >&1"]