#include <vector>

#include "int.hpp"

int main() {
    {
        std::vector<Int> v;
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "  v.push_back(" << i << ")" << std::endl;
            v.push_back(Int(i));
        }
    }

    {
        std::vector<Int> v;
        std::cout << "  v.resize(3)" << std::endl;
        v.resize(3, Int(999));
        std::cout << "  v.resize(0)" << std::endl;
        v.resize(0, Int(999));
    }

    return 0;
}
