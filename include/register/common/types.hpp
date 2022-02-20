#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#ifdef HAS_STD_LIB
#include <cstdint>
#endif

namespace reg
{
#ifdef HAS_STD_LIB
    using std::size_t;
    using std::uint16_t;
    using std::uint32_t;
    using std::uint64_t;
    using std::uint8_t;
#endif
}  // namespace reg

#endif  // _TYPES_HPP_