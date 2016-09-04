/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Scope.cpp
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

#include "Scope.hpp"

Scope::Scope() {}
Scope::Scope(Scope *parent): parent(parent) {}

void Scope::define(unsigned long sym, DotVariable *var) {
    variables.insert(std::pair<unsigned long, DotVariable *>(sym, var));
}

void Scope::define(unsigned long sym, DotMethod *met) {
    methods.insert(std::pair<unsigned long, DotMethod *>(sym, met));
}

DotVariable *Scope::getVariable(unsigned long sym) {
    if(variables.count(sym) == 0) {
        if(parent != nullptr)
            return parent->getVariable(sym);
    } else {
        return variables[sym];
    }
    return nullptr;
}

DotMethod *Scope::getMethod(unsigned long sym) {
    if(methods.count(sym) == 0) {
        if(parent != nullptr)
            return parent->getMethod(sym);
    } else {
        return methods[sym];
    }
    return nullptr;
}

Scope *Scope::close() {
    if(parent) {
        Scope *parent = this->parent;

        for(MethodMap::iterator it = methods.begin(); it != methods.end(); it++) {
            delete it->second;
        }
        for(VarMap::iterator it = variables.begin(); it != variables.end(); it++) {
            delete it->second;
        }

        delete this;
        return parent;
    } else {
        return this;
    }
}

Scope *Scope::child() {
    return new Scope(this);
}