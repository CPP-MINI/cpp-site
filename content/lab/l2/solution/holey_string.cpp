#include "holey_string.h"

#include <iostream>

namespace l2 {

void HoleyString::assign(const std::string val)
{
    size_t i = 0;
    for (; i < 15 && i < val.size(); ++i)
        string[i].c = val[i];
    string[i].c = 0x00;
}

void HoleyString::hide(const std::string val)
{
    /**
     * This code works - but only because I guessed the hole is one byte after the char.
     * That is Undefined Behaviour (UB). I used it to make some platform specific hack.
     *
     * Classic: It works on my machine!
     */
    for (size_t i = 0; i < 16 && i < val.size(); ++i)
        *((&string[i].c) + 1) = val[i];

}

void HoleyString::print()
{
    for (int i = 0; i < 16 and string[i].c != 0; ++i)
        std::cout << string[i].c;
}

}
