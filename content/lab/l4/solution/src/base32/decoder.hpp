#pragma once

#include <string>
#include <vector>

namespace l4::base32 {
    /**
     *
     */
    class Decoder {
    private:
        std::string _encoded_string;
        std::size_t _idx;

    public:
        // Rule of 5 - non copiable object

        /**
         *
         * @param encoded_string
         */
        Decoder(const std::string& encoded_string);
        Decoder(const Decoder&) = delete;
        Decoder(Decoder&&) = default;
        Decoder& operator=(const Decoder&) = delete;
        Decoder& operator=(Decoder&&) = default;

        /**
         *
         * @return
         */
        std::size_t byteStreamsCount() const;

        /**
         *
         * @return
         */
        std::vector<std::byte> pullBytestream() const;
    };

}
