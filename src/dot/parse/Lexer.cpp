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

#include <iostream>
#include "Lexer.hpp"
#include "lex_table.hpp"

void Lexer::start(std::istream *str, SymbolTable *symtbl) {
    code = str;
    cur = get();
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
        int id = getid(cur, pos);
        int nid;
        if(id == -1 || (nid = lex_table[state][id]) == 0) {
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
                case 16:    return lexString();
                case 17:    break;
                case 18:    return new Token(T_EOF, token_start, 0);
                case 19:    pos.line(); break;
                case 20:    return new Token(T_LPARENT, token_start, 0);
                case 21:    return new Token(T_RPARENT, token_start, 0);
                case 22:    return new Token(T_COMMA, token_start, 0);
                case 23:    return new Token(T_MUL, token_start, 0);
                case 24:    return new Token(T_DIV, token_start, 0);
                case 25:    return new Token(T_LBRACE, token_start, 0);
                case 26:    return new Token(T_RBRACE, token_start, 0);
                case 27:
                case 28:    return new Token(T_IDENT, token_start, addsym());
                case 29:    return new Token(T_KW_VAR, token_start, 0);

                default: throw LexerException(str);
            }
            state = 0;
            token_start = pos;
            str = "";
        } else {
            state = nid;
            str += cur;
            cur = get();
        }
    }
}

unsigned long Lexer::addsym() {
    if(sym->contains(str))
        return sym->id(str);
    std::string s = std::string(str);
    return sym->add(s);
}

SymbolTable *Lexer::getSymTbl() {
    return sym;
}

Token *Lexer::lexString() {
    str = "";
    while(cur != '"') {
        if(cur == '\0') {
            std::stringstream msg;
            msg << "Unrecognized character: "
                << cur << "("
                << (int) cur << ")"
                << " at " << pos;
            throw LexerException(msg.str());
        } else if(cur == '\\') {
            pos.next();
            switch(get()) {
                case '0': cur = '\0'; break;
                case 'a': cur = '\a'; break;
                case 'b': cur = '\b'; break;
                case 't': cur = '\t'; break;
                case 'n': cur = '\n'; break;
                case 'v': cur = '\v'; break;
                case 'f': cur = '\f'; break;
                case 'r': cur = '\r'; break;

                case '"': cur = '"'; break;
                case '\'': cur = '\''; break;
                case '\\': cur = '\\'; break;
                case '/': cur = '/'; break;

                default: continue;
            }
        } else if(cur == '\n') {
            cur = get();
            continue;
        }
        str += cur;
        cur = get();
    }
    cur = get();
    return new Token(T_STRING, token_start, addsym());
}

char Lexer::get() {
    pos.next();
    return (char) code->get();
}
