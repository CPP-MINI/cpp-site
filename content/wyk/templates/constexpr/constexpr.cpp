#include <array>
#include <iostream>

constexpr int add(int x, int y) { return x + y; }

int main(int argc, char** argv)
{
    constexpr int x = 1;
    constexpr int y = 2;
    constexpr int result = 2 * x + y;

    constexpr int limit = add(result, x);

    if (argc > limit) {
        return 1;
    }

    std::array<int, limit> arr = {};
    std::cout << "created std::array<int, " << arr.size() << ">" << std::endl;

    return 0;
}
