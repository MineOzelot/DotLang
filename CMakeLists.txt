cmake_minimum_required(VERSION 3.0)
project(DotLang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
        src/dot/parse/Position.hpp src/dot/parse/Position.cpp
        src/dot/NodeExecutor.cpp src/dot/NodeExecutor.hpp
        src/dot/Exception.hpp
        src/dot/type/DotValue.cpp src/dot/type/DotValue.hpp
        src/dot/operator/BaseOperator.hpp
        src/dot/operator/BinaryOperator.hpp src/dot/operator/BinaryOperator.cpp
        src/dot/type/DotVariable.cpp src/dot/type/DotVariable.hpp
        src/dot/type/DotType.cpp src/dot/type/DotType.hpp
        src/dot/type/DotMethod.cpp src/dot/type/DotMethod.hpp
        )


add_executable(DotLang ${SOURCE_FILES})