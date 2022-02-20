#include <gtest/gtest.h>

#include "register/register.hpp"

using reg8_rw_t  = reg::register_t<8, reg::access_modes::read_write>;
using reg16_rw_t = reg::register_t<16, reg::access_modes::read_write>;
using reg32_rw_t = reg::register_t<32, reg::access_modes::read_write>;
using reg64_rw_t = reg::register_t<64, reg::access_modes::read_write>;

TEST(test_bit_op, basic_operation_8)
{
    reg::uint8_t reg_value = 0xFF;
    const auto reg_address = reinterpret_cast<reg::reg_addr_t>(&reg_value);

    reg8_rw_t reg{ reg_address };

    // conversion operator
    reg::uint8_t data = reg;
    EXPECT_EQ(data, 0xFF);

    // operator&=
    reg &= 0xF0;
    data = reg;
    EXPECT_EQ(data, 0xF0);

    // operator|=
    reg |= 0x0F;
    data = reg;
    EXPECT_EQ(data, 0xFF);

    // operator=
    reg  = 0xAA;
    data = reg;
    EXPECT_EQ(data, 0xAA);
}

TEST(test_bit_op, basic_operation_16)
{
    reg::uint16_t reg_value = 0xFFFF;
    const auto reg_address  = reinterpret_cast<reg::reg_addr_t>(&reg_value);

    reg16_rw_t reg{ reg_address };

    // conversion operator
    reg::uint16_t data = reg;
    EXPECT_EQ(data, 0xFFFF);

    // operator&=
    reg &= 0xFF00;
    data = reg;
    EXPECT_EQ(data, 0xFF00);

    // operator|=
    reg |= 0x00FF;
    data = reg;
    EXPECT_EQ(data, 0xFFFF);

    // operator=
    reg  = 0xAAAA;
    data = reg;
    EXPECT_EQ(data, 0xAAAA);
}

TEST(test_bit_op, basic_operation_32)
{
    reg::uint32_t reg_value = 0xFFFFFFFF;
    const auto reg_address  = reinterpret_cast<reg::reg_addr_t>(&reg_value);

    reg32_rw_t reg{ reg_address };

    // conversion operator
    reg::uint32_t data = reg;
    EXPECT_EQ(data, 0xFFFFFFFF);

    // operator&=
    reg &= 0xFFFF0000;
    data = reg;
    EXPECT_EQ(data, 0xFFFF0000);

    // operator|=
    reg |= 0x0000FFFF;
    data = reg;
    EXPECT_EQ(data, 0xFFFFFFFF);

    // operator=
    reg  = 0xAAAABBBB;
    data = reg;
    EXPECT_EQ(data, 0xAAAABBBB);
}

TEST(test_bit_op, basic_operation_64)
{
    reg::uint64_t reg_value = 0xFFFFFFFFEEEEEEEE;
    const auto reg_address  = reinterpret_cast<reg::reg_addr_t>(&reg_value);

    reg64_rw_t reg{ reg_address };

    // conversion operator
    reg::uint64_t data = reg;
    EXPECT_EQ(data, 0xFFFFFFFFEEEEEEEE);

    // operator&=
    reg &= 0xFFFFFFFF00000000;
    data = reg;
    EXPECT_EQ(data, 0xFFFFFFFF00000000);

    // operator|=
    reg |= 0x00000000EEEEEEEE;
    data = reg;
    EXPECT_EQ(data, 0xFFFFFFFFEEEEEEEE);

    // operator=
    reg  = 0xAAAABBBBCCCCDDDD;
    data = reg;
    EXPECT_EQ(data, 0xAAAABBBBCCCCDDDD);
}