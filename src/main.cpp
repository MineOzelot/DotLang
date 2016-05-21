//
// Created by mineozelot on 21.05.16.
//


#include <sstream>
#include <iostream>
#include "dot/parse/Lexer.hpp"

int main(int argc, char **argv) {
    Lexer *lex = new Lexer();

    try {
        lex->start(
                "ident IDENT id3nt\n"
                        "1 23 456 +11 -23\n"
                        ": = :=\n"
                        "== + - += -= ++ --\n"
                        "def x");
    } catch (LexerException e) {
        std::cerr << "Lexer error: " << e.msg << std::endl;
        exit(-1);
    }
    Token *tok;
    do {
        try {
            tok = lex->nextToken();
        } catch (LexerException e) {
            std::cerr << e.msg << std::endl;
            exit(-1);
        }
        std::cout << "Token: " << tok->type << " : " << tok->str << std::endl;
    } while(tok->type != T_EOF);

    delete lex;
}