//
// Created by mineozelot on 21.05.16.
//

#ifndef DOTLANG_TOKEN_HPP
#define DOTLANG_TOKEN_HPP

#include <string>

enum TokenType {
    T_EOF = -1,
    T_IDENT,
    T_NUMBER,
    T_FLOAT,

    T_COLON,
    T_ASSIGN,
    T_LAZY_ASSIGN,
    T_EQUAL,

    T_PLUS, T_MINUS,
    T_PLUS_ASSIGN, T_MINUS_ASSIGN,
    T_INCREMENT, T_DECREMENT,

    T_KW_DEF
};

struct Token {
    TokenType type;
    std::string str;

    Token(TokenType type, std::string str): type(type), str(str) {}
};

#endif //DOTLANG_TOKEN_HPP