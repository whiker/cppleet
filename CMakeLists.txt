cmake_minimum_required(VERSION 3.5)
project(cppleet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TwoSum_001.cpp header.h)
add_executable(cppleet ${SOURCE_FILES})

# gtest gmock
include_directories("/usr/local/include")
link_directories("/usr/local/lib")
target_link_libraries(cppleet gtest)
target_link_libraries(cppleet gmock)
target_link_libraries(cppleet pthread)