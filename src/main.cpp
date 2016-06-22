/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  main.cpp
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
        in = ifs;
    } else {
        in = &(std::cin);
    }

    Dot *dot = new Dot();

    dot->init();

    ExprNode *node = dot->parse(in);
    dot->exec(node);

    dot->terminate();

    std::cout << "---------------------------------------------------\n";
    dot->print_debug_report();

    delete dot;
}
