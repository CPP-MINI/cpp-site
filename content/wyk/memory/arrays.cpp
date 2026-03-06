#include <string>
#include <iostream>
#include <array>

void f(int* p) {
    std::cout << *p << '\n';
}

void g(int (&a)[3])
{
    std::cout << a[0] << '\n';
    std::cout << a[1] << '\n';
    std::cout << a[2] << '\n';
}

extern int gtab[];

int main() {
    int tab[3] = {1, 2, 3};
    char txt[] = "txt"; // dedukcja typu tablicy `char[4]`
    std::string poem[3] = { "ala", "ma", "kota" };

    int x[3] = {1, 2, 3}, y[3] = {4, 5, 6};
    // x = y; // !

    struct S { int c[3]; };
    S s1 = {1, 2, 3}, s2 = {3, 4, 5};


    int a[3] = {1, 2, 3};
    int* p = a;

    f(a); // ok
    f(p);
    f(gtab);

    g(a);

    alignas(4) struct My1BStruct
    {
        char c;
    };
    My1BStruct stab[3];
    static_assert(sizeof(stab) == 12, "asdf");

    std::array<int, 3> ax = {1, 2, 3};
    std::array<int, 3> ay;
    ay = ax;
}

int gtab[] = {1, 2, 3};
