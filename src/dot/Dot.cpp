//
// Created by mineozelot on 05.06.16.
//

#include <iostream>
#include "Dot.hpp"
#include "parse/Parser.hpp"
#include "Exception.hpp"

Dot::Dot() {
    symtbl = new SymbolTable();
    ne = new NodeExecutor(this);
}

void Dot::init() {
    null_type = new DotType("null");

    null_value = new DotValue(null_type);

    operators.push_back(new AssignOperator(this));
}

ExprNode *Dot::parse(std::istream *in) {
    ExprNode *ret = nullptr;

    Lexer *lex = new Lexer();
    Parser *parser = new Parser(lex);

    try {
        lex->start(in, symtbl);
        ret = parser->parse();
    } catch (LexerException e) {
        std::cerr << "Lexer error: " << e.msg << std::endl;
    } catch (ParserException e) {
        std::cerr << "Parser error: " << e.msg << std::endl;
    }

    delete parser;
    delete lex;

    return ret;
}

DotValue *Dot::exec(ExprNode *node) {
    ne->start(node);
    ne->run();
    ne->terminate();
    return getNull();
}

DotValue *Dot::getNull() {
    return null_value;
}

void Dot::terminate() {
    delete symtbl;
    delete ne;
}

BaseOperator *Dot::getOperator(int id) {
    return operators[id];
}

DotVariable *Dot::getVariable(unsigned long sym) {
    if(variables.count(sym) > 0) {
        return variables[sym];
    } else {
        DotVariable *var = new DotVariable(this);
        variables.insert(std::pair<unsigned long, DotVariable *>(sym, var));
        return var;
    }
}

DotValue *Dot::createString(unsigned long sym) {
    return string_type->create(/*TODO: (*symtbl)[sym]*/);
}

DotValue *Dot::createNumber(unsigned long sym) {
    return number_type->create(/*TODO: (*symtbl)[sym]*/);
}

void Dot::print_debug_report() {
    std::cout
    << "Debug report:\n"
    << "Variables:\n";
    for(std::map<unsigned long, DotVariable *>::iterator it = variables.begin();
        it != variables.end(); it++) {
        std::cout << "Var " << *(*symtbl)[it->first] << '\n';
    }
    std::cout << std::endl;
}
