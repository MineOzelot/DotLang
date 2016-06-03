//
// Created by mineozelot on 21.05.16.
//


#include <sstream>
#include <iostream>

#include "dot/parse/Lexer.hpp"
#include "dot/parse/Parser.hpp"

int main(int argc, char **argv) {
    Lexer *lex = new Lexer();
    Parser *parser = new Parser(lex);

    try {
        SymbolTable *sym = new SymbolTable();
        lex->start(
                //(char *) "x = 7 y = 5", sym);
                &(std::cin), sym);
        /*while(true) {
            Token *tok = lex->nextToken();
            std::cout
            << "Token(" << tok->type << ", "
            << tok->symbol_id << ", ("
            << tok->pos.col << ", "
            << tok->pos.row << "))\n";
            if(tok->type == T_EOF) break;
        }*/
        ExprNode *node = parser->parse();
        SymbolTable *tbl = lex->getSymTbl();
        std::cout << "Symbol Table: \n";
        for(SymbolTable::iterator it = tbl->begin(); it != tbl->end(); it++) {
            std::cout << it->first << " : " << it->second << std::endl;
        }
    } catch (LexerException e) {
        std::cerr << "Lexer error: " << e.msg << std::endl;
        exit(-1);
    }

    delete parser;
    delete lex;
}