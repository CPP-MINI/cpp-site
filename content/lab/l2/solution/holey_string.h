#pragma once

#include <cstdint>
#include <string>
namespace l2 {

    struct HoleyString{
        using holey_char = struct alignas(uint16_t) { char c;};
        holey_char string[16];

        void assign(const std::string val);
        void hide(const std::string val);
        void print();
    };

}
