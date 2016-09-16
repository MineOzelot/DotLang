/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  DotVariable.cpp
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

#include "DotVariable.hpp"
#include "../Dot.hpp"


DotVariable::DotVariable(Dot *dot): dot(dot) {
    value = dot->getNull();
}

DotVariable::DotVariable(Dot *dot, DotValue *val): dot(dot) {
    value = val;
}

void DotVariable::setValue(DotValue *val) {
    value = val;
}

DotValue *DotVariable::getValue() {
    return value;
}
