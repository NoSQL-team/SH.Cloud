cmake_minimum_required(VERSION 3.17)
project(server_posts)
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_CXX_FLAGS "-g -Wall -lpthread -lgtest -L/usr/local/lib")
set(CMAKE_CXX_FLAGS "-g -Wall -lpthread -lgtest -L/usr/local/lib -lpqxx -lpq")


#find_package(PQXX)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)




find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(INC_DIR ${DIR}/include)
set(SRC_DIR ${DIR}/src)


add_library(server_posts STATIC
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/database.cpp include/post.h)

add_executable(server_posts_test src/main.cpp)
target_link_libraries(server_posts_test ${Boost_LIBRARIES} Threads::Threads pthread)



