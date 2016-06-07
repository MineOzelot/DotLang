//
// Created by mineozelot on 06.06.16.
//

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
