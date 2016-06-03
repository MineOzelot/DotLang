//
// Created by mineozelot on 21.05.16.
//

#ifndef DOTLANG_TOKEN_HPP
#define DOTLANG_TOKEN_HPP

#include <string>
#include "Position.hpp"

enum TokenType {
    T_EOF = -1,
    T_IDENT,
    T_NUMBER,
    T_ASSIGN,

    T_COLON,
    T_LAZY_ASSIGN,
    T_EQUAL,

    T_QUOTE,

    T_PLUS, T_MINUS,
    T_PLUS_ASSIGN, T_MINUS_ASSIGN,
    T_INCREMENT, T_DECREMENT,

    T_KW_DEF
};

struct Token {
    TokenType type;
    unsigned long symbol_id;
    Position pos;

    Token(TokenType type, Position pos, unsigned long symbol_id): type(type), pos(pos), symbol_id(symbol_id) {}
};

#endif //DOTLANG_TOKEN_HPP
