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
            return new CallNode(tok->symbol_id, parseArgList());
        } case T_PLUS:
        case T_MINUS: {
            int id;
            if(curtok->type == T_PLUS) id = 2; else id = 3;
            VarExprNode *left = new VarExprNode(tok->symbol_id);
            nextToken();
            return new BinaryOpNode(id, left, parseExpr());
        } default:
            return new VarExprNode(tok->symbol_id);
    }
}

ListNode *Parser::parseArgList() {
    ListNode *ret = new ListNode();
    ListNode *cur = ret;
    while(curtok->type != T_RPARENT) {
        ExprNode *node = parseExpr();
        ListNode *next = new ListNode();
        cur->val = node;
        next->prev = cur;
        cur->next = next;
        cur = next;
        if(curtok->type != T_COMMA && curtok->type != T_RPARENT) return (ListNode *) error("syntax error");
    }
    nextToken();
    return ret;
}

ExprNode *Parser::parseExpr() {
    switch (curtok->type) {
        case T_IDENT: return parseIdent();
        case T_NUMBER: return parseNumber();
        case T_STRING: return parseString();
        default: return error("syntax error");
    }
}

ExprNode *Parser::parseNumber() {
    Token *tok = curtok;
    switch(nextToken()->type) {
        case T_PLUS:
        case T_MINUS: {
            int id;
            if(curtok->type == T_PLUS) id = 2; else id = 3;
            NumberExprNode *left = new NumberExprNode(tok->symbol_id);
            nextToken();
            return new BinaryOpNode(id, left, parseExpr());
        } default:
            return new NumberExprNode(tok->symbol_id);
    }
}

ExprNode *Parser::parseString() {
    Token *tok = curtok;
    switch(nextToken()->type) {
        case T_PLUS:
        case T_MINUS: {
            int id;
            if(curtok->type == T_PLUS) id = 2; else id = 3;
            StringExprNode *left = new StringExprNode(tok->symbol_id);
            nextToken();
            return new BinaryOpNode(id, left, parseExpr());
        } default:
            return new StringExprNode(tok->symbol_id);
    }
}

