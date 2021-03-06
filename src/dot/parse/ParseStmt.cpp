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

#include <vector>
#include "Parser.hpp"


ExprNode *Parser::parseStmt() {
    switch (curtok->type) {
        case T_IDENT: return parseIdent();

        case T_KW_VAR: return parseVarKW();
        case T_KW_DEF: return parseDefKW();

        case T_LBRACE: return parseBraces();
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
            if(isOperator(curtok->type)) return parseOperator(new VarExprNode(tok->symbol_id));
            return new VarExprNode(tok->symbol_id);
    }
}

std::vector<ExprNode*> Parser::parseArgList() {
    std::vector<ExprNode*> ret;
    while(true) {
        if(curtok->type == T_RPARENT) break;
        ExprNode *node = parseExpr();
        ret.push_back(node);
        if(curtok->type == T_RPARENT) break;
        if(curtok->type == T_COMMA) { nextToken(); continue; }
        else error("syntax error");
    }
    nextToken();
    return ret;
}

ExprNode *Parser::parseExpr() {
    switch (curtok->type) {
        case T_IDENT: return parseIdent();
        case T_NUMBER: return parseNumber();
        case T_STRING: return parseString();
        case T_LBRACE: return parseBraces();
        default: return error("syntax error");
    }
}

ExprNode *Parser::parseNumber() {
    NumberExprNode *left = new NumberExprNode(curtok->symbol_id);
    if(isOperator(nextToken()->type)) return parseOperator(left);
    return left;
}

ExprNode *Parser::parseString() {
    StringExprNode *left = new StringExprNode(curtok->symbol_id);
    if(isOperator(nextToken()->type)) return parseOperator(left);
    return left;
}

ExprNode *Parser::parseValue() {
    ExprNode *ret;
    switch (curtok->type) {
        case T_IDENT: ret = new VarExprNode(curtok->symbol_id); break;
        case T_NUMBER: ret = new NumberExprNode(curtok->symbol_id); break;
        case T_STRING: ret = new StringExprNode(curtok->symbol_id); break;
        default: return error("syntax error");
    }
    nextToken();
    return ret;
}

ExprNode *Parser::parseOperator(ExprNode *left) {
    Token *cur = curtok;
    int id = getTokenOperatorId(curtok->type);
    nextToken();
    if(isOperator(nextToken()->type)
       && getTokenPrecedence(curtok->type) < getTokenPrecedence(cur->type)) {
        prevToken();
        return parseOperator(new BinaryOpNode(id, left, parseValue()));
    };
    prevToken();
    return new BinaryOpNode(id, left, parseExpr());
}

ExprNode *Parser::parseBraces() {
    nextToken();
    lens::TList<ExprNode *> *list = new lens::TList<ExprNode *>();
    while(true) {
        if(curtok->type == T_RBRACE) break;
        else if(curtok->type == T_EOF) return error("expected }");
        list->push_back(parseStmt());
    }
    nextToken();
    return new ListNode(list);
}

ExprNode *Parser::parseVarKW() {
    switch(nextToken()->type) {
        case T_IDENT: {
            unsigned long sym = curtok->symbol_id;
            if(nextToken()->type == T_ASSIGN) {
                nextToken();
                ExprNode *right = parseExpr();
                return new DefVarNode(sym, right);
            } else {
                return new DefVarNode(sym, nullptr);
            }
        } default: return error("syntax error");
    }
}

ExprNode *Parser::parseDefKW() {
    switch(nextToken()->type) {
        case T_IDENT: {
            unsigned long sym = curtok->symbol_id;
            std::vector<unsigned long> args;
            if(nextToken()->type == T_LPARENT) {
                nextToken();
                while(true) {
                    if(curtok->type == T_RPARENT) { nextToken(); break; }
                    else if(curtok->type == T_EOF) return error("expected )");
                    args.push_back(curtok->symbol_id);
                    if(nextToken()->type == T_RPARENT) { nextToken(); break; }
                    if(curtok->type == T_COMMA) { nextToken(); continue; }
                    else error("syntax error");
                }
                return new DefMethodNode(sym, args, static_cast<ListNode *>(parseBraces()));
            } else {
                return error("syntax error");
            }
        } default: return error("syntax error");
    }
}