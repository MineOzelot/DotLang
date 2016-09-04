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
#include "type/DotValue.hpp"

class Dot;
class Scope;
class TreeWalker;

struct ExprNode {
    virtual const char *type() = 0;
    virtual DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker) = 0;
    virtual ~ExprNode() {};
};

struct NumberExprNode: public ExprNode {
    unsigned long num;
    const char *type() { return "node_number"; }
    NumberExprNode(unsigned long num): num(num) {}
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};
struct StringExprNode: public ExprNode {
    unsigned long str;
    const char *type() { return "node_string"; }
    StringExprNode(unsigned long str): str(str) {}
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};
struct VarExprNode: public ExprNode {
    unsigned long name;
    const char *type() { return "node_variable"; }
    VarExprNode(unsigned long name): name(name) {}
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};
struct BinaryOpNode: public ExprNode {
    int op;
    ExprNode *left, *right;
    const char *type() { return "node_operator"; }
    BinaryOpNode(int op, ExprNode *left, ExprNode *right): op(op), left(left), right(right) {}
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};
struct UnaryOpNode: public ExprNode {
    int op;
    ExprNode *right;
    const char *type() { return "node_unary_operator"; }
    UnaryOpNode(int op, ExprNode *right): op(op), right(right) {}
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};
struct AssignOpNode: public ExprNode {
    int op;
    VarExprNode *left;
    ExprNode *right;
    const char *type() { return "node_assign_operator"; }
    AssignOpNode(int op, VarExprNode *left, ExprNode *right): op(op), left(left), right(right) {}
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};
struct ListNode: public ExprNode {
    ListNode *prev = nullptr, *next = nullptr;
    ExprNode *val = nullptr;
    const char *type() { return "node_list"; }
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};
struct CallNode: public ExprNode {
    unsigned long id;
    ListNode *args;
    const char *type() { return "node_method_call"; }
    CallNode(unsigned long id, ListNode *node): id(id), args(node) {}
    DotValue *execute(Dot *dot, Scope *scope, TreeWalker *walker);
};


#endif //DOTLANG_NODE_HPP
