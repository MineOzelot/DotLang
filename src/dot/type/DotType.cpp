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
#include "../Dot.hpp"

DotType::DotType(Dot *dot, const std::string &name): dot(dot), name(name) {}

DotValue *DotType::create() {
    return new DotValue(dot, this);
}

DotValue *DotType::add(DotValue *num1, DotValue *num2) {
    return dot->getNull(); //TODO: throw RuntimeException
}

DotValue *DotType::sub(DotValue *num1, DotValue *num2) {
    return dot->getNull(); //TODO: throw RuntimeException
}

DotValue *DotType::mul(DotValue *num1, DotValue *num2) {
    return dot->getNull();
}
DotValue *DotType::div(DotValue *num1, DotValue *num2) {
    return dot->getNull();
}

DotValue *DotType::to_str(DotValue *val) {
    return dot->createString("null");
}


DotNumber::DotNumber(Dot *dot): DotType(dot, "number") {}
DotValue *DotNumber::create(long num) {
    DotValue *ret = new DotValue(dot, this);
    ret->setData(new long(num));
    return ret;
}

DotValue *DotNumber::add(DotValue *num1, DotValue *num2) {
    long *val1 = num1->getData<long>();
    long *val2 = num2->getData<long>();
    long res = *val1 + *val2;
    return create(res);
}

DotValue *DotNumber::sub(DotValue *num1, DotValue *num2) {
    long *val1 = num1->getData<long>();
    long *val2 = num2->getData<long>();
    long res = *val1 - *val2;
    return create(res);
}

DotValue *DotNumber::mul(DotValue *num1, DotValue *num2) {
    long *val1 = num1->getData<long>();
    long *val2 = num2->getData<long>();
    long res = *val1 * *val2;
    return create(res);
}

DotValue *DotNumber::div(DotValue *num1, DotValue *num2) {
    long *val1 = num1->getData<long>();
    long *val2 = num2->getData<long>();
    long res = *val1 / *val2; //TODO: if(*val2 == 0) throw RuntimeException
    return create(res);
}

DotValue *DotNumber::to_str(DotValue *val) {
    long *num = val->getData<long>();
    std::stringstream str;
    str << *num;
    return dot->createString(str.str());
}


DotString::DotString(Dot *dot): DotType(dot, "string") {}
DotValue *DotString::create(std::string str) {
    DotValue *ret = new DotValue(dot, this);
    ret->setData(new std::string(str));
    return ret;
}

DotValue *DotString::add(DotValue *str1, DotValue *str2) {
    std::string *val1 = str1->getData<std::string>();
    std::string *val2 = str2->getType()->to_str(str2)->getData<std::string>();
    std::string res = *val1 + *val2;
    return create(res);
}

DotValue *DotString::to_str(DotValue *val) {
    return val;
}
