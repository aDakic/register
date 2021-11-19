#pragma once

#include "bit_proxy.hpp"
#include "common/assert.hpp"
#include "common/type_traits.hpp"
#include "register_traits.hpp"

namespace reg
{

    template<size_t Size, typename AccessMode = access_modes::read_write>
    class register_t
    {
    public:
        using native_t = typename register_native_type<Size>::type;

        explicit register_t(const uint64_t address) : ptr{ reinterpret_cast<native_t*>(address) } { }

        operator native_t() const
        {
            if constexpr (is_readable_v<AccessMode>)
            {
                return *ptr;
            }
            else
            {
                static_assert(traits::always_false<AccessMode>, "Register doesn't provide read access.");
            }
        }

        register_t& operator=(native_t bit_mask)
        {
            if constexpr (is_writeable_v<AccessMode>)
            {
                *ptr = bit_mask;
                return *this;
            }
            else
            {
                static_assert(traits::always_false<AccessMode>, "Register doesn't provide write access.");
            }
        }

        register_t& operator|=(native_t bit_mask)
        {
            if constexpr (is_read_write_v<AccessMode>)
            {
                *ptr |= bit_mask;
                return *this;
            }
            else
            {
                static_assert(traits::always_false<AccessMode>, "Register doesn't provide read-write access.");
            }
        }

        register_t& operator&=(native_t bit_mask)
        {
            if constexpr (is_read_write_v<AccessMode>)
            {
                *ptr &= bit_mask;
                return *this;
            }
            else
            {
                static_assert(traits::always_false<AccessMode>, "Register doesn't provide read-write access.");
            }
        }

        bit_proxy_t<Size, AccessMode> operator[](size_t index)
        {
            if constexpr (is_read_write_v<AccessMode>)
            {
                assert(index >= 0 && index < size);
                return { this, index };
            }
            else
            {
                static_assert(traits::always_false<AccessMode>, "Register doesn't provide read-write access.");
            }
        }

        const bit_proxy_t<Size, AccessMode> operator[](size_t index) const
        {
            if constexpr (is_readable_v<AccessMode>)
            {
                assert(index >= 0 && index < size);
                return { const_cast<register_t<Size, AccessMode>*>(this), index };
            }
            else
            {
                static_assert(traits::always_false<AccessMode>, "Register doesn't provide read access.");
            }
        }

        static constexpr size_t size = register_native_type<Size>::size;

    private:
        friend bit_proxy_t<Size, AccessMode>;
        volatile native_t* const ptr;
    };
}  // namespace reg