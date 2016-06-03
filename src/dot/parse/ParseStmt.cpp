//
// Created by mineozelot on 05.06.16.
//

#include <iostream>
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
            if (curtok->type == T_LAZY_ASSIGN) {
                id = 3;
                std::cout << "There's a lazy assign!\n";
            } else {
                id = 2;
                std::cout << "There's an assign!\n";
            }
            ExprNode *left = new VarExprNode(tok->symbol_id);
            nextToken();
            ExprNode *right = parseExpr();
            std::cout << "(" << ((VarExprNode *) left)->name
            << ", ";
            if(right->type() == NUMBER)
                std::cout << ((NumberExprNode *) right)->num << ")\n";
            else
                std::cout << ((VarExprNode *) right)->name << ")\n";
            return new BinaryOpNode(id, left, right);
        } default:
            return new VarExprNode(prevToken()->symbol_id);
    }
}

ExprNode *Parser::parseExpr() {
    switch (curtok->type) {
        case T_IDENT: {
            ExprNode *node = new VarExprNode(curtok->symbol_id);
            nextToken();
            return node;
        } case T_NUMBER: return parseNumber();
        default: return error("syntax error");
    }
}

ExprNode *Parser::parseNumber() {
    ExprNode *node = new NumberExprNode(curtok->symbol_id);
    nextToken();
    return node;
}