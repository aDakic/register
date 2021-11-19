#pragma once

#include "register/common/types.hpp"

namespace reg
{
    template<size_t Size, typename AccessModeTag>
    class register_t;

    template<size_t Size, typename AccessModeTag>
    class bit_proxy_t
    {
    public:
        using reg_t    = register_t<Size, AccessModeTag>;
        using native_t = typename reg_t::native_t;

        bit_proxy_t(reg_t* reg, size_t num) : owner{ reg }, bit_num{ num } { }

        operator native_t() const { return (*(owner->ptr) & (1 << bit_num)) ? 1 : 0; }

        void operator=(native_t val)
        {
            if (val == 0)
                *(owner->ptr) &= ~(1 << bit_num);
            else
                *(owner->ptr) |= (1 << bit_num);
        }

        bit_proxy_t& operator=(const bit_proxy_t& other)
        {
            *this = static_cast<native_t>(other);
            return *this;
        }

    private:
        reg_t* const owner;
        size_t bit_num;
    };
}  // namespace reg