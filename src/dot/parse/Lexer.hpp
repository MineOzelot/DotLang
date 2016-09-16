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

class SymbolTable {
    std::map<unsigned long, std::string> *val_map;
    std::map<std::string, unsigned long> *key_map;
    unsigned long cur = 0;
public:
    SymbolTable() {
        val_map = new std::map<unsigned long, std::string>();
        key_map = new std::map<std::string, unsigned long>();
    }

    unsigned long id(std::string &str) {
        return key_map->operator[](str);
    }

    std::string value(unsigned long sym) {
        return std::string(val_map->operator[](sym));
    }

    unsigned long add(std::string &str) {
        cur++;
        val_map->insert(std::pair<unsigned long, std::string>(cur, str));
        key_map->insert(std::pair<std::string, unsigned long>(str, cur));
        return cur;
    }

    bool contains(std::string &str) {
        return key_map->count(str) > 0;
    }

    ~SymbolTable() {
        delete val_map;
        delete key_map;
    }
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

    char get();

    Token *lexString();
public:
    void start(std::istream *str, SymbolTable *symtbl);
    Token *nextToken();

    SymbolTable *getSymTbl();
};


#endif //DOTLANG_LEXER_HPP
