FROM ubuntu:focal

ENV TZ=Europe/Minsk
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install wget -y && \
    apt-get install libssl-dev -y
RUN mkdir libtmp && cd libtmp && \
    wget https://github.com/Kitware/CMake/releases/download/v3.19.1/cmake-3.19.1.tar.gz && \
    tar -zxvf cmake-3.19.1.tar.gz && cd cmake-3.19.1 && \
    ./bootstrap && make && make install && cd ..

RUN apt-get install libboost-all-dev -y && \
    apt-get install libgtest-dev -y


ADD ./include /app/include
ADD ./src /app/src
ADD ./tests /app/tests
ADD ./client_for_tests.cpp /app
ADD ./echo_server_for_tests_1.cpp /app
ADD ./echo_server_for_tests_2.cpp /app
ADD ./server_router_for_tests.cpp /app
ADD ./test_parser.cpp /app
ADD ./CMakeLists.txt /app

RUN cd /app/ && mkdir tmp && cd tmp && cmake .. && make

CMD ["/bin/sh", "-c", "/app/tmp/server_router_test >&1"]