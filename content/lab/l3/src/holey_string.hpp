#pragma once

#include <cstdint>
#include <string>
namespace l2
{

struct HoleyString
{
    using holey_char = char;  // STAGE 4: Define me!

    static constexpr int capacity = 16;
    holey_char string[capacity];

    void assign(const std::string& val);
    void hide(const std::string& val);
    void print() const;
};

}  // namespace l2
