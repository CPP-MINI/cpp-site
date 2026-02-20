#include <iostream>

#define MULTI_LINE_MACRO(x, y) \
std::cout << "x: " << x << ", y: " << y << std::endl; \
std::cout << "This is a multi-line macro!" << std::endl;

const char* longString = "This is a very long string \
that is continued \
on the next line.";

const char* longerString = "This is a set of long string literals "
    "that has been split across multiple lines "
    "to improve code readability.";

const char* injectedString =
    "this is a string "
#include "middle.hpp"
    "from somewhere else.";

int main()
{
    MULTI_LINE_MACRO(10, 20);
    std::cout << longString << std::endl;
    std::cout << longerString << std::endl;
    std::cout << injectedString << std::endl;
    return 0;
}
