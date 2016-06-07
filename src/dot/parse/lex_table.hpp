//
// Created by mineozelot on 21.05.16.
//

#ifndef DOTLANG_LEX_TESTS_HPP
#define DOTLANG_LEX_TESTS_HPP

#include "Token.hpp"
#include "Lexer.hpp"
#include "../Exception.hpp"

/*
 * 0 - 'd'
 * 1 - 'e'
 * 2 - 'f'
 * 3 - '='
 * 4 - ':'
 * 5 - any_digit
 * 6 - any_letter
 * 7 - [ \r\t]
 * 8 - '+'
 * 9 - '-'
 * 10 - ["']
 * 11 - eof
 * 12 - '\n'
 * 13 - '.'
 * 14 - 'x'
 * 15 - '0'
 */
const int state_table[][16] {
       // 0    1    2    3    4    5    6    7    8    9   10   11   12
       // d    e    f    =    :    0    a         +    -   "'   \0   \n
        { 6,   5,   5,   2,   1,   4,   5,  17,  10,  11,  16,  18,  19 }, //state 0
        { 0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 1: :
        { 0,   0,   0,   9,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 2: =
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 3: :=
        { 0,   0,   0,   0,   0,   4,   0,   0,   0,   0,   0,   0,   0 }, //state 4: /number
        { 5,   5,   5,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0 }, //state 5: /ident
        { 5,   7,   5,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0 }, //state 6: d
        { 5,   5,   8,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0 }, //state 7: de
        { 5,   5,   5,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0 }, //state 8: def
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 9: ==
       // 0    1    2    3    4    5    6    7    8    9   10   11   12
        { 0,   0,   0,  12,   0,   4,   0,   0,  14,   0,   0,   0,   0 }, //state 10: +
        { 0,   0,   0,  13,   0,   4,   0,   0,   0,  15,   0,   0,   0 }, //state 11: -
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 12: +=
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 13: -=
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 14: ++
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 15: --
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 16: "
        { 0,   0,   0,   0,   0,   0,   0,  17,   0,   0,   0,   0,   0 }, //state 17: /whitespace
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 18: /eof
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 19: \n
};

bool isDigit(char ch);
bool isIdent(char ch);

int getid(char ch) {
    int id;
    switch (ch) {
        case '\n': id = 12; break;
        case ' ': case '\r': case '\t': id = 7; break;
        case 0: case -1: id = 11; break;
        case 'd': id = 0; break;
        case 'e': id = 1; break;
        case 'f': id = 2; break;
        case '=': id = 3; break;
        case ':': id = 4; break;

        case '+': id = 8; break;
        case '-': id = 9; break;
        case '\'': case '"': id = 10; break;

        default:
            if(isDigit(ch)) id = 5;
            else if(isIdent(ch)) id = 6;
            else {
                std::stringstream msg;
                msg << "Unrecognized character: "
                << ch << "("
                << (int)ch << ")";
                throw LexerException(msg.str());
            }
    }
    return id;
}

bool isDigit(char ch) {
    switch (ch) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return true;
        default:
            return false;
    }
}

bool isIdent(char ch) {
    switch (ch) {
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
        case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
        case 'V': case 'W': case 'X': case 'Y': case 'Z':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
        case 'v': case 'w': case 'x': case 'y': case 'z':
        case '_': case '$':
            return true;
        default:
            return false;
    }
}

#endif //DOTLANG_LEX_TESTS_HPP
