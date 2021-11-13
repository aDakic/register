#include "register/register.hpp"

void fun()
{
    static_assert(traits::is_same<int, int>::value);
    static_assert(!traits::is_same<int, float>::value);
}