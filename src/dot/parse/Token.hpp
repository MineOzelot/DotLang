/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Token.hpp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

    T_PLUS, T_MINUS,
    T_MUL, T_DIV,
    T_PLUS_ASSIGN, T_MINUS_ASSIGN,
    T_INCREMENT, T_DECREMENT,

    T_LPARENT, T_RPARENT,
    T_LBRACE, T_RBRACE,
    T_COMMA, T_STRING,

    T_KW_DEF, T_KW_VAR
};

struct Token {
    TokenType type;
    unsigned long symbol_id;
    Position pos;

    Token(TokenType type, Position pos, unsigned long symbol_id): type(type), pos(pos), symbol_id(symbol_id) {}
};

#endif //DOTLANG_TOKEN_HPP
