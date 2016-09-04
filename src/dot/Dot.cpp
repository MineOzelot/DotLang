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
    global_scope = new Scope();

    null_type = new DotType(this, "null");
    string_type = new DotString(this);
    number_type = new DotNumber(this);

    null_value = new DotValue(this, null_type);

    operators.push_back(new AssignOperator(this)); //0
    operators.push_back((operatorMethod = new MethodOperator(this))); //1
    operators.push_back(new AddOperator(this)); //2
    operators.push_back(new SubOperator(this)); //3
    operators.push_back(new MulOperator(this)); //4
    operators.push_back(new DivOperator(this)); //5

    defineMethod("println", new DotPrintLnMethod(this));
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
    while(ne->next());
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

DotVariable *Dot::getVariable(std::string name) {
    return global_scope->getVariable(symtbl->id(name));
}

DotMethod *Dot::getMethod(std::string name) {
    return global_scope->getMethod(symtbl->id(name));
}

DotValue *Dot::createString(std::string str) {
    return string_type->create(str);
}

DotValue *Dot::createNumber(long num) {
    return number_type->create(num);
}

void Dot::defineVariable(std::string name, DotVariable *var) {
    if(symtbl->contains(name)) symtbl->add(name);
    global_scope->define(symtbl->id(name), var);
}

void Dot::defineMethod(std::string name, DotMethod *met) {
    if(symtbl->contains(name)) symtbl->add(name);
    global_scope->define(symtbl->id(name), met);
}

void Dot::defineValue(DotValue *value) {
    values.push_back(value);
}

SymbolTable *Dot::getSymTbl() {
    return symtbl;
}

Scope *Dot::getGlobalScope() {
    return global_scope;
}
