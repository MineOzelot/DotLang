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
    if(*cur == 0) return new Token(T_EOF, "\\eof");
    return lex();
}

Token *Lexer::lex() {
    char *cur = this->cur;
    int state = 0;
    std::string str;
    while(true) {
        int id = getid(*cur);
        if(id == -1) throw LexerException(std::string("Unrecognized character: ") + *cur);
        int nid = state_table[state][id];
        if(nid == 0) this->cur = ++cur;
        else if(nid < 0) {
            Token *ret = nullptr;
            switch (-nid) {
                case 1: ret = new Token(T_COLON, ":"); break;
                case 2: ret = new Token(T_ASSIGN, "="); break;
                case 3: ret = new Token(T_LAZY_ASSIGN, ":="); break;
                case 4: ret = new Token(T_NUMBER, str); break;
                case 5: ret = new Token(T_IDENT, str); break;
                case 8: ret = new Token(T_KW_DEF, "def"); break;
                case 9: ret = new Token(T_EQUAL, "=="); break;

                case 10: ret = new Token(T_PLUS, "+"); break;
                case 11: ret = new Token(T_MINUS, "-"); break;
                case 12: ret = new Token(T_PLUS_ASSIGN, "+="); break;
                case 13: ret = new Token(T_MINUS_ASSIGN, "-="); break;
                case 14: ret = new Token(T_INCREMENT, "++"); break;
                case 15: ret = new Token(T_DECREMENT, "--"); break;

                default: throw LexerException(std::string("Lexer error: ") + *cur);
            }
            this->cur = cur;
            return ret;
        } else {
            state = nid;
            str += *cur;
            cur++;
        }
    }
}