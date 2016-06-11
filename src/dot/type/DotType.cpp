/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  DotType.cpp
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

#include "DotType.hpp"
#include "DotValue.hpp"
#include "../Dot.hpp"

DotType::DotType(Dot *dot, const std::string &name): dot(dot), name(name) {}

DotValue *DotType::create() {
    return new DotValue(dot, this);
}

std::string DotType::to_str(DotValue *value) {
    return "null";
}


DotNumber::DotNumber(Dot *dot): DotType(dot, "number") {}
DotValue *DotNumber::create(std::string str) {
    DotValue *ret = new DotValue(dot, this);
    ret->setData(new std::string(str));
    return ret;
}
std::string DotNumber::to_str(DotValue *value) {
    return std::string(*((std::string *) value->getData()));
}

DotString::DotString(Dot *dot): DotType(dot, "string") {}
DotValue *DotString::create(std::string str) {
    DotValue *ret = new DotValue(dot, this);
    ret->setData(new std::string(str));
    return ret;
}
std::string DotString::to_str(DotValue *value) {
    return std::string(*(std::string *) value->getData());
}