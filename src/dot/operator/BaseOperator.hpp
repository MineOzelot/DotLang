/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  BaseOperator.hpp
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

#ifndef DOTLANG_BASEOPERATOR_HPP
#define DOTLANG_BASEOPERATOR_HPP


#include "../type/DotValue.hpp"
#include "../type/DotVariable.hpp"
#include "../Node.hpp"

class Dot;

class BaseOperator {
protected:
    Dot *dot;
public:
    BaseOperator(Dot *dot): dot(dot) {};
    virtual ~BaseOperator() {}
};

class UnaryOperator: public BaseOperator {
public:
    UnaryOperator(Dot *dot): BaseOperator(dot) {}
    virtual DotValue *exec(ExprNode *node, DotValue *par) = 0;
    virtual ~UnaryOperator() {}
};

class BinaryOperator: public BaseOperator {
public:
    BinaryOperator(Dot *dot): BaseOperator(dot) {}
    virtual DotValue *exec(ExprNode *node, DotValue *left, DotValue *right) = 0;
    virtual ~BinaryOperator() {}
};

class BaseAssignOperator: public BaseOperator {
public:
    BaseAssignOperator(Dot *dot): BaseOperator(dot) {}
    virtual  DotValue *exec(ExprNode *node, DotVariable *left, DotValue *right) = 0;
    virtual ~BaseAssignOperator() {}
};

#endif //DOTLANG_BASEOPERATOR_HPP
