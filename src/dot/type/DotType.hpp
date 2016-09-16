/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  DotType.hpp
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

#ifndef DOTLANG_DOTTYPE_HPP
#define DOTLANG_DOTTYPE_HPP


#include <string>

class Dot;
class DotValue;

class DotType {
protected:
    std::string name;
    Dot *dot;
public:
    DotType(Dot *dot, const std::string &name);

    virtual DotValue *create();

    virtual DotValue *add(DotValue *num1, DotValue *num2);
    virtual DotValue *sub(DotValue *num1, DotValue *num2);
    virtual DotValue *mul(DotValue *num1, DotValue *num2);
    virtual DotValue *div(DotValue *num1, DotValue *num2);

    virtual DotValue *to_str(DotValue *val);

    virtual ~DotType() {}
};

class DotNumber: public DotType {
public:
    DotNumber(Dot *dot);
    DotValue *create(long num);
    DotValue *add(DotValue *num1, DotValue *num2);
    DotValue *sub(DotValue *num1, DotValue *num2);
    DotValue *mul(DotValue *num1, DotValue *num2);
    DotValue *div(DotValue *num1, DotValue *num2);

    DotValue *to_str(DotValue *val);
};

class DotString: public DotType { //todo: Функцию для перевода в std::string
public:
    DotString(Dot *dot);
    DotValue *create(std::string str);
    DotValue *add(DotValue *str1, DotValue *str2);

    DotValue *to_str(DotValue *val);
};


#endif //DOTLANG_DOTTYPE_HPP
