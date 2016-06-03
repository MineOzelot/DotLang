//
// Created by mineozelot on 05.06.16.
//

#ifndef DOTLANG_TLIST_HPP
#define DOTLANG_TLIST_HPP

namespace lens {

    template <class T>
    struct TElement {
        TElement *next = nullptr;
        TElement *prev = nullptr;
        T value;
        TElement(T val): value(val) {}
    };

    template <class T>
    class TList {

        TElement<T> *head = nullptr;
        TElement<T> *current = nullptr;
        TElement<T> *end = nullptr;

    public:

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
    };

}

#endif //DOTLANG_TLIST_HPP
