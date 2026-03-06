#include <iostream>
#include <list>

#include "int.hpp"
#include <list>

int main() {
    std::list<Int> l;
    for (int i = 0; i < 4; ++i) {
        l.emplace_back(i);
    }
    auto it = l.begin();
    ++it;
    ++it;
    l.emplace(it, 100);
    return 0;
}
