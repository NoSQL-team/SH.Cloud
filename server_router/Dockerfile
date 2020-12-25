FROM ubuntu:focal

ENV TZ=Europe/Minsk
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install cmake -y

RUN apt-get install libboost-all-dev -y

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

ADD ./router_settings.ini /

CMD ["/bin/sh", "-c", "/app/tmp/server_router_test >&1"]