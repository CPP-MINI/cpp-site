#include <gtest/gtest.h>

#include "lib/base32/decoder.hpp"

namespace l4::base32::test
{
    TEST(DecoderTest, EmptyStream)
    {
        char input[] = "";
        char expected_chars[] = "";
        std::vector expected(reinterpret_cast<std::byte *>(expected_chars),
                             reinterpret_cast<std::byte *>(expected_chars) + sizeof(expected_chars) - 1);

        Decoder decoder(input);

        ASSERT_TRUE(decoder.isEmpty());
        const std::vector<std::byte> res = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res.size(), expected.size());
        for (size_t i = 0; i < res.size(); ++i)
        {
            EXPECT_EQ(res[i], expected[i]) << "Different value at " << i;
        }
    }

    TEST(DecoderTest, SingleByte)
    {
        char input[] = "CO======";
        char expected_chars[] = "f";
        std::vector expected(reinterpret_cast<std::byte *>(expected_chars),
                             reinterpret_cast<std::byte *>(expected_chars) + sizeof(expected_chars) - 1);

        Decoder decoder(input);

        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res.size(), expected.size());
        for (size_t i = 0; i < res.size(); ++i)
        {
            EXPECT_EQ(res[i], expected[i]) << "Different value at " << i;
        }
    }

    TEST(DecoderTest, TwoBytes)
    {
        char input[] = "CPNG====";
        char expected_chars[] = "fo";
        std::vector expected(reinterpret_cast<std::byte *>(expected_chars),
                             reinterpret_cast<std::byte *>(expected_chars) + sizeof(expected_chars) - 1);

        Decoder decoder(input);

        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res.size(), expected.size());
        for (size_t i = 0; i < res.size(); ++i)
        {
            EXPECT_EQ(res[i], expected[i]) << "Different value at " << i;
        }
    }

    TEST(DecoderTest, ThreeBytes)
    {
        char input[] = "CPNMU===";
        char expected_chars[] = "foo";
        std::vector expected(reinterpret_cast<std::byte *>(expected_chars),
                             reinterpret_cast<std::byte *>(expected_chars) + sizeof(expected_chars) - 1);

        Decoder decoder(input);

        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res.size(), expected.size());
        for (size_t i = 0; i < res.size(); ++i)
        {
            EXPECT_EQ(res[i], expected[i]) << "Different value at " << i;
        }
    }

    TEST(DecoderTest, FourBytes)
    {
        char input[] = "CPNMUOG=";
        char expected_chars[] = "foob";
        std::vector expected(reinterpret_cast<std::byte *>(expected_chars),
                             reinterpret_cast<std::byte *>(expected_chars) + sizeof(expected_chars) - 1);

        Decoder decoder(input);

        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res.size(), expected.size());
        for (size_t i = 0; i < res.size(); ++i)
        {
            EXPECT_EQ(res[i], expected[i]) << "Different value at " << i;
        }
    }

    TEST(DecoderTest, FiveBytes)
    {
        char input[] = "CPNMUOJ1";
        char expected_chars[] = "fooba";
        std::vector expected(reinterpret_cast<std::byte *>(expected_chars),
                             reinterpret_cast<std::byte *>(expected_chars) + sizeof(expected_chars) - 1);

        Decoder decoder(input);

        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res.size(), expected.size());
        for (size_t i = 0; i < res.size(); ++i)
        {
            EXPECT_EQ(res[i], expected[i]) << "Different value at " << i;
        }
    }

    TEST(DecoderTest, SixBytes)
    {
        char input[] = "CPNMUOJ1E8======";
        char expected_chars[] = "foobar";
        std::vector expected(reinterpret_cast<std::byte *>(expected_chars),
                             reinterpret_cast<std::byte *>(expected_chars) + sizeof(expected_chars) - 1);

        Decoder decoder(input);

        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res.size(), expected.size());
        for (size_t i = 0; i < res.size(); ++i)
        {
            EXPECT_EQ(res[i], expected[i]) << "Different value at " << i;
        }
    }

    TEST(DecoderTest, ChainTwoBytestreams)
    {
        char input[] = "CPNMUOJ1E8======;CPNMU===";
        char expected_chars1[] = "foobar";
        char expected_chars2[] = "foo";

        std::vector expected1(reinterpret_cast<std::byte *>(expected_chars1),
                             reinterpret_cast<std::byte *>(expected_chars1) + sizeof(expected_chars1) - 1);
        std::vector expected2(reinterpret_cast<std::byte *>(expected_chars2),
                     reinterpret_cast<std::byte *>(expected_chars2) + sizeof(expected_chars2) - 1);

        Decoder decoder(input);
        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res1 = decoder.pullBytestream();
        ASSERT_FALSE(decoder.isEmpty());
        const std::vector<std::byte> res2 = decoder.pullBytestream();
        ASSERT_TRUE(decoder.isEmpty());

        ASSERT_EQ(res1.size(), expected1.size());
        for (size_t i = 0; i < res1.size(); ++i)
        {
            EXPECT_EQ(res1[i], expected1[i]) << "Different value at " << i;
        }
        ASSERT_EQ(res2.size(), expected2.size());
        for (size_t i = 0; i < res2.size(); ++i)
        {
            EXPECT_EQ(res2[i], expected2[i]) << "Different value at " << i;
        }
    }
}
