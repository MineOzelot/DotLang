//
// Created by mineozelot on 06.06.16.
//

#include "BinaryOperator.hpp"


DotValue *AssignOperator::exec(ExprNode *node, DotVariable *left, DotValue *right) {
    left->setValue(right);
    return right;
}
