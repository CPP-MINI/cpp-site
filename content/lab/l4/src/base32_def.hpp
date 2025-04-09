#pragma once
#include <climits>

namespace l4::base32
{
    const char k_base32hex_pad_char = '=';
    const char k_base32hex_separator_char = ';'; // Extension of the RFC!
    const int k_illegal_value = INT_MAX;
}
