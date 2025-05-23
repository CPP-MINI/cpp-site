#include <iostream>

#include <ostream>

#include "utils.hpp"

int main()
{
    auto center = make_point(0, 0);

    std::vector<pointd> points(10);
    for (auto& p : points)
    {
        p = make_random_point();
        std::cout << "generated " << p << std::endl;
    }

    auto f = get_furthest(center, points);
    std::cout << "furthest = " << f << std::endl;

    return 0;
}