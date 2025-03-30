#include <gtest/gtest.h>

#include "src/base32/encoder.hpp"

namespace l4::base32::test
{
    class EncoderTest : public testing::Test
    {
    protected:
        l4::base32::Encoder _encoder;
    };

    TEST_F(EncoderTest, EmptyStream)
    {
        char input[] = "";

        _encoder.pushBytes(reinterpret_cast<const std::byte *>(input), sizeof(input) - 1);
        std::string res = _encoder.encodedString();

        ASSERT_EQ(res, "");
    }

    TEST_F(EncoderTest, SingleByte)
    {
        char input[] = "f";

        _encoder.pushBytes(reinterpret_cast<const std::byte *>(input), sizeof(input) - 1);
        std::string res = _encoder.encodedString();

        ASSERT_EQ(res, "CO======");
    }

    TEST_F(EncoderTest, TwoBytes)
    {
        char input[] = "fo";

        _encoder.pushBytes(reinterpret_cast<const std::byte *>(input), sizeof(input) - 1);
        std::string res = _encoder.encodedString();

        ASSERT_EQ(res, "CPNG====");
    }

    TEST_F(EncoderTest, ThreeBytes)
    {
        char input[] = "foo";

        _encoder.pushBytes(reinterpret_cast<const std::byte *>(input), sizeof(input) - 1);
        std::string res = _encoder.encodedString();

        ASSERT_EQ(res, "CPNMU===");
    }

    TEST_F(EncoderTest, FourBytes)
    {
        char input[] = "foob";

        _encoder.pushBytes(reinterpret_cast<const std::byte *>(input), sizeof(input) - 1);
        std::string res = _encoder.encodedString();

        ASSERT_EQ(res, "CPNMUOG=");
    }

    TEST_F(EncoderTest, FiveBytes)
    {
        char input[] = "fooba";

        _encoder.pushBytes(reinterpret_cast<const std::byte *>(input), sizeof(input) - 1);
        std::string res = _encoder.encodedString();

        ASSERT_EQ(res, "CPNMUOJ1");
    }

    TEST_F(EncoderTest, SixBytes)
    {
        char input[] = "foobar";

        _encoder.pushBytes(reinterpret_cast<const std::byte *>(input), sizeof(input) - 1);
        std::string res = _encoder.encodedString();

        ASSERT_EQ(res, "CPNMUOJ1E8======");
    }
}
