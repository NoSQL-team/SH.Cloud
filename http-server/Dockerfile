FROM debian:buster

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

RUN apt-get install libboost-all-dev -y

ADD ./lib /app/src/lib
ADD ./CMakeLists.txt /app/src
ADD ./main.cpp /app/src

RUN cd /app/src/ && mkdir tmp && cd tmp && mkdir out && cmake .. && make && cd ..

ADD ./lib/http-server/noskoolHTTP.ini /
ADD ./static/m-skull/spa/out /out

CMD ["/bin/sh", "-c", "/app/src/tmp/main >&1"]