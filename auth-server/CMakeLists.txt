cmake_minimum_required(VERSION 3.13.4)
project(auth-server-nosool)

add_library(libauth-server STATIC 
  lib/auth-server/auth-server.cpp
)

set(CMAKE_CXX_FLAGS "-lpthread -lpqxx -lpq")

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main libauth-server)
