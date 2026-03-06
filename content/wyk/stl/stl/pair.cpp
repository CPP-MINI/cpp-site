#include <utility>

#include "int.hpp"

int main() {
    {
        std::cout << "  construction\n";
        std::pair<A, B> p;
        std::cout << "  assignment\n";
        p.first = A();
        p.second = B();
    }

    {
        A a;
        B b;
        std::cout << "  construction\n";
        std::pair<A, B> p(a, b);
        std::cout << "  move construction\n";
        std::pair<A, B> p2(std::move(a), std::move(b));
    }

    return 0;
}
