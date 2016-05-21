cmake_minimum_required(VERSION 3.0)
project(DotLang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        src/main.cpp
        src/dot/parse/Lexer.cpp src/dot/parse/Lexer.hpp
        src/dot/parse/Token.hpp
        src/dot/parse/lex_table.hpp
        )


add_executable(DotLang ${SOURCE_FILES})