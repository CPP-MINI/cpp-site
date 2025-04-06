#pragma once
#include <string>
#include <cstdint>
#include <vector>

namespace l4::base32
{


    /**
     *
     */
    class Encoder
    {
    private:


        // Buffer of already encoded data. Will expand during the pushBytes function.
        std::vector<char> _buff;

        char encodePlace(int bit_idx, std::byte current_byte, std::byte next_byte);
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
