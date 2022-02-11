#ifndef _TYPE_TRAITS_HPP_
#define _TYPE_TRAITS_HPP_

#ifdef HAS_STD_LIB
#include <type_traits>
#endif

namespace reg
{
    namespace traits
    {
#ifdef HAS_STD_LIB
        using std::enable_if;
        using std::false_type;
        using std::integral_constant;
        using std::is_same;
        using std::true_type;
#else
        template<bool B, typename T = void>
        struct enable_if
        {
        };

        template<typename T>
        struct enable_if<true, T>
        {
            using type = T;
        };

        template<typename T, T v>
        struct integral_constant
        {
            static constexpr T value = v;
            using type               = integral_constant;
            constexpr operator T() const noexcept { return value; }
        };

        using true_type  = integral_constant<bool, true>;
        using false_type = integral_constant<bool, false>;

        template<typename T, typename U>
        struct is_same : false_type
        {
        };

        template<typename T>
        struct is_same<T, T> : true_type
        {
        };
#endif
        template<bool B, typename T = void>
        using enable_if_t = typename enable_if<B, T>::type;

        template<typename... Ts>
        struct always_false
        {
            static constexpr bool value = false;
        };
    }  // namespace traits
}  // namespace reg

#endif  // _TYPE_TRAITS_HPP_