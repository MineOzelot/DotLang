//
// Created by mineozelot on 25.05.16.
//

#include <iostream>
#include "Parser.hpp"


Parser::Parser(Lexer *lex): lex(lex) {}

ExprNode *Parser::parse() {
    tokens.push_back(lex->nextToken());
    curtok = tokens.get();
    ListNode *list = new ListNode();
    while (curtok->type != T_EOF) {
        list->val = parseStmt();
        list->next = new ListNode();
        list->next->prev = list;
        list = list->next;
    }
    tokens.to_end();
    do {
        delete tokens.get();
        tokens.prev();
    } while(!tokens.is_head());
    tokens.clear();
    return list;
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
