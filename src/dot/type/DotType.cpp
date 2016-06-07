//
// Created by mineozelot on 06.06.16.
//

#include "DotType.hpp"
#include "DotValue.hpp"

DotType::DotType(const std::string &name): name(name) {}

DotValue *DotType::create() {
    return new DotValue(this);
}

DotNumber::DotNumber(): DotType("number") {}
DotString::DotString(): DotType("string") {}