/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Parser.cpp
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
#include "Parser.hpp"


Parser::Parser(Lexer *lex): lex(lex) {}

ExprNode *Parser::parse() {
    tokens.push_back(lex->nextToken());
    curtok = tokens.get();
    ListNode *list = new ListNode();
    ListNode *cur = list;
    while (curtok->type != T_EOF) {
        cur->val = parseStmt();
        cur->next = new ListNode();
        cur->next->prev = cur;
        cur = cur->next;
    }
    tokens.to_end();
    do {
        delete tokens.get();
        tokens.prev();
    } while(!tokens.is_head());
    tokens.clear();
    return list;
}

bool Parser::isOperator(TokenType t) {
    switch(t) {
        case T_PLUS:
        case T_MINUS:
        case T_MUL:
        case T_DIV:
            return true;
        default:
            return false;
    }
}

int Parser::getTokenOperatorId(TokenType t) {
    switch(t) {
        case T_ASSIGN: return 0;
        case T_LAZY_ASSIGN: return 1;
        case T_PLUS: return 2;
        case T_MINUS: return 3;
        case T_MUL: return 4;
        case T_DIV: return 5;
        default: return -1;
    }
}

int Parser::getTokenPrecedence(TokenType t) {
    switch(t) {
        case T_ASSIGN: case T_LAZY_ASSIGN: return 0;
        case T_PLUS: case T_MINUS: return 10;
        case T_MUL: case T_DIV: return 20;
        default: return 0;
    }
}

Token *Parser::nextToken() {
    if(tokens.is_end())
        tokens.push_back(lex->nextToken());
    curtok = tokens.next();
    return curtok;
}

Token *Parser::prevToken() {
    curtok = tokens.prev();
    return curtok;
}

ExprNode *Parser::error(const char *msg) {
    std::cout << msg << " at " << curtok->pos << std::endl;
    return nullptr;
}
