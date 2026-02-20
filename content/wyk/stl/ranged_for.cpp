#include "list.hpp"

#include <iostream>

int main() {
    int tab[] = {1, 2, 3};
    for (int i : tab) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (int& i : tab) {
        i *= 2;
    }

    list l;
    for (int i : tab) {
        l.prepend(i);
    }

    for (int it : l) { // try auto
        std::cout << it << " ";
    }
    std::cout << std::endl;

    for (int& it : l) { // try auto
        it *= 2;
        std::cout << it << " ";
    }
    std::cout << std::endl;

    return 0;
}
