cmake_minimum_required(VERSION 3.13.4)

project(auth-server-noskool)
#======================================================================================

option(TESTS "" OFF)

#======================================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "-lpthread -lgtest -lpqxx -lpq")

#======================================================================================

find_package(Boost 1.67.0 REQUIRED COMPONENTS system thread regex log_setup log)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_LIBRARIES})
add_definitions(-DBOOST_LOG_DYN_LINK)

#======================================================================================

add_library(libauth-server STATIC 
  lib/auth-server/auth-server.cpp
  lib/auth-server/requests-handler.cpp
  lib/auth-server/session.cpp
  lib/auth-server/data-base-connection.cpp
)

#======================================================================================

add_subdirectory(ex_lib/jwt-cpp)
include_directories(ex_lib/jwt-cpp/include)

#======================================================================================

if(TESTS)
  find_package(GTest REQUIRED)
  find_package(Threads REQUIRED)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED on)

  add_executable(mainTest 
    tests/tests.cpp
    tests/mock_classes.h
  )

  include_directories(${GTEST_INCLUDE_DIRS})
  target_link_libraries(
      mainTest  
      ${GTEST_LIBRARIES} 
      Threads::Threads
      libauth-server
      -lgmock
      ${USED_LIBS}
  )

else()
  add_executable(main main.cpp)
  target_link_libraries(main jwt-cpp::jwt-cpp libauth-server ${USED_LIBS} -lboost_iostreams)
endif()
