//
// Created by mineozelot on 05.06.16.
//

#include <ostream>
#include "Position.hpp"

Position::Position(unsigned long col, unsigned long row): col(col), row(row) {}
Position::Position(const Position &other) { col = other.col; row = other.row; }

void Position::next(int c) { col += c; }
void Position::line() { row++; col = 0; }

std::ostream &operator<<(std::ostream &os, const Position &pos) {
    os << "(" << pos.col << ", " << pos.row << ")";
    return os;
}