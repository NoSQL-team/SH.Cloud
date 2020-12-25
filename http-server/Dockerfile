FROM debian:buster

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install cmake -y
RUN apt-get install libboost-all-dev -y

ADD ./lib /app/src/lib
ADD ./CMakeLists.txt /app/src
ADD ./main.cpp /app/src

RUN cd /app/src/ && mkdir tmp && cd tmp && mkdir out && cmake .. && make && cd ..

ADD ./lib/http-server/noskoolHTTP.ini /
ADD ./static /out

CMD ["/bin/sh", "-c", "/app/src/tmp/main >&1"]