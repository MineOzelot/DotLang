/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Dot.cpp
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
    string_type = new DotString();
    number_type = new DotNumber();

    null_value = new DotValue(null_type);

    operators.push_back(new AssignOperator(this));
    operators.push_back(new MethodOperator(this));

    unsigned long cur = symtbl->cur++;
    symtbl->map.insert(std::pair<unsigned long, std::string *>(cur, new std::string("println")));
    methods.insert(std::pair<unsigned long, DotMethod *>(cur, new DotPrintLnMethod(this)));
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
    return ne->run(node);
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

DotMethod *Dot::getMethod(unsigned long sym) {
    return methods[sym];
}

DotValue *Dot::createString(unsigned long sym) {
    return string_type->create(*symtbl->map[sym]);
}

DotValue *Dot::createNumber(unsigned long sym) {
    return number_type->create(*symtbl->map[sym]);
}

void Dot::print_debug_report() {
    std::cout
    << "Debug report:\n";
    for(std::map<unsigned long, std::string *>::iterator it = symtbl->map.begin();
        it != symtbl->map.end(); it++) {
        std::cout << "Sym " << it->first << " - " << *it->second << '\n';
    }
    std::cout << "Variables:\n";
    for(std::map<unsigned long, DotVariable *>::iterator it = variables.begin();
        it != variables.end(); it++) {
        std::cout << "Var " << *symtbl->map[it->first] << '\n';
    }
    std::cout << "Methods:\n";
    for(std::map<unsigned long, DotMethod *>::iterator it = methods.begin();
        it != methods.end(); it++) {
        std::cout << "Method " << *symtbl->map[it->first] << '\n';
    }
    std::cout << std::endl;
}

void Dot::defineVariable(unsigned long sym, DotVariable *var) {
    variables.insert(std::pair<unsigned long, DotVariable *>(sym, var));
}

void Dot::defineMethod(unsigned long sym, DotMethod *met) {
    methods.insert(std::pair<unsigned long, DotMethod *>(sym, met));
}
