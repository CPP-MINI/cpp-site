#pragma once
#include <string>
#include <cstdint>
#include <vector>

namespace l4::base32
{
    // Source: https://datatracker.ietf.org/doc/html/rfc4648#section-7
    static constexpr char k_base32hex_alphabet[]
    {
        '0','1','2','3','4','5','6','7',
        '8','9','A','B','C','D','E','F',
        'G','H','I','J','K','L','M','N',
        'O','P','Q','R','S','T','U','V',
    };

    static constexpr char k_base32hex_pad_char = '=';
    static constexpr int k_bit_idx_to_padding_count[]
    {
        0,  // 0
        3,  // 1
        6,  // 2
        1,  // 3
        4,  // 4
        -1, // 5 - illegal
        -1, // 6 - illegal
        -1, // 7 - illegal
    };

    static constexpr char k_base32hex_separator_char = ';'; // Extension of the RFC!

    /**
     *
     */
    class Encoder
    {
    private:
        static constexpr uint8_t base32_bit_mask = 0b11111;

        // Buffer of already encoded data. Will expand during the pushBytes function.
        std::vector<char> _buff;

        void appendBytestream(const std::byte *bytestream, std::size_t size);
        void appendSingleByte(const std::byte& byte);


    public:
        // Rule of 5 - non copiable object
        
        /**
         * 
         */
        Encoder() = default;
        Encoder(const Encoder&) = delete;
        Encoder(Encoder&&) = default;
        Encoder& operator=(const Encoder&) = delete;
        Encoder& operator=(Encoder&&) = default;

        /**
         * 
         * @param bytestream 
         * @param size 
         */
        void pushBytes(const std::byte *bytestream, std::size_t size);
        /**
         * 
         * @return 
         */
        [[nodiscard]] std::string encodedString() const;
    };
}
