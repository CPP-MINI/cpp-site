#include <cstddef>
#include <iostream>
#include <ostream>

void allocate_all_the_thing() {
    for(int i = 0; i < 1000000; ++i) {
        std::cout << "allocating [" << i << ']' << std::endl;

        try
        {
            int* tab = new int[100'000'000]; // 400MB
        } catch (std::bad_alloc& e) {
            std::cerr << "bad_alloc" << std::endl;
            return;
        }
    }
}

int main() {
    int* ptr = new int;
    int* tab = new int[10];

    *ptr = 10;
    for (int i = 0; i < 10; i++) {
        tab[i] = i;
    }
    delete ptr;
    delete[] tab;

    allocate_all_the_thing();
    return 0;
}


