/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  DotType.hpp
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

#ifndef DOTLANG_DOTTYPE_HPP
#define DOTLANG_DOTTYPE_HPP


#include <string>

class DotValue;

class DotType {
    std::string name;
public:
    DotType(const std::string &name);

    virtual DotValue *create();

    virtual ~DotType() {}

    virtual std::string to_str(DotValue *value);
};

class DotNumber: public DotType {
public:
    DotNumber();
    DotValue *create(std::string str);
    std::string to_str(DotValue *value);
};

class DotString: public DotType {
public:
    DotString();
    DotValue *create(std::string str);
    std::string to_str(DotValue *value);
};


#endif //DOTLANG_DOTTYPE_HPP
