/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Lexer.hpp
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

#ifndef DOTLANG_LEXER_HPP
#define DOTLANG_LEXER_HPP


#include <sstream>
#include <map>
#include "Token.hpp"

struct SymbolTable {
    std::map<unsigned long, std::string*> map;
    unsigned long cur = 1;
};

class Lexer {
    std::istream *code;
    char cur;
    std::string str;

    Position pos;
    Position token_start;

    SymbolTable *sym = nullptr;

    Token *lex();
    unsigned long addsym();

    Token *lexString();
public:
    void start(std::istream *str, SymbolTable *symtbl);
    Token *nextToken();

    SymbolTable *getSymTbl();
};


#endif //DOTLANG_LEXER_HPP
