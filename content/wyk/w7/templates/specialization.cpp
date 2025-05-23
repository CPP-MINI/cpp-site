#include <cstring>
#include <iostream>

template <typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

template<>
const char* min(const char* a, const char* b)
{
    return std::strcmp(a, b) < 0 ? a : b;
}

int main()
{
    std::cout << min(1, 2) << std::endl;
    std::cout << min(3.0, 2.0) << std::endl;

    const char* txt1 = "hey";
    const char* txt2 = "alex";

    std::cout << min(txt1, txt2) << std::endl;
    return 0;
}
