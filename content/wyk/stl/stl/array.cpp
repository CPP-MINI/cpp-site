#include <array>
#include <iostream>

class A {
public:
    A() { std::cout << "A()\n"; }
};

class Point {
public:
     Point(int x, int y) { std::cout << "Point(" << x << ", " << y << ")\n"; }
};

int main() {
    std::array<int, 10> a;
    a[0] = 1;
    a.at(1) = 2;
    a.front() = 3;
    a.back() = 4;
    a.fill(3);
    for (int i = 0; i < a.size(); i++) {
        a[i] = i;
    }
    for (auto it = a.begin(); it != a.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    for (auto it = a.rbegin(); it != a.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    for (int i : a) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::array<A, 3> tab;

    std::array<Point, 3> tab2{Point{1, 1}, Point{2, 2}, Point{3, 3}};

    return 0;
}