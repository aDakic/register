#pragma once

#include "common/type_traits.hpp"
#include "register_traits.hpp"

namespace reg
{
    using namespace traits;

    struct read_write
    {
    };
    struct read_only
    {
    };
    struct write_only
    {
    };

    template<size_t Size, typename AccessMode = read_write>
    class register_t
    {
    public:
        using reg_native_t = typename register_trait<Size>::type;

        explicit register_t(const uint64_t address) : ptr{ reinterpret_cast<reg_native_t*>(address) } { }

        template<typename T = AccessMode,
                 typename   = enable_if_t<is_same<T, read_only>::value || is_same<T, read_write>::value>>
        operator uint8_t() const
        {
            return *ptr;
        }

        template<typename T = AccessMode,
                 typename   = enable_if_t<is_same<T, write_only>::value || is_same<T, read_write>::value>>
        register_t& operator=(uint8_t bit_mask)
        {
            *ptr = bit_mask;
            return *this;
        }

        template<typename T = AccessMode, typename = enable_if_t<is_same<T, read_write>::value>>
        register_t& operator|=(reg_native_t bit_mask)
        {
            *ptr |= bit_mask;
            return *this;
        }

        template<typename T = AccessMode, typename = enable_if_t<is_same<T, read_write>::value>>
        register_t& operator&=(reg_native_t bit_mask)
        {
            *ptr &= bit_mask;
            return *this;
        }

        // template<typename T = AccessMode, typename = enable_if_t<is_same<T, read_write>::value>>
        // bit_t operator[](unsigned int index)
        // {
        //     return bit_t{ this, index };
        // }

    private:
        volatile reg_native_t* const ptr;
    };
}  // namespace reg