/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Node.hpp
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

#ifndef DOTLANG_NODE_HPP
#define DOTLANG_NODE_HPP


#include <string>

enum NodeType {
    NUMBER, STRING,
    VARIABLE,
    BINOPERATOR, UNOPERATOR, ASSIGN,
    METHOD,
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
struct CallNode: public ExprNode {
    unsigned long id;
    ListNode *args;
    NodeType type() { return METHOD; }
    CallNode(unsigned long id, ListNode *node): id(id), args(node) {}
};


#endif //DOTLANG_NODE_HPP
