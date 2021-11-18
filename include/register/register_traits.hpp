#pragma once

#include "common/types.hpp"

namespace reg
{
    template<size_t>
    struct register_trait
    {
    };

    template<>
    struct register_trait<8>
    {
        static constexpr size_t size = 8;
        using type                   = uint8_t;
    };

    template<>
    struct register_trait<16>
    {
        static constexpr size_t size = 16;
        using type                   = uint16_t;
    };

    template<>
    struct register_trait<32>
    {
        static constexpr size_t size = 32;
        using type                   = uint32_t;
    };

    template<>
    struct register_trait<64>
    {
        static constexpr size_t size = 64;
        using type                   = uint64_t;
    };
}  // namespace reg