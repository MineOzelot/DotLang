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
 * 5 - '\r'
 * 6 - '\t'
 * 7 - '+'
 * 8 - '-'
 * 9 - '\"'
 * 10 - eof
 * 11 - '\n'
 * 12 - '('
 * 13 - ')'
 * 14 - ','
 * 15 - '*'
 * 16 - '/'
 *
 * 17 - any_digit
 * 18 - any_letter
 */
const char chars[] = "def=:\r\t +-\"\0\n(),*/";
const int lex_table[][20] {
       // 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
       // d    e    f    =    :   \r   \t         +    -    "   \0   \n    (    )    ,    *    /   ad   al
        { 6,   5,   5,   2,   1,  17,  17,  17,  10,  11,  16,  18,  19,  20,  21,  22,  23,  24,   4,   5 }, //state 0
        { 0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 1: :
        { 0,   0,   0,   9,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 2: =
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 3: :=
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   0 }, //state 4: /number
        { 5,   5,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5 }, //state 5: /ident
        { 5,   7,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5 }, //state 6: d
        { 5,   5,   8,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5 }, //state 7: de
        { 5,   5,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5 }, //state 8: def
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 9: ==
        { 0,   0,   0,  12,   0,   0,   0,   0,  14,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 10: +
        { 0,   0,   0,  13,   0,   0,   0,   0,   0,  15,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 11: -
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 12: +=
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 13: -=
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 14: ++
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 15: --
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 16: "
        { 0,   0,   0,   0,   0,  17,  17,  17,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 17: /whitespace
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 18: /eof
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 19: \n
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 20: (
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 21: )
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 22: ,
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 23: *
        { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }, //state 24: /
};
const int chars_size = sizeof(chars) / sizeof(char) - 1;

inline bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isLetter(char ch) {
    if(ch >= 'a' && ch <= 'z') return true;
    if(ch >= 'A' && ch <= 'Z') return true;
    return ch == '_' || ch == '$';
}

int getid(char ch) {
    for(int c = 0; c < chars_size; c++) if(chars[c] == ch) return c;

    if(isLetter(ch)) return chars_size + 1;
    else if(isDigit(ch)) return chars_size;
    else if(ch == -1) return 11;
    else {
        std::stringstream msg;
        msg << "Unrecognized character: " << ch << "(" << (int) ch << ")";
        throw LexerException(msg.str());
    }
}

#endif //DOTLANG_LEX_TESTS_HPP
