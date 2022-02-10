#ifndef _BIT_PROXY_HPP_
#define _BIT_PROXY_HPP_

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
        using reg_value_t = typename reg_t::reg_value_t;

        bit_proxy_t(reg_t* reg, size_t num) noexcept;
        bit_proxy_t& operator   =(const bit_proxy_t& other) noexcept;
        ~bit_proxy_t() noexcept = default;

        void operator=(reg_value_t val) noexcept;
        operator reg_value_t() const noexcept;

    private:
        reg_t* const owner;
        size_t bit_num;
    };

    // IMPLEMENTATION

    template<size_t Size, typename AccessModeTag>
    inline bit_proxy_t<Size, AccessModeTag>::bit_proxy_t(reg_t* reg, size_t num) noexcept : owner{ reg }, bit_num{ num }
    {
    }

    template<size_t Size, typename AccessModeTag>
    inline bit_proxy_t<Size, AccessModeTag>& bit_proxy_t<Size, AccessModeTag>::operator=(const bit_proxy_t& other) noexcept
    {
        *this = static_cast<reg_value_t>(other);
        return *this;
    }

    template<size_t Size, typename AccessModeTag>
    inline void bit_proxy_t<Size, AccessModeTag>::operator=(reg_value_t val) noexcept
    {
        if (val == 0)
            *(owner->ptr) &= ~(1 << bit_num);
        else
            *(owner->ptr) |= (1 << bit_num);
    }

    template<size_t Size, typename AccessModeTag>
    inline bit_proxy_t<Size, AccessModeTag>::operator reg_value_t() const noexcept
    {
        return (*(owner->ptr) & (1 << bit_num)) ? 1 : 0;
    }

}  // namespace reg

#endif  // _BIT_PROXY_HPP_