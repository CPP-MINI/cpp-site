#pragma once

#include <cstdint>
#include <string>
namespace l2
{

struct HoleyString
{
    using holey_char = struct alignas(uint16_t)
    {
        char c;
    };

    static const int capacity = 16;
    holey_char string[capacity];
};

void holey_string_assign(HoleyString& hs, const std::string& val);
void holey_string_hide(HoleyString& hs, const std::string& val);
void holey_string_print(const HoleyString& hs);

}  // namespace l2
