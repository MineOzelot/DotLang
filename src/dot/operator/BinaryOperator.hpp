/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  BinaryOperator.hpp
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

#ifndef DOTLANG_BINARYOPERATOR_HPP
#define DOTLANG_BINARYOPERATOR_HPP

#include <vector>
#include "BaseOperator.hpp"
#include "../type/DotVariable.hpp"

class AssignOperator: public BaseAssignOperator {
public:
    AssignOperator(Dot *dot): BaseAssignOperator(dot) {}
    DotValue *exec(ExprNode *node, DotVariable *left, DotValue *right);
};

class MethodOperator: public BaseOperator {
public:
    MethodOperator(Dot *dot): BaseOperator(dot) {}
    DotValue *exec(ExprNode *node, unsigned long id, std::vector<DotValue*> args, Scope *scope);
};

class AddOperator: public BinaryOperator {
public:
    AddOperator(Dot *dot): BinaryOperator(dot) {}
    DotValue *exec(ExprNode *node, DotValue *left, DotValue *right);
};

class SubOperator: public BinaryOperator {
public:
    SubOperator(Dot *dot): BinaryOperator(dot) {}
    DotValue *exec(ExprNode *node, DotValue *left, DotValue *right);
};

class MulOperator: public BinaryOperator {
public:
    MulOperator(Dot *dot): BinaryOperator(dot) {}
    DotValue *exec(ExprNode *node, DotValue *left, DotValue *right);
};

class DivOperator: public BinaryOperator {
public:
    DivOperator(Dot *dot): BinaryOperator(dot) {}
    DotValue *exec(ExprNode *node, DotValue *left, DotValue *right);
};

#endif //DOTLANG_BINARYOPERATOR_HPP