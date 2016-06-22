/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Parser.hpp
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

#ifndef DOTLANG_PARSER_HPP
#define DOTLANG_PARSER_HPP


#include "Lexer.hpp"
#include "../Node.hpp"
#include "../../lens/TList.hpp"

class Parser {
    Lexer *lex;

    Token *curtok;
    lens::TList<Token *> tokens;

    bool isOperator(TokenType t);
    int getTokenOperatorId(TokenType t);

    Token *nextToken();
    Token *prevToken();

    ExprNode *parseStmt();

    ExprNode *parseIdent();
    ExprNode *parseNumber();
    ExprNode *parseString();

    ExprNode *parseExpr();

    ListNode *parseArgList();

    ExprNode *error(const char *msg);
public:
    Parser(Lexer *lex);

    ExprNode *parse();
};


#endif //DOTLANG_PARSER_HPP
