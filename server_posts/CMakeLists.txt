cmake_minimum_required(VERSION 3.13.4)
project(main_tp)
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_CXX_FLAGS "-g -Wall -lpthread -lgtest -L/usr/local/lib")
#set(CMAKE_CXX_FLAGS "-g -Wall -lpthread -lgtest -L/usr/local/lib -lpqxx -lpq")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(docker_build TRUE)

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

if (FALSE)
    #find_package(PQXX)
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)
endif()


#find_package(Boost)
#include_directories(${Boost_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS system thread regex log_setup log)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_LIBRARIES})
add_definitions(-DBOOST_LOG_DYN_LINK)


set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INC_DIR ${DIR}/include)
set(SRC_DIR ${DIR}/src)


add_library(main_tp STATIC
        main.cpp
        ${SRC_DIR}/handlers.cpp
        ${SRC_DIR}/server.cpp
        ${SRC_DIR}/database.cpp
        ${SRC_DIR}/session.cpp
        ${SRC_DIR}/utility_for_lib.cpp

        ${INC_DIR}/handlers.h
        ${INC_DIR}/server.h
        ${INC_DIR}/post.h
        ${INC_DIR}/database.h
        ${INC_DIR}/types.h
        ${INC_DIR}/session.h
        ${INC_DIR}/utility_for_lib.h)




add_executable(main main.cpp)
target_link_libraries(main main_tp ${Boost_LIBRARIES} Threads::Threads pthread ${PQXX_LIB} ${PQ_LIB})