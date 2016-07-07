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
    null_type = new DotType(this, "null");
    string_type = new DotString(this);
    number_type = new DotNumber(this);

    null_value = new DotValue(this, null_type);

    operators.push_back(new AssignOperator(this)); //0
    operators.push_back(new MethodOperator(this)); //1
    operators.push_back(new AddOperator(this)); //2
    operators.push_back(new SubOperator(this)); //3
    operators.push_back(new MulOperator(this)); //4
    operators.push_back(new DivOperator(this)); //5


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

DotValue *Dot::createString(std::string str) {
    return string_type->create(str);
}

DotValue *Dot::createNumber(long num) {
    return number_type->create(num);
}

void Dot::print_debug_report() {
    std::cout
    << "Debug report:\n";
    for(auto it = symtbl->map.begin();
        it != symtbl->map.end(); it++) {
        std::cout << "Sym " << it->first << " - " << *it->second << '\n';
    }
    std::cout << "Variables:\n";
    for(auto it = variables.begin();
        it != variables.end(); it++) {
        std::cout << "Var " << *symtbl->map[it->first] << '\n';
    }
    std::cout << "Methods:\n";
    for(auto it = methods.begin(); it != methods.end(); it++) {
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

void Dot::defineValue(DotValue *value) {
    values.push_back(value);
}

unsigned long Dot::defineSymbol(std::string str) {
    for(auto it = symtbl->map.begin(); it != symtbl->map.end(); it++)
        if(*(it->second) == str)
            return it->first;
    unsigned long id = symtbl->cur++;
    symtbl->map.insert(std::pair<unsigned long, std::string*>(id, new std::string(str)));
    return id;
}

std::string Dot::getSymbol(unsigned long sym) {
    return *symtbl->map[sym];
}
