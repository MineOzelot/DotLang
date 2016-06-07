//
// Created by mineozelot on 06.06.16.
//

#include "DotVariable.hpp"
#include "../Dot.hpp"


DotVariable::DotVariable(Dot *dot) {
    value = dot->getNull();
}

void DotVariable::setValue(DotValue *val) {
    value = val;
}

DotValue *DotVariable::getValue() {
    return value;
}
