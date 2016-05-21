//
// Created by mineozelot on 21.05.16.
//

#ifndef DOTLANG_LEX_TESTS_HPP
#define DOTLANG_LEX_TESTS_HPP

#include "Token.hpp"
#include "Lexer.hpp"

/*
 * 0 - d
 * 1 - e
 * 2 - f
 * 3 - =
 * 4 - :
 * 5 - any_digit
 * 6 - any_letter
 * 7 - ' \r\n\t'
 * 8 - +
 * 9 - -
 */
int state_table[][10] {
       // 0    1    2    3    4    5    6    7    8    9
        { 6,   5,   5,   2,   1,   4,   5,   0,  10,  11 }, //state 0
        {-1,  -1,  -1,   3,  -1,  -1,  -1,  -1,  -1,  -1 }, //state 1: :
        {-2,  -2,  -2,   9,  -2,  -2,  -2,  -2,  -2,  -2 }, //state 2: =
        {-3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -4 }, //state 3: :=
        {-4,  -4,  -4,  -4,  -4,   4,  -4,  -4,  -4,  -4 }, //state 4: /number
        { 5,   5,   5,  -5,  -5,   5,   5,  -5,  -5,  -5 }, //state 5: /ident
        { 5,   7,   5,  -5,  -5,   5,   5,  -5,  -5,  -5 }, //state 6: d
        { 5,   5,   8,  -5,  -5,   5,   5,  -5,  -5,  -5 }, //state 7: de
        { 5,   5,   5,  -8,  -8,   5,   5,  -5,  -8,  -8 }, //state 8: def
        {-9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9 }, //state 9: ==
       // 0    1    2    3    4    5    6    7    8    9
        {-10, -10, -10,  12, -10,   4, -10, -10,  14, -10 }, //state 10: +
        {-11, -11, -11,  13, -11,   4, -11, -11,  15, -11 }, //state 11: -
        {-12, -12, -12, -12, -12, -12, -12, -12, -12, -12 }, //state 12: +=
        {-13, -13, -13, -13, -13, -13, -13, -13, -13, -13 }, //state 13: -=
        {-14, -14, -14, -14, -14, -14, -14, -14, -14, -14 }, //state 14: ++
        {-15, -15, -15, -15, -15, -15, -15, -15, -15, -15 }, //state 15: --
};

bool isDigit(char ch);
bool isIdent(char ch);

int getid(char ch) {
    int id = -1;
    switch (ch) {
        case ' ': case '\r': case '\n': case '\t': case 0: id = 7; break;
        case 'd': id = 0; break;
        case 'e': id = 1; break;
        case 'f': id = 2; break;
        case '=': id = 3; break;
        case ':': id = 4; break;

        case '+': id = 8; break;
        case '-': id = 9; break;

        default:
            if(isDigit(ch)) id = 5;
            else if(isIdent(ch)) id = 6;
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
