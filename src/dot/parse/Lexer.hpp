//
// Created by mineozelot on 21.05.16.
//

#ifndef DOTLANG_LEXER_HPP
#define DOTLANG_LEXER_HPP


#include <sstream>
#include <map>
#include "Token.hpp"

typedef std::map<unsigned long, std::string*> SymbolTable;

class Lexer {
    std::istream *code;
    char cur;
    std::string str;

    Position pos;
    Position token_start;

    unsigned long cur_id = 1;
    SymbolTable *sym = nullptr;

    Token *lex();
    unsigned long addsym();
public:
    //void start(char *str, SymbolTable *symtbl);
    void start(std::istream *str, SymbolTable *symtbl);
    Token *nextToken();

    SymbolTable *getSymTbl();
};


#endif //DOTLANG_LEXER_HPP
