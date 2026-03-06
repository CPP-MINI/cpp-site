#include <vector>

#include "int.hpp"

int main() {
    std::vector<Int> v;
    v.reserve(10);

    Int v1(1);
    Int v2(2);

    std::cout << "  v.push_back(v1)" << std::endl;
    v.push_back(v1);
    std::cout << "  v.push_back(std::move(v2))" << std::endl;
    v.push_back(std::move(v2));
    std::cout << "  v.emplace_back(3)" << std::endl;
    v.emplace_back(3);

    std::cout << "  v.insert(v.begin(), Int(0))" << std::endl;
    v.insert(v.begin(), Int(0));
    std::cout << "  v.emplace(v.end(), 4)" << std::endl;
    v.emplace(v.end(), 4);

    std::cout << "  v.erase(v.begin() + 1, v.begin() + 4)" << std::endl;
    v.erase(v.begin() + 1, v.begin() + 4);

    std::cout << "  v.clear()" << std::endl;
    v.clear();

    return 0;
}
