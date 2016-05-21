//
// Created by mineozelot on 21.05.16.
//

#ifndef DOTLANG_LEXER_HPP
#define DOTLANG_LEXER_HPP


#include <sstream>
#include "Token.hpp"

struct LexerException {
    std::string msg;
    LexerException(std::string msg): msg(msg) {}
};

class Lexer {
    char *code;
    char *cur;

    Token *lex();
public:
    void start(char *str);
    Token *nextToken();
};


#endif //DOTLANG_LEXER_HPP
