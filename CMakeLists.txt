cmake_minimum_required(VERSION 3.5)
include(bin/cppleet.cmake)
project(cppleet)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
set(CMAKE_BUILD_TYPE Debug ON)
set(CMAKE_CXX_COMPILER "g++")

# -g3     生成调试信息
# -ggdb   让编译器(g++)生成专用于gdb的调试信息
# -O0     关闭编译器优化
# -Wall   打开所有警告
# -Werror 任一警告都是错误，都会停止编译过程
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -ggdb -O0 -Wall -Werror")

# gtest
include_and_link(${CMAKE_SOURCE_DIR}/ext/gtest)

# executable
set(SOURCE_FILES "")
append_source_files(SOURCE_FILES "src")
include_directories("include")
add_executable(cppleet ${SOURCE_FILES})

# gtest
target_link_libraries(cppleet gtest)