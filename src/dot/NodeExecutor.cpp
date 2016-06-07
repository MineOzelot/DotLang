//
// Created by mineozelot on 06.06.16.
//

#include "NodeExecutor.hpp"
#include "operator/BinaryOperator.hpp"
#include "Dot.hpp"

NodeExecutor::NodeExecutor(Dot *dot): dot(dot) {}

void NodeExecutor::start(ExprNode *node) {
    this->node = node;
}

void NodeExecutor::run() {
    if(!node) return;
    isRunning = true;
    execNode(node);
}

void NodeExecutor::terminate() {
    isRunning = false;
    node = nullptr;
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
            } case NodeType::UNOPERATOR:
                //TODO: Unary operator
                return nullptr;
            case NodeType::BINOPERATOR: {
                BinaryOpNode *cur = (BinaryOpNode *) node;
                BinaryOperator *op = (BinaryOperator *) dot->getOperator(cur->op);
                return op->exec(cur, execNode(cur->left), execNode(cur->right));
            } case NodeType::ASSIGN: {
                AssignOpNode *cur = (AssignOpNode *) node;
                AssignOperator *op = (AssignOperator *) dot->getOperator(cur->op);
                return op->exec(cur, dot->getVariable(cur->left->name), execNode(cur->right));
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
}
