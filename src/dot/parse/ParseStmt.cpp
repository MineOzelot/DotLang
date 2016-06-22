#include "Parser.hpp"


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
            int id = getTokenOperatorId(curtok->type);
            VarExprNode *left = new VarExprNode(tok->symbol_id);
            nextToken();
            ExprNode *right = parseExpr();
            return new AssignOpNode(id, left, right);
        } case T_LPARENT: {
            nextToken();
            return new CallNode(tok->symbol_id, parseArgList());
        } default:
            if(isOperator(curtok->type)) {
                int id = getTokenOperatorId(curtok->type);
                VarExprNode *left = new VarExprNode(tok->symbol_id);
                nextToken();
                return new BinaryOpNode(id, left, parseExpr());
            }
            return new VarExprNode(tok->symbol_id);
    }
}

ListNode *Parser::parseArgList() {
    ListNode *ret = new ListNode();
    ListNode *cur = ret;
    while(true) {
        ExprNode *node = parseExpr();
        ListNode *next = new ListNode();
        cur->val = node;
        next->prev = cur;
        cur->next = next;
        cur = next;
        if(curtok->type == T_COMMA) { nextToken(); continue; }
        if(curtok->type == T_RPARENT) break;
        else return (ListNode *) error("syntax error");
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
    if(isOperator(nextToken()->type)) {
        int id = getTokenOperatorId(curtok->type);
        NumberExprNode *left = new NumberExprNode(tok->symbol_id);
        nextToken();
        return new BinaryOpNode(id, left, parseExpr());
    }
    return new NumberExprNode(tok->symbol_id);
}

ExprNode *Parser::parseString() {
    Token *tok = curtok;
    if(isOperator(nextToken()->type)) {
        int id = getTokenOperatorId(curtok->type);
        StringExprNode *left = new StringExprNode(tok->symbol_id);
        nextToken();
        return new BinaryOpNode(id, left, parseExpr());
    }
    return new StringExprNode(tok->symbol_id);
}
