#pragma once

#include "common/type_traits.hpp"
#include "common/types.hpp"

namespace reg
{
    namespace access_modes
    {
        struct read_write
        {
        };
        struct read_only
        {
        };
        struct write_only
        {
        };
    }  // namespace access_modes

    template<size_t>
    struct register_native_type
    {
    };

    template<>
    struct register_native_type<8>
    {
        static constexpr size_t size = 8;
        using type                   = uint8_t;
    };

    template<>
    struct register_native_type<16>
    {
        static constexpr size_t size = 16;
        using type                   = uint16_t;
    };

    template<>
    struct register_native_type<32>
    {
        static constexpr size_t size = 32;
        using type                   = uint32_t;
    };

    template<>
    struct register_native_type<64>
    {
        static constexpr size_t size = 64;
        using type                   = uint64_t;
    };

    template<typename AccessModeTag>
    struct is_read_only
    {
        static constexpr bool value = traits::is_same<AccessModeTag, access_modes::read_only>::value;
    };

    template<typename AccessModeTag>
    inline constexpr bool is_read_only_v = is_read_only<AccessModeTag>::value;

    template<typename AccessModeTag>
    struct is_read_write
    {
        static constexpr bool value = traits::is_same<AccessModeTag, access_modes::read_write>::value;
    };

    template<typename AccessModeTag>
    inline constexpr bool is_read_write_v = is_read_write<AccessModeTag>::value;

    template<typename AccessModeTag>
    struct is_write_only
    {
        static constexpr bool value = traits::is_same<AccessModeTag, access_modes::write_only>::value;
    };

    template<typename AccessModeTag>
    inline constexpr bool is_write_only_v = is_write_only<AccessModeTag>::value;

    template<typename AccessModeTag>
    struct is_readable
    {
        static constexpr bool value = is_read_only<AccessModeTag>::value || is_read_write<AccessModeTag>::value;
    };

    template<typename AccessModeTag>
    inline constexpr bool is_readable_v = is_readable<AccessModeTag>::value;

    template<typename AccessModeTag>
    struct is_writeable
    {
        static constexpr bool value = is_write_only<AccessModeTag>::value || is_read_write<AccessModeTag>::value;
    };

    template<typename AccessModeTag>
    inline constexpr bool is_writeable_v = is_writeable<AccessModeTag>::value;
}  // namespace reg