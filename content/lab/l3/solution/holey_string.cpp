#include "holey_string.hpp"

#include <iostream>

namespace l2
{

void holey_string_assign(HoleyString& hs, const std::string& val)
{
    size_t i = 0;
    for (; i < HoleyString::capacity - 1 && i < val.size(); ++i)
        hs.string[i].c = val[i];
    hs.string[i].c = 0x00;
}

void holey_string_hide(HoleyString& hs, const std::string& val)
{
    /**
     * This code works - but only because I guessed the hole is one byte after the char.
     * That is Undefined Behaviour (UB). I used it to make some platform specific hack.
     *
     * Classic: It works on my machine!
     */
    for (size_t i = 0; i < HoleyString::capacity && i < val.size(); ++i)
        *((&hs.string[i].c) + 1) = val[i];
}

void holey_string_print(const HoleyString& hs)
{
    for (int i = 0; i < HoleyString::capacity && hs.string[i].c != 0; ++i)
        std::cout << hs.string[i].c;
}

}  // namespace l2
