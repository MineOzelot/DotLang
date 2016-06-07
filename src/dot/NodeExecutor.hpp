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


#include "Node.hpp"
#include "type/DotValue.hpp"

class NodeExecutor {
    class Dot *dot;
    ExprNode *node = nullptr;

    bool isRunning = false;

    DotValue *execNode(ExprNode *node);
public:
    NodeExecutor(class Dot *dot);

    void start(ExprNode *node);

    void run();

    void terminate();
};


#endif //DOTLANG_NODEEXECUTOR_HPP
