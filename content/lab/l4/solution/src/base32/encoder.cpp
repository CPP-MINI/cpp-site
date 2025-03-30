#include "encoder.hpp"

void l4::base32::Encoder::appendBytestream(const std::byte *bytestream, std::size_t size)
{
    if (size == 0)
        return;

    if (size == 1)
    {
        appendSingleByte(bytestream[0]);
        return;
    }

    std::size_t byte_idx = 1;
    int bit_idx = 0;

    // Assuming more than one byte in the stream
    std::byte current_byte = bytestream[0];
    std::byte next_byte = bytestream[1];

    while (byte_idx < size)
    {
        // Move 5 bits ahead
        int next_bit_index = bit_idx + 5;

        // Read as many bits as possible from the current byte
        int number_to_encode = static_cast<int>((current_byte & std::byte(base32_bit_mask << bit_idx)) >> bit_idx);

        // Read the rest from the next byte and add the result
        if (next_bit_index > 8)
        {
            int backward_number = next_bit_index - 8;
            number_to_encode <<= backward_number;
            number_to_encode += static_cast<int>(next_byte & std::byte(base32_bit_mask >> backward_number))
        }

        // Save the encoded value to the string
        _buff.push_back(k_base32hex_alphabet[number_to_encode]);

        // Move and byte ahead, if we are going to overflow current byte
        if (bit_idx + 5 > 8)
        {
            byte_idx++;
            current_byte = next_byte;
            next_byte = bytestream[byte_idx];
        }

        bit_idx = next_bit_index % 8; // Move 5 bits ahead
    }

    int padding_count = k_bit_idx_to_padding_count[bit_idx];
    for (std::size_t i = 0; i < padding_count; i++)
        _buff.push_back(k_base32hex_pad_char);
}

void l4::base32::Encoder::appendSingleByte(const std::byte &byte)
{
    int value_to_encode = static_cast<int>(byte & std::byte(base32_bit_mask));
    _buff.push_back(k_base32hex_alphabet[value_to_encode]);
    for (std::size_t i = 0; i < k_bit_idx_to_padding_count[1]; i++)
        _buff.push_back(k_base32hex_pad_char);
}

void l4::base32::Encoder::pushBytes(const std::byte *bytestream, std::size_t size)
{
    if (!_buff.empty())
        _buff.push_back(k_base32hex_separator_char);

    appendBytestream(bytestream, size);
}

std::string l4::base32::Encoder::encodedString() const
{
    return {_buff.data(), _buff.size()};
}
