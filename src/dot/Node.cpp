/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Node.cpp
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
#include "Dot.hpp"

DotValue *NumberExprNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    return dot->createNumber(std::stol(dot->getSymTbl()->value(num)));
}

DotValue *StringExprNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    return dot->createString(dot->getSymTbl()->value(str));
}

DotValue *VarExprNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    DotVariable *var = scope->getVariable(name);
    return var ? var->getValue() : dot->getNull();
}

DotValue *UnaryOpNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    return static_cast<UnaryOperator*>(dot->getOperator(op))->exec(this, walker->exec(right));
}

DotValue *BinaryOpNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    return static_cast<BinaryOperator*>(dot->getOperator(op))->exec(this, walker->exec(left), walker->exec(right));
}

DotValue *AssignOpNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    DotVariable *var = scope->getVariable(left->name);
    if(!var) {
        return dot->getNull();
    }
    return static_cast<AssignOperator*>(dot->getOperator(op))->exec(
            this, var,
            walker->exec(right)
    );
}

DotValue *ListNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    walker->enter(this, scope->child());
    return dot->getNull();
}

DotValue *CallNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    std::vector<DotValue *> values;
    for(std::vector<ExprNode *>::iterator it = args.begin(); it != args.end(); it++) {
        if(!(*it)) break;
        else values.push_back(walker->exec(*it));
    }
    return dot->operatorMethod->exec(this, id, values, scope, walker);
}

DotValue *DefVarNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    DotVariable *var;
    if(!(var = scope->getVariable(id))) {
        scope->define(id, (var = new DotVariable(dot)));
    }
    if(right) {
        var->setValue(walker->exec(right));
    }
    return var->getValue();
}

DotValue *DefMethodNode::execute(Dot *dot, Scope *scope, TreeWalker *walker) {
    DotMethod *met = new DefinedMethod(dot, args, code);
    scope->define(id, met);
    return dot->getNull();
}
