#include <iostream>

#include "list.hpp"

int main() {
    list l;
    l.prepend(1);
    l.prepend(2);
    l.prepend(3);
    for (list::iterator it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}

