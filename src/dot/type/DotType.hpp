//
// Created by mineozelot on 06.06.16.
//

#ifndef DOTLANG_DOTTYPE_HPP
#define DOTLANG_DOTTYPE_HPP


#include <string>

class DotValue;

class DotType {
    std::string name;
public:
    DotType(const std::string &name);

    DotValue *create();

    virtual ~DotType() {}
};

class DotNumber: public DotType {
public:
    DotNumber();
};

class DotString: public DotType {
public:
    DotString();
};


#endif //DOTLANG_DOTTYPE_HPP
