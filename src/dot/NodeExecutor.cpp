/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  NodeExecutor.cpp
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

#include <iostream>
#include "NodeExecutor.hpp"
#include "operator/BinaryOperator.hpp"
#include "Dot.hpp"

TreeWalker::TreeWalker(Dot *dot, Scope *scope): scope(scope), dot(dot) { }

bool TreeWalker::next() {
    if(current && current->val) {
        exec(current->val);
        if(doNext) current = current->next; else doNext = true;
    } else {
        if(!stack.empty()) {
            current = stack.top();
            stack.pop();
            scope = scope->close();
        } else {
            return false;
        }
    }
    return true;
}

void TreeWalker::reset(Scope *scope) {
    current = nullptr;
    this->scope = scope;
}

void TreeWalker::enter(ListNode *node) {
    if(node) {
        if(current) {
            stack.push(current->next);
            doNext = false;
        }
        scope = scope->child();
        current = node;
    }
}

DotValue *TreeWalker::exec(ExprNode *node) {
    return node->execute(dot, scope, this);
}

NodeExecutor::NodeExecutor(Dot *dot): dot(dot) {}

DotValue *NodeExecutor::start(ExprNode *node) {
    if(!node) return dot->getNull();
    if(!walker) walker = new TreeWalker(dot, dot->getGlobalScope());
    return walker->exec(node);
}

bool NodeExecutor::next() {
    return walker->next();
}

NodeExecutor::~NodeExecutor() {
    delete walker;
}
