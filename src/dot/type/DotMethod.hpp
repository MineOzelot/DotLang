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


#include "DotValue.hpp"
#include "../../lens/TList.hpp"

class Dot;

class DotMethod {
protected:
    Dot *dot;
public:
    DotMethod(Dot *dot): dot(dot) {}
    virtual DotValue *call(lens::TList<DotValue *> *args);
};

class DotPrintLnMethod: public DotMethod {
public:
    DotPrintLnMethod(Dot *dot): DotMethod(dot) {}
    DotValue *call(lens::TList<DotValue *> *args);
};


#endif //DOTLANG_DOTMETHOD_HPP