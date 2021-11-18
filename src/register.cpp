#include "register/register.hpp"

#include "register/bit_proxy.hpp"
#include "register/common/type_traits.hpp"
#include "register/common/types.hpp"
void fun()
{
    static_assert(reg::traits::is_same<int, int>::value);
    static_assert(!reg::traits::is_same<int, float>::value);
}