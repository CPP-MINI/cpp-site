#include "decoder.hpp"
#include "base32_def.hpp"

#include <cstdint>

namespace l4::base32
{
const int k_character_counter_to_bytes[]{
    0,                // 0
    k_illegal_value,  // 1 - illegal
    1,                // 2
    k_illegal_value,  // 3 - illegal
    2,                // 4
    3,                // 5
    k_illegal_value,  // 6 - illegal
    4,                // 7
    5,                // 8
};

const int k_character_counter_to_byte_shift[]{
    0,                // 0
    k_illegal_value,  // 1 - illegal
    2,                // 2
    k_illegal_value,  // 3 - illegal
    4,                // 4
    1,                // 5
    k_illegal_value,  // 6 - illegal
    3,                // 7
    0,                // 8
};

std::vector<std::byte> Decoder::decodeBytestream()
{
    std::vector<std::byte> result;
    uint64_t buffer = 0;
    int character_counter = 0;

    while (_idx < _encoded_string.size() && _encoded_string[_idx] != k_base32hex_pad_char &&
           _encoded_string[_idx] != k_base32hex_separator_char)
    {
        int value = _encoded_string[_idx] - '0';
        if (_encoded_string[_idx] >= 'A')
            value = _encoded_string[_idx] - 'A' + 10;

        if (value < 0 || value > 32)
            break;  // wrong value
        buffer <<= 5;
        buffer += value;

        _idx++;
        character_counter++;

        if (character_counter == 8)
        {
            std::byte batch[5];
            for (int i = 4; i >= 0; --i)
            {
                batch[i] = std::byte(buffer & 0xff);
                buffer >>= 8;
            }

            for (int i = 0; i < 5; ++i)
                result.push_back(batch[i]);

            buffer = 0;
            character_counter = 0;
        }
    }

    if (character_counter != 0)
    {
        int byte_count = k_character_counter_to_bytes[character_counter];
        buffer >>= k_character_counter_to_byte_shift[character_counter];

        std::byte batch[5];
        for (int i = byte_count - 1; i >= 0; --i)
        {
            batch[i] = std::byte(buffer & 0xff);
            buffer >>= 8;
        }

        for (int i = 0; i < byte_count; ++i)
            result.push_back(batch[i]);

        buffer = 0;
    }

    // Here iterating only over `=` is too much - trigger a problem with empty last line on the input
    while (_idx < _encoded_string.size() && _encoded_string[_idx] != k_base32hex_separator_char)
        ++_idx;

    if (_encoded_string[_idx] == k_base32hex_separator_char)
        ++_idx;

    return result;
}

Decoder::Decoder(const std::string &encoded_string) : _encoded_string(encoded_string), _idx(0) {}

bool Decoder::isEmpty() const { return _idx == _encoded_string.size(); }

std::vector<std::byte> Decoder::pullBytestream() { return decodeBytestream(); }
}  // namespace l4::base32
