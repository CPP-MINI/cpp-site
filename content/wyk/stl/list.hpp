#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

class list {
    struct node {
        int value;
        std::unique_ptr<node> next;
        node(int value, std::unique_ptr<node> next) : value(value), next(std::move(next)) {}
    };

    std::unique_ptr<node> head;
public:
    class iterator {
        node* ptr;
    public:
        iterator(node* ptr) : ptr(ptr) {}

        int& operator*() { return ptr->value; }

        iterator& operator++() {
            ptr = ptr->next.get();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) { return ptr == other.ptr; }
        bool operator!=(const iterator& other) { return !(*this == other); }
    };

    iterator begin() { return iterator(head.get()); }
    iterator end() { return iterator(nullptr); }

    list() = default;

    void prepend(int value) {
        head = std::make_unique<node>(value, std::move(head));
    }
};

#endif