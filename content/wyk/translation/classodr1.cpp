#include <iostream>

struct Point {
    int x;
    int y;
};

int dist(Point p, Point q);

int main() {
    Point p = {1, 1};
    Point q = {0, 0};
    std::cout << dist(p, q) << std::endl;
    return 0;
}