cmake_minimum_required(VERSION 3.28.2)
project(compiler VERSION 0.0.1 LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
    src/Main.cc
    src/ast/BinOp.cc
    src/ast/Expression.cc
    src/ast/Literal.cc
    src/ast/Sequence.cc
    # src/ast/Variable.cc
    # src/ast/Declare.cc
    # src/ast/Set.cc
    # src/ast/While.cc
    src/lexer/Parser.cc
    src/lexer/Tokenizer.cc
    src/lexer/BracketUtil.cc
    src/visitors/CompileVisitor.cc
    src/visitors/StringVisitor.cc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")
