#pragma once

#include "bit_proxy.hpp"
#include "common/assert.hpp"
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
        using native_t = typename register_trait<Size>::type;

        explicit register_t(const uint64_t address) : ptr{ reinterpret_cast<native_t*>(address) } { }

        template<typename T = AccessMode,
                 typename   = enable_if_t<is_same<T, read_only>::value || is_same<T, read_write>::value>>
        operator native_t() const
        {
            return *ptr;
        }

        template<typename T = AccessMode,
                 typename   = enable_if_t<is_same<T, write_only>::value || is_same<T, read_write>::value>>
        register_t& operator=(native_t bit_mask)
        {
            *ptr = bit_mask;
            return *this;
        }

        template<typename T = AccessMode, typename = enable_if_t<is_same<T, read_write>::value>>
        register_t& operator|=(native_t bit_mask)
        {
            *ptr |= bit_mask;
            return *this;
        }

        template<typename T = AccessMode, typename = enable_if_t<is_same<T, read_write>::value>>
        register_t& operator&=(native_t bit_mask)
        {
            *ptr &= bit_mask;
            return *this;
        }

        template<typename T = AccessMode, typename = enable_if_t<is_same<T, read_write>::value>>
        bit_proxy_t<Size, AccessMode> operator[](size_t index)
        {
            assert(index >= 0 && index < size);
            return { this, index };
        }

        template<typename T = AccessMode, typename = enable_if_t<is_same<T, read_write>::value>>
        const bit_proxy_t<Size, AccessMode> operator[](size_t index) const
        {
            assert(index >= 0 && index < size);
            return { const_cast<register_t<Size, AccessMode>*>(this), index };
        }

        static constexpr size_t size = register_trait<Size>::size;

    private:
        friend bit_proxy_t<Size, AccessMode>;
        volatile native_t* const ptr;
    };
}  // namespace reg