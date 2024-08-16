cmake_minimum_required(VERSION 3.28.2)
project(compiler VERSION 0.0.1 LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
    src/Main.cc
    src/ast/Expressions.cc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")
