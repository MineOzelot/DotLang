/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  ParseStmt.cpp
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

#include "Parser.hpp"

ExprNode *Parser::parseStmt() {
    switch (curtok->type) {
        case T_IDENT: return parseIdent();
        default: return error("syntax error");
    }
}

ExprNode *Parser::parseIdent() {
    Token *tok = curtok;
    switch (nextToken()->type) {
        case T_ASSIGN:
        case T_LAZY_ASSIGN: {
            int id;
            if (curtok->type == T_LAZY_ASSIGN) id = 1; else id = 0;
            VarExprNode *left = new VarExprNode(tok->symbol_id);
            nextToken();
            ExprNode *right = parseExpr();
            return new AssignOpNode(id, left, right);
        } case T_LPARENT: {
            nextToken();
            return new CallNode(tok->symbol_id, (ListNode *) parseArgList());
        } default:
            return new VarExprNode(tok->symbol_id);
    }
}

ExprNode *Parser::parseArgList() {
    ListNode *ret = new ListNode();
    while(curtok->type != T_RPARENT) {
        ExprNode *node = parseExpr();
        ListNode *next = new ListNode();
        ret->val = node;
        next->prev = ret;
        ret->next = next;
        if(nextToken()->type != T_COMMA && curtok->type != T_RPARENT) return error("syntax error");
    }
    nextToken();
    return ret;
}

ExprNode *Parser::parseExpr() {
    switch (curtok->type) {
        case T_IDENT: return parseIdent();
        case T_NUMBER: return parseNumber();
        default: return error("syntax error");
    }
}

ExprNode *Parser::parseNumber() {
    ExprNode *node = new NumberExprNode(curtok->symbol_id);
    nextToken();
    return node;
}