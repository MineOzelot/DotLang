cmake_minimum_required(VERSION 3.0)
project(DotLang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        src/lens/TList.hpp
        src/dot/parse/Parser.cpp src/dot/parse/Parser.hpp
        src/main.cpp
        src/dot/parse/Lexer.cpp src/dot/parse/Lexer.hpp
        src/dot/parse/Token.hpp
        src/dot/parse/lex_table.hpp
        src/dot/Node.hpp
        src/dot/Dot.cpp src/dot/Dot.hpp
        src/dot/parse/ParseStmt.cpp
        src/dot/parse/Position.hpp src/dot/parse/Position.cpp)


add_executable(DotLang ${SOURCE_FILES})