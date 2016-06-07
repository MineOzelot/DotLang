/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Lexer.cpp
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

#include "Lexer.hpp"
#include "lex_table.hpp"

void Lexer::start(std::istream *str, SymbolTable *symtbl) {
    code = str;
    cur = (char) str->get();
    sym = symtbl;
}

Token *Lexer::nextToken() {
    return lex();
}

Token *Lexer::lex() {
    int state = 0;
    token_start = pos;
    str = "";
    while(true) {
        int id = getid(cur);
        int nid = state_table[state][id];
        if(nid == 0) {
            switch (state) {
                case 1:     return new Token(T_COLON, token_start, 0);
                case 2:     return new Token(T_ASSIGN, token_start, 0);
                case 3:     return new Token(T_LAZY_ASSIGN, token_start, 0);
                case 4:     return new Token(T_NUMBER, token_start, addsym());
                case 5:
                case 6:
                case 7:     return new Token(T_IDENT, token_start, addsym());
                case 8:     return new Token(T_KW_DEF, token_start, 0);
                case 9:     return new Token(T_EQUAL, token_start, 0);
                case 10:    return new Token(T_PLUS, token_start, 0);
                case 11:    return new Token(T_MINUS, token_start, 0);
                case 12:    return new Token(T_PLUS_ASSIGN, token_start, 0);
                case 13:    return new Token(T_MINUS_ASSIGN, token_start, 0);
                case 14:    return new Token(T_INCREMENT, token_start, 0);
                case 15:    return new Token(T_DECREMENT, token_start, 0);
                case 16:    return new Token(T_QUOTE, token_start, 0);
                case 17:    break;
                case 18:    return new Token(T_EOF, token_start, 0);
                case 19:    pos.line(); break;

                default: throw LexerException(str);
            }
            state = 0;
            token_start = pos;
            str = "";
        } else {
            state = nid;
            str += cur;
            cur = (char) code->get();
            pos.next();
        }
    }
}

unsigned long Lexer::addsym() {
    for(SymbolTable::iterator it = sym->begin(); it != sym->end(); it++)
        if(*(it->second) == str)
            return it->first;
    unsigned long id = cur_id++;
    sym->insert(std::pair<unsigned long, std::string*>(id, new std::string(str)));
    return id;
}

SymbolTable *Lexer::getSymTbl() {
    return sym;
}