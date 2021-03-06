#ifndef _REGISTER_TRAITS_HPP_
#define _REGISTER_TRAITS_HPP_

#include "common/type_traits.hpp"
#include "common/types.hpp"

namespace reg
{
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

    namespace details
    {
        template<size_t>
        struct register_address_type
        {
        };

        template<>
        struct register_address_type<1>
        {
            using type = uint8_t;
        };

        template<>
        struct register_address_type<2>
        {
            using type = uint16_t;
        };

        template<>
        struct register_address_type<4>
        {
            using type = uint32_t;
        };

        template<>
        struct register_address_type<8>
        {
            using type = uint64_t;
        };
    }  // namespace details

    using reg_addr_t = typename details::register_address_type<sizeof(void*)>::type;

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

    template<typename AccessModeTag>
    struct is_read_only
    {
        static constexpr bool value = traits::is_same<AccessModeTag, access_modes::read_only>::value;
    };

    template<typename AccessModeTag>
    struct is_read_write
    {
        static constexpr bool value = traits::is_same<AccessModeTag, access_modes::read_write>::value;
    };

    template<typename AccessModeTag>
    struct is_write_only
    {
        static constexpr bool value = traits::is_same<AccessModeTag, access_modes::write_only>::value;
    };

    template<typename AccessModeTag>
    struct is_readable
    {
        static constexpr bool value = is_read_only<AccessModeTag>::value || is_read_write<AccessModeTag>::value;
    };

    template<typename AccessModeTag>
    struct is_writeable
    {
        static constexpr bool value = is_write_only<AccessModeTag>::value || is_read_write<AccessModeTag>::value;
    };

}  // namespace reg

#endif  // _REGISTER_TRAITS_HPP_