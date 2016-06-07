//
// Created by mineozelot on 21.05.16.
//


#include <iostream>
#include <fstream>
#include "dot/Dot.hpp"

int main(int argc, char *argv[]) {
    std::istream *in;

    if(argc > 1) {
        std::ifstream *ifs = new std::ifstream(argv[1]);
        if(ifs->bad() || ifs->eof()) {
            std::cout << argv[1] << std::endl;
            delete ifs;
            exit(-1);
        }
        in = reinterpret_cast<std::istream *>(ifs);
    } else {
        in = &(std::cin);
    }

    Dot *dot = new Dot();

    dot->init();

    ExprNode *node = dot->parse(in);
    dot->exec(node);

    dot->terminate();

    dot->print_debug_report();

    delete dot;
}
