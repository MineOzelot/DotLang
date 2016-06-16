/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Dot.hpp
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

#ifndef DOTLANG_DOT_HPP
#define DOTLANG_DOT_HPP


#include <vector>
#include "parse/Lexer.hpp"
#include "Node.hpp"
#include "NodeExecutor.hpp"
#include "type/DotValue.hpp"
#include "operator/BaseOperator.hpp"
#include "operator/BinaryOperator.hpp"
#include "type/DotMethod.hpp"

class Dot {
    SymbolTable *symtbl;
    NodeExecutor *ne;

    std::vector<BaseOperator *> operators;

    std::map<unsigned long, DotVariable *> variables;
    std::map<unsigned long, DotMethod *> methods;
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

    unsigned long defineSymbol(std::string str);
    std::string getSymbol(unsigned long sym);

    void defineVariable(unsigned long sym, DotVariable *var);
    void defineValue(DotValue *value);
    void defineMethod(unsigned long sym, DotMethod *met);

    DotVariable *getVariable(unsigned long sym);

    DotMethod *getMethod(unsigned long sym);

    DotValue *createString(std::string str);
    DotValue *createNumber(long num);
};


#endif //DOTLANG_DOT_HPP
