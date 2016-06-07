//
// Created by mineozelot on 06.06.16.
//

#ifndef DOTLANG_BINARYOPERATOR_HPP
#define DOTLANG_BINARYOPERATOR_HPP

#include "BaseOperator.hpp"
#include "../type/DotVariable.hpp"


class AssignOperator: public BaseAssignOperator {
public:
    AssignOperator(Dot *dot): BaseAssignOperator(dot) {}
    DotValue *exec(ExprNode *node, DotVariable *left, DotValue *right);
};

#endif //DOTLANG_BINARYOPERATOR_HPP
