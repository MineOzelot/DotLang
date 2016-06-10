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

NodeExecutor::NodeExecutor(Dot *dot): dot(dot) {}

DotValue *NodeExecutor::run(ExprNode *node) {
    if(!node) return dot->getNull();
    return execNode(node);
}

DotValue *NodeExecutor::execNode(ExprNode *node) {
        switch (node->type()) {
            case NodeType::LIST: {
                ListNode *cur = (ListNode *) node;
                DotValue *last = nullptr;
                while (cur) {
                    if(!cur->val) break;
                    if (last) delete last;
                    last = execNode(cur->val);
                    cur = cur->next;
                }
                return last;
            } case NodeType::UNOPERATOR: {
                UnaryOpNode *cur = (UnaryOpNode *) node;
                UnaryOperator *op = (UnaryOperator *) dot->getOperator(cur->op);
                return op->exec(cur, execNode(cur->right));
            } case NodeType::BINOPERATOR: {
                BinaryOpNode *cur = (BinaryOpNode *) node;
                BinaryOperator *op = (BinaryOperator *) dot->getOperator(cur->op);
                return op->exec(cur, execNode(cur->left), execNode(cur->right));
            } case NodeType::ASSIGN: {
                AssignOpNode *cur = (AssignOpNode *) node;
                AssignOperator *op = (AssignOperator *) dot->getOperator(cur->op);
                return op->exec(cur, dot->getVariable(cur->left->name), execNode(cur->right));
            } case NodeType::METHOD: {
                CallNode *cur = (CallNode *) node;
                MethodOperator *op = (MethodOperator *) dot->getOperator(1);
                lens::TList<DotValue *> *tlist = new lens::TList<DotValue *>();
                ListNode *args = cur->args;
                while(args) {
                    if(!args->val) break;
                    tlist->push_back(execNode(args->val));
                    args = args->next;
                }
                return op->exec(cur, cur->id, tlist);
            } case NodeType::VARIABLE: {
                VarExprNode *cur = (VarExprNode *) node;
                return dot->getVariable(cur->name)->getValue();
            } case NodeType::STRING: {
                StringExprNode *cur = (StringExprNode *) node;
                return dot->createString(cur->str);
            } case NodeType::NUMBER: {
                NumberExprNode *cur = (NumberExprNode *) node;
                return dot->createNumber(cur->num);
            }
        }
    return nullptr;
}
