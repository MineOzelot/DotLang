//
// Created by mineozelot on 06.06.16.
//

#ifndef DOTLANG_DOTVARIABLE_HPP
#define DOTLANG_DOTVARIABLE_HPP


#include "DotValue.hpp"

class Dot;

class DotVariable {
    Dot *dot;
    DotValue *value;
public:
    DotVariable(Dot *dot);
    void setValue(DotValue *val);
    DotValue *getValue();
};


#endif //DOTLANG_DOTVARIABLE_HPP
