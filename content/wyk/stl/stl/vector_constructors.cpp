#include <vector>
#include <array>
#include <iostream>

#include "int.hpp"

int main()
{
    {
        std::vector<A> v2(3);
    }
    {
        std::vector<Int> v3(3, Int(1));
    }
    {
        std::array<int, 3> tab = {1, 2, 3};
        std::vector<Int> v4(tab.begin(), tab.end());
    }
    return 0;
}