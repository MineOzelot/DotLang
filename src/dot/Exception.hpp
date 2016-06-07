//
// Created by mineozelot on 06.06.16.
//

#ifndef DOTLANG_EXCEPTION_HPP
#define DOTLANG_EXCEPTION_HPP

#include <string>

struct Exception {
    const std::string &msg;
    Exception(const std::string &msg): msg(msg) {}
    virtual ~Exception() {}
};

struct LexerException: public Exception {
    LexerException(const std::string &msg) : Exception(msg) { }
};

struct ParserException: public Exception {
    ParserException(const std::string &msg) : Exception(msg) { }
};


#endif //DOTLANG_EXCEPTION_HPP
