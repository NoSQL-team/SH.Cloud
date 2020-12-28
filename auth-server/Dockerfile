FROM debian:buster

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install libssl-dev -y && \
    apt-get install cmake -y

RUN apt-get install libboost-all-dev -y && \
    apt-get install libpqxx-dev -y
    
ADD ./lib /app/src/lib
ADD ./ex_lib /app/src/ex_lib
ADD ./CMakeLists.txt /app/src
ADD ./main.cpp /app/src

RUN cd /app/src/ && mkdir tmp && cd tmp && cmake .. && make

ADD ./lib/auth-server/noskoolAuth.ini /

CMD ["/bin/sh", "-c", "/app/src/tmp/main >&1"]