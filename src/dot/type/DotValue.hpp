/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  DotValue.hpp
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

#ifndef DOTLANG_DOTVALUE_HPP
#define DOTLANG_DOTVALUE_HPP


#include "DotType.hpp"

class Dot;

class DotValue {
    DotType *type;
    void *data;
public:
    DotValue(Dot *dot, DotType *type);
    void setData(void *data);
    template <typename _Return>
    _Return *getData() { return static_cast<_Return *>(data); }
    DotType *getType();
};


#endif //DOTLANG_DOTVALUE_HPP
