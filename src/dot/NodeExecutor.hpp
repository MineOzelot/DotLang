/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  NodeExecutor.hpp
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

#ifndef DOTLANG_NODEEXECUTOR_HPP
#define DOTLANG_NODEEXECUTOR_HPP


#include <stack>
#include "Node.hpp"
#include "Scope.hpp"
#include "type/DotValue.hpp"

class Dot;

class TreeWalker {
    ListNode *current;

    Dot *dot;
    Scope *scope;

    bool doNext = true;

    std::stack<ListNode *> stack;
public:
    TreeWalker(Dot *dot, Scope *scope);

    bool next();

    void enter(ListNode *node);

    DotValue *exec(ExprNode *node);

    void reset(Scope *scope);
};

class NodeExecutor {
    Dot *dot;
    TreeWalker *walker;
public:
    NodeExecutor(Dot *dot);

    DotValue *start(ExprNode *node);
    bool next();

    virtual ~NodeExecutor();
};


#endif //DOTLANG_NODEEXECUTOR_HPP
