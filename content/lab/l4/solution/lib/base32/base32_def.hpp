#pragma once

namespace l4::base32
{
    static constexpr char k_base32hex_pad_char = '=';
    static constexpr char k_base32hex_separator_char = ';'; // Extension of the RFC!
    static constexpr int k_illegal_value = -1; // Przy ustawieniu tutaj INT_MAX mamy segfault dla wejscia do dekodowania "1["
}
