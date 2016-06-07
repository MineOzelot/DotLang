//
// Created by mineozelot on 27.05.16.
//

#ifndef DOTLANG_NODE_HPP
#define DOTLANG_NODE_HPP


#include <string>

enum NodeType {
    NUMBER, STRING,
    VARIABLE,
    BINOPERATOR, UNOPERATOR, ASSIGN,
    LIST
};

struct ExprNode {
    virtual NodeType type() = 0;
    virtual ~ExprNode() {};
};

struct NumberExprNode: public ExprNode {
    unsigned long num;
    NodeType type() { return NUMBER; }
    NumberExprNode(unsigned long num): num(num) {}
};
struct StringExprNode: public ExprNode {
    unsigned long str;
    NodeType type() { return STRING; }
    StringExprNode(unsigned long str): str(str) {}
};
struct VarExprNode: public ExprNode {
    unsigned long name;
    NodeType type() { return VARIABLE; }
    VarExprNode(unsigned long name): name(name) {}
};
struct BinaryOpNode: public ExprNode {
    int op;
    ExprNode *left, *right;
    NodeType type() { return BINOPERATOR; }
    BinaryOpNode(int op, ExprNode *left, ExprNode *right): op(op), left(left), right(right) {}
};
struct UnaryOpNode: public ExprNode {
    int op;
    ExprNode *right;
    NodeType type() { return UNOPERATOR; }
    UnaryOpNode(int op, ExprNode *right): op(op), right(right) {}
};
struct AssignOpNode: public ExprNode {
    int op;
    VarExprNode *left;
    ExprNode *right;
    NodeType type() { return ASSIGN; }
    AssignOpNode(int op, VarExprNode *left, ExprNode *right): op(op), left(left), right(right) {}
};
struct ListNode: public ExprNode {
    ListNode *prev = nullptr, *next = nullptr;
    ExprNode *val = nullptr;
    NodeType type() { return LIST; }
};


#endif //DOTLANG_NODE_HPP
