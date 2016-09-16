/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  DotMethod.hpp
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

#ifndef DOTLANG_DOTMETHOD_HPP
#define DOTLANG_DOTMETHOD_HPP


#include <vector>
#include "DotValue.hpp"
#include "../Node.hpp"

class Dot;
class Scope;

class DotMethod {
protected:
    Dot *dot;
public:
    DotMethod(Dot *dot): dot(dot) {}
    virtual DotValue *call(Scope *scope, std::vector<DotValue*> args, TreeWalker *walker);
};

class DefinedMethod: public DotMethod {
    std::vector<unsigned long> pars;
    ListNode *code;
public:
    DefinedMethod(Dot *dot, std::vector<unsigned long> args, ListNode *code): DotMethod(dot), pars(args), code(code) {}
    DotValue *call(Scope *scope, std::vector<DotValue*> args, TreeWalker *walker);
};

class DotPrintMethod: public DotMethod {
public:
    DotPrintMethod(Dot *dot): DotMethod(dot) {}
    DotValue *call(Scope *scope, std::vector<DotValue*> args, TreeWalker *walker);
};

class DotTypeMethod: public DotMethod {
public:
    DotTypeMethod(Dot *dot): DotMethod(dot) {}
    DotValue *call(Scope *scope, std::vector<DotValue*> args, TreeWalker *walker);
};


#endif //DOTLANG_DOTMETHOD_HPP
