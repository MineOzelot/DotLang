/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  lex_table.hpp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DOTLANG_LEX_TESTS_HPP
#define DOTLANG_LEX_TESTS_HPP

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
 * 10 - '"'
 * 11 - eof
 * 12 - '\n'
 * 13 - '('
 * 14 - ')'
 * 15 - ','
 * 16 - any_character
 */
const int state_table[][18] {
       // 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16
       // d    e    f    =    :    0    a         +    -    "   \0   \n    (    )    ,   ac
        { 6,   5,   5,   2,   1,   4,   5,  17,  10,  11,  16,  18,  19,  20,  21,  22,  -1 }, //state 0
        { 0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 1: :
        { 0,   0,   0,   9,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 2: =
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 3: :=
        { 0,   0,   0,   0,   0,   4,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 4: /number
        { 5,   5,   5,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 5: /ident
        { 5,   7,   5,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 6: d
        { 5,   5,   8,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 7: de
        { 5,   5,   5,   0,   0,   5,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 8: def
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 9: ==
       // 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16
        { 0,   0,   0,  12,   0,   4,   0,   0,  14,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 10: +
        { 0,   0,   0,  13,   0,   4,   0,   0,   0,  15,   0,   0,   0,   0,   0,   0,   0 }, //state 11: -
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 12: +=
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 13: -=
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 14: ++
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 15: --
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 16: "
        { 0,   0,   0,   0,   0,   0,   0,  17,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 17: /whitespace
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 18: /eof
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 19: \n
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 20: (
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 21: )
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 22: ,
};

bool isDigit(char ch);
bool isIdent(char ch);

int getid(char ch) {
    int id;
    switch (ch) {
        case 'd': id = 0; break;
        case 'e': id = 1; break;
        case 'f': id = 2; break;
        case '=': id = 3; break;
        case ':': id = 4; break;

        case ' ':
        case '\r':
        case '\t': id = 7; break;
        case '+': id = 8; break;
        case '-': id = 9; break;

        case '\'':
        case '"': id = 10; break;
        case 0:
        case -1: id = 11; break;
        case '\n': id = 12; break;
        case '(': id = 13; break;
        case ')': id = 14; break;
        case ',': id = 15; break;

        default:
            if(isDigit(ch)) id = 5;
            else if(isIdent(ch)) id = 6;
            else {
                std::stringstream msg;
                msg << "Unrecognized character: "
                << ch << "("
                << (int) ch << ")";
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
