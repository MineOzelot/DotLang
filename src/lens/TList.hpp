/*  DotLang - The Dot Interpreter
 *  Copyright (C) 2016 MineOzelot
 *
 *  TList.hpp
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

#ifndef DOTLANG_TLIST_HPP
#define DOTLANG_TLIST_HPP

namespace lens {

    template <class T>
    struct TElement {
        TElement *next = nullptr;
        TElement *prev = nullptr;
        T value;
        TElement(T val): value(val) {}
        TElement(TElement<T> &el) {
            next = el.next;
            prev = el.prev;
            value = el.value;
        }
    };

    template <class T>
    class TList {

        TElement<T> *head = nullptr;
        TElement<T> *current = nullptr;
        TElement<T> *end = nullptr;

    public:

        TList() {}

        TList(TList<T> &list) {
            head = list.head;
            current = list.current;
            end = list.end;
        }

        T next() {
            if(current->next) {
                current = current->next;
                return current->value;
            }
            return nullptr;
        }

        T prev() {
            if(current->prev) {
                current = current->prev;
                return current->value;
            }
            return nullptr;
        }

        T get() {
            if(current)
                return current->value;
            return 0;
        }

        void push_back(T t) {
            if(!end) {
                head = current = end = new TElement<T>(t);
                return;
            }
            end->next = new TElement<T>(t);
            end->next->prev = end;
            end = end->next;
        }

        void push_front(T t) {
            if(!head) {
                head = current = end = new TElement<T>(t);
                return;
            }
            head->prev = new TElement<T>(t);
            head->prev->next = head;
            head = head->prev;
        }

        void del() {
            TElement<T> *next = current->next;
            if(current->next && current->prev) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            current = next;
        }

        inline bool is_end() {
            return current == end;
        }

        inline bool is_head() {
            return current == head;
        }

        inline void to_end() {
            current = end;
        }

        inline void to_head() {
            current = head;
        }

        void clear() {
            TElement<T> *cur = end;
            while(cur != head) {
                TElement<T> *next = cur->prev;
                delete cur;
                cur = next;
            }
            delete head;
            head = current = end = nullptr;
        }

        ~TList() {
            clear();
        }
    };

}

#endif //DOTLANG_TLIST_HPP
