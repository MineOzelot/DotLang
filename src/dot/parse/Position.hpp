/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  Position.hpp
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
