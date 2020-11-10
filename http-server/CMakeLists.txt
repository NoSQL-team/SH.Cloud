cmake_minimum_required(VERSION 2.6)
PROJECT(boost-asio-examples)


SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.67.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

add_library(libhttp-server STATIC 
  lib/http-server/connection.cpp
  lib/http-server/session.cpp
  lib/http-server/requests-handler.cpp
  lib/http-server/responses-handler.cpp
)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

set(CMAKE_CXX_FLAGS "-lpthread")

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main ${USED_LIBS} libhttp-server)
