#include <gtest/gtest.h>

#include "register/register.hpp"

using reg8_t  = reg::register_t<8>;
using reg16_t = reg::register_t<16>;
using reg32_t = reg::register_t<32>;
using reg64_t = reg::register_t<64>;

TEST(test_index_op, index_operator_8)
{
    reg::uint8_t reg_value = 0xFF;
    const auto reg_address = reinterpret_cast<uint64_t>(&reg_value);

    reg8_t reg{ reg_address };

    EXPECT_EQ(reg[0], 1);
    EXPECT_EQ(reg[7], 1);

    reg[0] = 0;
    EXPECT_EQ(reg[0], 0);

    reg[7] = 0;
    EXPECT_EQ(reg[7], 0);

    EXPECT_DEATH(reg[-1] = 1, "");
    EXPECT_DEATH(reg[8] = 1, "");
}

TEST(test_index_op, const_index_operator_8)
{
    constexpr reg::uint8_t reg_value = 0xFF;
    const auto reg_address = reinterpret_cast<uint64_t>(&reg_value);

    const reg8_t creg{ reg_address };

    EXPECT_EQ(creg[0], 1);
    EXPECT_EQ(creg[7], 1);

    EXPECT_DEATH(creg[-1], "");
    EXPECT_DEATH(creg[8], "");
}

TEST(test_index_op, index_operator_16)
{
    reg::uint16_t reg_value = 0xFFFF;
    const auto reg_address  = reinterpret_cast<uint64_t>(&reg_value);

    reg16_t reg{ reg_address };

    EXPECT_EQ(reg[0], 1);
    EXPECT_EQ(reg[15], 1);

    reg[0] = 0;
    EXPECT_EQ(reg[0], 0);

    reg[15] = 0;
    EXPECT_EQ(reg[15], 0);

    EXPECT_DEATH(reg[-1] = 1, "");
    EXPECT_DEATH(reg[16] = 1, "");
}

TEST(test_index_op, const_index_operator_16)
{
    constexpr reg::uint16_t reg_value = 0xFFFF;
    const auto reg_address  = reinterpret_cast<uint64_t>(&reg_value);

    const reg16_t creg{ reg_address };

    EXPECT_EQ(creg[0], 1);
    EXPECT_EQ(creg[15], 1);

    EXPECT_DEATH(creg[-1], "");
    EXPECT_DEATH(creg[16], "");
}

TEST(test_index_op, index_operator_32)
{
    reg::uint32_t reg_value = 0xFFFFFFFF;
    const auto reg_address  = reinterpret_cast<uint64_t>(&reg_value);

    reg32_t reg{ reg_address };

    EXPECT_EQ(reg[0], 1);
    EXPECT_EQ(reg[31], 1);

    reg[0] = 0;
    EXPECT_EQ(reg[0], 0);

    reg[31] = 0;
    EXPECT_EQ(reg[31], 0);

    EXPECT_DEATH(reg[-1] = 1, "");
    EXPECT_DEATH(reg[32] = 1, "");
}

TEST(test_index_op, const_index_operator_32)
{
    constexpr reg::uint32_t reg_value = 0xFFFFFFFF;
    const auto reg_address  = reinterpret_cast<uint64_t>(&reg_value);

    const reg32_t creg{ reg_address };

    EXPECT_EQ(creg[0], 1);
    EXPECT_EQ(creg[31], 1);

    EXPECT_DEATH(creg[-1], "");
    EXPECT_DEATH(creg[32], "");
}

TEST(test_index_op, index_operator_64)
{
    reg::uint64_t reg_value = 0xFFFFFFFFFFFFFFFF;
    const auto reg_address  = reinterpret_cast<uint64_t>(&reg_value);

    reg64_t reg{ reg_address };

    EXPECT_EQ(reg[0], 1);
    EXPECT_EQ(reg[63], 1);

    reg[0] = 0;
    EXPECT_EQ(reg[0], 0);

    reg[63] = 0;
    EXPECT_EQ(reg[63], 0);

    EXPECT_DEATH(reg[-1] = 1, "");
    EXPECT_DEATH(reg[64] = 1, "");
}

TEST(test_index_op, const_index_operator_64)
{
    constexpr reg::uint64_t reg_value = 0xFFFFFFFFFFFFFFFF;
    const auto reg_address  = reinterpret_cast<uint64_t>(&reg_value);

    const reg64_t creg{ reg_address };

    EXPECT_EQ(creg[0], 1);
    EXPECT_EQ(creg[63], 1);

    EXPECT_DEATH(creg[-1], "");
    EXPECT_DEATH(creg[64], "");
}

TEST(test_index_op, bit_proxy_assignment)
{
    reg::uint8_t reg_value = 0x00;
    const auto reg_address = reinterpret_cast<uint64_t>(&reg_value);

    reg8_t reg{ reg_address };

    EXPECT_EQ(reg[0], 0);
    EXPECT_EQ(reg[1], 0);

    reg[0] = 1;
    EXPECT_EQ(reg[0], 1);

    reg[1] = reg[0];
    EXPECT_EQ(reg[1], 1);
}