#include <gtest/gtest.h>

#include "register/register.hpp"

using reg8_t = reg::register_t<8>;

TEST(test_bit_op, basic_operation_8)
{
    const uint8_t reg      = 0xFF;
    const auto reg_address = reinterpret_cast<uint64_t>(&reg);

    reg8_t r{ reg_address };

    // conversion operator
    reg::uint8_t data = r;
    EXPECT_EQ(data, 0xFF);
}