#pragma once

namespace l4::base32
{
const char k_base32hex_pad_char = '=';
const char k_base32hex_separator_char = ';';  // Extension of the RFC!
const int k_illegal_value = -1;               // Here was a bug: using INT_MAX is inappropriate. -1 is safe.
}  // namespace l4::base32
