#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace l4::base32
{
/**
 * The class represents a process of encoding arbitrary bytestream into base32hex encoded string.
 * It can encode multiple bytestreams and separate it by the ; character.
 */
class Encoder
{
   private:
    // Buffer of already encoded data. Will expand during the pushBytes function.
    std::vector<char> _buff;

    char encodePlace(int bit_idx, std::byte current_byte, std::byte next_byte);
    void appendBytestream(const std::byte* bytestream, std::size_t size);
    void appendSingleByte(const std::byte& byte);

   public:
    // Rule of 5 - non copiable object

    /**
     * Creates empty encoder object
     */
    Encoder() = default;
    Encoder(const Encoder&) = delete;
    Encoder(Encoder&&) = default;
    Encoder& operator=(const Encoder&) = delete;
    Encoder& operator=(Encoder&&) = default;

    /**
     * It takes a bytestream and encodes it into base32hex encoding.
     * To aquire encoded string use encodedString method.
     * @param bytestream The pointer to the block containing bytestream.
     * @param size Length in bytes of the block
     */
    void pushBytes(const std::byte* bytestream, std::size_t size);

    /**
     * It returns encoded string containing data from consecutive calls of pushBytes method
     * @return Returns encoded string containing multiple encoded bytestreams separated by the ; charater.
     */
    [[nodiscard]] std::string encodedString() const;
};
}  // namespace l4::base32
