#ifndef _REGISTER_IMPL_HPP_
#define _REGISTER_IMPL_HPP_

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

        explicit register_t(const reg_addr_t address) noexcept;
        register_t(const register_t&) = delete;
        register_t(register_t&&)      = delete;
        register_t& operator=(const register_t&) = delete;
        register_t& operator=(register_t&&) = delete;
        ~register_t() noexcept              = default;

        operator native_t() const noexcept;
        register_t& operator=(native_t bit_mask) noexcept;
        register_t& operator|=(native_t bit_mask) noexcept;
        register_t& operator&=(native_t bit_mask) noexcept;
        bit_proxy_t<Size, AccessMode> operator[](size_t index) noexcept;
        const bit_proxy_t<Size, AccessMode> operator[](size_t index) const noexcept;

        static constexpr size_t size = register_native_type<Size>::size;

    private:
        friend bit_proxy_t<Size, AccessMode>;
        volatile native_t* const ptr;
    };

    // IMPLEMENTATION

    template<size_t Size, typename AccessMode>
    register_t<Size, AccessMode>::register_t(const reg_addr_t address) noexcept : ptr{ reinterpret_cast<native_t*>(address) }
    {
    }

    template<size_t Size, typename AccessMode>
    register_t<Size, AccessMode>::operator native_t() const noexcept
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

    template<size_t Size, typename AccessMode>
    register_t<Size, AccessMode>& register_t<Size, AccessMode>::operator=(native_t bit_mask) noexcept
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

    template<size_t Size, typename AccessMode>
    register_t<Size, AccessMode>& register_t<Size, AccessMode>::operator|=(native_t bit_mask) noexcept
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

    template<size_t Size, typename AccessMode>
    register_t<Size, AccessMode>& register_t<Size, AccessMode>::operator&=(native_t bit_mask) noexcept
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

    template<size_t Size, typename AccessMode>
    bit_proxy_t<Size, AccessMode> register_t<Size, AccessMode>::operator[](size_t index) noexcept
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

    template<size_t Size, typename AccessMode>
    const bit_proxy_t<Size, AccessMode> register_t<Size, AccessMode>::operator[](size_t index) const noexcept
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
}  // namespace reg

#endif  // _REGISTER_IMPL_HPP_