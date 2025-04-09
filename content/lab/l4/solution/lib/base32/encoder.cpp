#include "encoder.hpp"
#include "base32_def.hpp"

namespace l4::base32
{
    // Source: https://datatracker.ietf.org/doc/html/rfc4648#section-7
    const char k_base32hex_alphabet[]
    {
        '0','1','2','3','4','5','6','7',
        '8','9','A','B','C','D','E','F',
        'G','H','I','J','K','L','M','N',
        'O','P','Q','R','S','T','U','V',
    };

    const int k_bit_idx_to_padding_count[]
    {
        0,  // 0
        3,  // 1
        6,  // 2
        1,  // 3
        4,  // 4
        k_illegal_value, // 5 - illegal
        k_illegal_value, // 6 - illegal
        k_illegal_value, // 7 - illegal
    };

    const uint8_t base32_bit_mask = 0b11111000;

    char Encoder::encodePlace(int bit_idx, std::byte current_byte, std::byte next_byte)
    {
        // Move 5 bits ahead
        int next_bit_index = bit_idx + 5;

        // Read as many bits as possible from the current byte
        int number_to_encode = static_cast<int>(current_byte & std::byte(base32_bit_mask >> bit_idx));
        number_to_encode >>= std::max(8 - next_bit_index, 0);

        // Read the rest from the next byte and add the result
        if (next_bit_index > 8)
        {
            int reverse_number = next_bit_index - 8;
            std::byte next_byte_chunk = next_byte & std::byte(base32_bit_mask << (5 - reverse_number));
            next_byte_chunk >>= 8 - reverse_number;
            number_to_encode <<= reverse_number;
            number_to_encode += static_cast<int>(next_byte_chunk);
        }

        // Translate value to the character from alphabet
        return k_base32hex_alphabet[number_to_encode];
    }

    void Encoder::appendBytestream(const std::byte *bytestream, std::size_t size)
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

        // Iterate through the whole byte stream till the last byte
        while (byte_idx < size)
        {
            int next_bit_index = bit_idx + 5;
            _buff.push_back(encodePlace(bit_idx, current_byte, next_byte));

            // Move one byte ahead, if we are going to overflow current byte
            if (next_bit_index >= 8)
            {
                byte_idx++;
                current_byte = bytestream[byte_idx - 1];
                next_byte = bytestream[byte_idx];
            }

            bit_idx = next_bit_index % 8;
        }

        // At the last two bytes finish the work without loading the next byte
        while (bit_idx < 8)
        {
            _buff.push_back(encodePlace(bit_idx, current_byte, next_byte));
            bit_idx = bit_idx + 5; // Was bug here: adding the modulo 8 make the loop infinite
        }

        // Insert as much padding as it is required
        int padding_count = k_bit_idx_to_padding_count[bit_idx % 8];
        for (int i = 0; i < padding_count; i++)
            _buff.push_back(k_base32hex_pad_char);
    }

    void Encoder::appendSingleByte(const std::byte &byte)
    {
        _buff.push_back(encodePlace(0, byte, std::byte(0)));
        _buff.push_back(encodePlace(5, byte, std::byte(0)));

        int padding_count = k_bit_idx_to_padding_count[2];
        for (int i = 0; i < padding_count; i++)
            _buff.push_back(k_base32hex_pad_char);
    }

    void Encoder::pushBytes(const std::byte *bytestream, std::size_t size)
    {
        if (!_buff.empty())
            _buff.push_back(k_base32hex_separator_char);

        appendBytestream(bytestream, size);
    }

    std::string Encoder::encodedString() const
    {
        return {_buff.data(), _buff.size()};
    }
}
