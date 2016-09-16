/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  DotMethod.cpp
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
#include "DotMethod.hpp"
#include "../Dot.hpp"

DotValue *DotMethod::call(Scope *scope, std::vector<DotValue*> args, TreeWalker *walker) {
    return dot->getNull();
}

DotValue *DotPrintMethod::call(Scope *scope, std::vector<DotValue*> args, TreeWalker *walker) {
    if(!args.empty()) {
        for(std::vector<DotValue*>::iterator it = args.begin(); it != args.end(); it++)
            std::cout << *(it.operator*()->getType()->to_str(*it)->getData<std::string>());
    }
    std::cout.flush();
    return dot->getNull();
}

DotValue *DefinedMethod::call(Scope *scope, std::vector<DotValue *> args, TreeWalker *walker) {
    Scope *my = scope->child();
    for(int g = 0; g < pars.size(); g++) {
        DotValue *val;
        if(g >= args.size())
            val = dot->getNull();
        else
            val = args[g];
        my->define(pars[g], new DotVariable(dot, val));
    }
    walker->enter(code, my);
    return dot->getNull(); //todo: return
}
