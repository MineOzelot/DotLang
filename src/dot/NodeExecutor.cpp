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

#include "NodeExecutor.hpp"
#include "operator/BinaryOperator.hpp"
#include "Dot.hpp"

TreeWalker::TreeWalker(Dot *dot): dot(dot) {
    current.scope = dot->getGlobalScope();
}

bool TreeWalker::next() {
    if(!current.isExecuted) {
        current.isExecuted = true;
        exec(current.exec->get());
        if(current.isExecuted && current.exec->next()) {
            current.isExecuted = false;
        }
    } else {
        if(!stack.empty()) {
            current.scope->close();
            current = stack.top();
            stack.pop();
            if(current.isExecuted && current.exec->next()) {
                current.isExecuted = false;
            }
        } else {
            return false;
        }
    }
    return true;
}

void TreeWalker::enter(ListNode *node, Scope *scope) {
    if(node) {
        if(current.exec)
            stack.push(current);

        current.scope = scope;
        current.exec = new lens::TList<ExprNode *>(*node->list);
        current.isExecuted = false;
    }
}

DotValue *TreeWalker::exec(ExprNode *node) {
    return node->execute(dot, current.scope, this);
}

NodeExecutor::NodeExecutor(Dot *dot): dot(dot) {}

DotValue *NodeExecutor::start(ExprNode *node) {
    if(!node) return dot->getNull();
    if(!walker) walker = new TreeWalker(dot);
    return walker->exec(node);
}

bool NodeExecutor::next() {
    return walker->next();
}

NodeExecutor::~NodeExecutor() {
    delete walker;
}
