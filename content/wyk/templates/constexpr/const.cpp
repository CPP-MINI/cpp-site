#include <array>
#include <iostream>

int add(int x, int y) { return x + y; }

int main(int argc, char** argv)
{
    const int x = 1;
    const int y = 2;
    const int result = 2 * x + y;

    const int limit = add(result, x);

    if (argc > limit) {
        return 1;
    }

    // std::array<int, limit> arr = {};
    // std::cout << "created std::array<int, " << arr.size() << ">" << std::endl;

    return 0;
}
