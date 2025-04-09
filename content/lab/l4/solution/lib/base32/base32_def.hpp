#pragma once
#include <limits.h>

namespace l4::base32
{
    static constexpr char k_base32hex_pad_char = '=';
    static constexpr char k_base32hex_separator_char = ';'; // Extension of the RFC!
    static constexpr int k_illegal_value = INT_MAX; // Przy ustawieniu tutaj INT_MAX mamy segfault dla wejscia do dekodowania "1["
}
