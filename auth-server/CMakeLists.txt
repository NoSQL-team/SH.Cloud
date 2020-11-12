cmake_minimum_required(VERSION 3.13.4)

project(auth-server-noskool)
#======================================================================================

option(TESTS "" OFF)

#======================================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "-lpthread -lgtest -lpqxx -lpq")

#======================================================================================

add_library(libauth-server STATIC 
  lib/auth-server/auth-server.cpp
)

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
  )

else()
  add_executable(main main.cpp)
  target_link_libraries(main libauth-server)
endif()
