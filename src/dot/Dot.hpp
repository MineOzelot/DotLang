//
// Created by mineozelot on 05.06.16.
//

#ifndef DOTLANG_DOT_HPP
#define DOTLANG_DOT_HPP


#include <vector>
#include "parse/Lexer.hpp"
#include "Node.hpp"
#include "NodeExecutor.hpp"
#include "type/DotValue.hpp"
#include "operator/BaseOperator.hpp"
#include "operator/BinaryOperator.hpp"

class Dot {
    SymbolTable *symtbl;
    NodeExecutor *ne;

    std::vector<BaseOperator *> operators;

    std::map<unsigned long, DotVariable *> variables;
    std::vector<DotValue *> values;

    DotType *null_type;
    DotString *string_type;
    DotNumber *number_type;

    DotValue *null_value;
public:
    Dot();

    void init();
    void print_debug_report();
    void terminate();

    ExprNode *parse(std::istream *in);
    DotValue *exec(ExprNode *node);

    DotValue *getNull();
    BaseOperator *getOperator(int id);

    DotVariable *getVariable(unsigned long sym);

    DotValue *createString(unsigned long sym);
    DotValue *createNumber(unsigned long sym);
};


#endif //DOTLANG_DOT_HPP
