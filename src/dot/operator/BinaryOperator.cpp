/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  BinaryOperator.cpp
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

#include "BinaryOperator.hpp"
#include "../Dot.hpp"


DotValue *AssignOperator::exec(ExprNode *node, DotVariable *left, DotValue *right) {
    left->setValue(right);
    return right;
}

DotValue *MethodOperator::exec(ExprNode *node, unsigned long id, std::vector<DotValue*> args, Scope *scope, TreeWalker *walker) { //todo: Переделать
    return scope->getMethod(id)->call(scope, args, walker);
}

inline DotValue *AddOperator::exec(ExprNode *node, DotValue *left, DotValue *right) {
    return left->getType()->add(left, right);
}

inline DotValue *SubOperator::exec(ExprNode *node, DotValue *left, DotValue *right) {
    return left->getType()->sub(left, right);
}

inline DotValue *MulOperator::exec(ExprNode *node, DotValue *left, DotValue *right) {
    return left->getType()->mul(left, right);
}

inline DotValue *DivOperator::exec(ExprNode *node, DotValue *left, DotValue *right) {
    return left->getType()->div(left, right);
}