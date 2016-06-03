//
// Created by mineozelot on 05.06.16.
//

#ifndef DOTLANG_LOCATION_HPP
#define DOTLANG_LOCATION_HPP


struct Position {
    unsigned long col, row;
    void next(int c = 1);
    void line();

    Position(unsigned long col = 0, unsigned long row = 0);
    Position(const Position &other);
};

std::ostream &operator<<(std::ostream &os, const Position &pos);

#endif //DOTLANG_LOCATION_HPP
