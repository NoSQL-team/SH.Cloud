FROM debian:buster

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install libssl-dev -y && \
    apt-get install cmake -y

RUN apt-get install libboost-all-dev -y && \
    apt-get install libpqxx-dev -y

ADD ./include /app/include
ADD ./src /app/src
ADD ./main.cpp /app
ADD ./CMakeLists.txt /app

RUN cd /app/ && mkdir tmp && cd tmp && cmake .. && make

CMD ["/bin/sh", "-c", "/app/tmp/main >&1"]
