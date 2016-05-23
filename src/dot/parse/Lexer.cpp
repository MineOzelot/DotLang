//
// Created by mineozelot on 21.05.16.
//

#include "Lexer.hpp"
#include "lex_table.hpp"

void Lexer::start(char *str) {
    code = str;
    cur = code;
}

Token *Lexer::nextToken() {
    return lex();
}

Token *Lexer::lex() {
    char *cur = this->cur;
    int state = 0;
    std::string str;
    while(true) {
        int id = getid(*cur);
        int nid = state_table[state][id];
        if(nid == 0) {
            this->cur = cur;
            switch (state) {
                case 1:     return new Token(T_COLON,         str);
                case 2:     return new Token(T_ASSIGN,        str);
                case 3:     return new Token(T_LAZY_ASSIGN,   str);
                case 4:     return new Token(T_NUMBER,        str);
                case 5: case 6:
                case 7:     return new Token(T_IDENT,         str);
                case 8:     return new Token(T_KW_DEF,        str);
                case 9:     return new Token(T_EQUAL,         str);
                case 10:    return new Token(T_PLUS,          str);
                case 11:    return new Token(T_MINUS,         str);
                case 12:    return new Token(T_PLUS_ASSIGN,   str);
                case 13:    return new Token(T_MINUS_ASSIGN,  str);
                case 14:    return new Token(T_INCREMENT,     str);
                case 15:    return new Token(T_DECREMENT,     str);
                case 16:    return new Token(T_QUOTE,         str);
                case 17: break;
                case 18:    return new Token(T_EOF,       "\\eof");

                default: throw LexerException(str);
            }
            state = 0;
            str = "";
        } else {
            state = nid;
            str += *cur;
            cur++;
        }
    }
}