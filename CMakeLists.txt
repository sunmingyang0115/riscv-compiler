cmake_minimum_required(VERSION 3.28.2)
project(compiler VERSION 0.0.1 LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
    src/Main.cc
    src/ast/Expressions.cc
    src/parser/BracketHelper.cc
    src/parser/Tokenizer.cc
    src/parser/Parser.cc
    src/codegen/RegAlloc.cc
    src/codegen/Compiler.cc
    src/codegen/HelperFunctions.cc
    src/codegen/CodeGen.cc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")
