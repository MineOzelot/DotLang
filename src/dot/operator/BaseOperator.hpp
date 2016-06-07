//
// Created by mineozelot on 06.06.16.
//

#ifndef DOTLANG_BASEOPERATOR_HPP
#define DOTLANG_BASEOPERATOR_HPP


#include "../type/DotValue.hpp"
#include "../type/DotVariable.hpp"
#include "../Node.hpp"

class Dot;

class BaseOperator {
protected:
    Dot *dot;
public:
    BaseOperator(Dot *dot): dot(dot) {};
    virtual ~BaseOperator() {}
};

class UnaryOperator: public BaseOperator {
public:
    UnaryOperator(Dot *dot): BaseOperator(dot) {}
    virtual DotValue *exec(ExprNode *node, DotValue *par) = 0;
    virtual ~UnaryOperator() {}
};

class BinaryOperator: public BaseOperator {
public:
    BinaryOperator(Dot *dot): BaseOperator(dot) {}
    virtual DotValue *exec(ExprNode *node, DotValue *left, DotValue *right) = 0;
    virtual ~BinaryOperator() {}
};

class BaseAssignOperator: public BaseOperator {
public:
    BaseAssignOperator(Dot *dot): BaseOperator(dot) {}
    virtual  DotValue *exec(ExprNode *node, DotVariable *left, DotValue *right) = 0;
    virtual ~BaseAssignOperator() {}
};

#endif //DOTLANG_BASEOPERATOR_HPP
