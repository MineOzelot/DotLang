//
// Created by mineozelot on 25.05.16.
//

#ifndef DOTLANG_PARSER_HPP
#define DOTLANG_PARSER_HPP


#include "Lexer.hpp"
#include "../Node.hpp"
#include "../../lens/TList.hpp"

class Parser {
    Lexer *lex;

    Token *curtok;
    lens::TList<Token *> tokens;

    Token *nextToken();
    Token *prevToken();

    ExprNode *parseStmt();

    ExprNode *parseIdent();
    ExprNode *parseNumber();

    ExprNode *parseExpr();

    ExprNode *error(const char *msg);
public:
    Parser(Lexer *lex);

    ExprNode *parse();
};


#endif //DOTLANG_PARSER_HPP
