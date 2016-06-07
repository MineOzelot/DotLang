//
// Created by mineozelot on 05.06.16.
//

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
        } default:
            return new VarExprNode(tok->symbol_id);
    }
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