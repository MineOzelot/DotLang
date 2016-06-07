//
// Created by mineozelot on 06.06.16.
//

#ifndef DOTLANG_DOTVALUE_HPP
#define DOTLANG_DOTVALUE_HPP


#include "DotType.hpp"

class DotValue {
    DotType *type;
public:
    DotValue(DotType *type);
};


#endif //DOTLANG_DOTVALUE_HPP
