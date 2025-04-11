#pragma once

#include <string>
#include <vector>

namespace l4::base32
{
/**
 * The class represents a process of decoding base32hex string into an arbitrary bytestream.
 * It can decode multiple bytestreams that are separated by the ; character in the input string.
 */
class Decoder
{
   private:
    std::string _encoded_string;
    std::size_t _idx;

    std::vector<std::byte> decodeBytestream();

   public:
    // Rule of 5 - non copiable object

    /**
     * Creates a decoder which will operate on given encoded string.
     * @param encoded_string String containing one or more encoded bytestreams seperated by the ; character.
     */
    Decoder(const std::string& encoded_string);
    Decoder(const Decoder&) = delete;
    Decoder(Decoder&&) = default;
    Decoder& operator=(const Decoder&) = delete;
    Decoder& operator=(Decoder&&) = default;

    /**
     * It says whether the decoder has any bytestream to decode.
     * @return Returns false when there is a bytestream to decode. Otherwise, true
     */
    bool isEmpty() const;

    /**
     * It makes actual decoding of the string into bytestream.
     * It returns a vector of bytes to inform how long the bytestream is.
     * @return Vector of bytes that was encoded in string passed during the creation of the decoder.
     */
    std::vector<std::byte> pullBytestream();
};

}  // namespace l4::base32
