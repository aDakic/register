#include "register_impl.hpp"

namespace reg
{
    using reg8_rw_t = register_t<8, access_modes::read_write>;
    using reg8_ro_t = register_t<8, access_modes::read_only>;
    using reg8_wo_t = register_t<8, access_modes::write_only>;

    using reg16_rw_t = register_t<16, access_modes::read_write>;
    using reg16_ro_t = register_t<16, access_modes::read_only>;
    using reg16_wo_t = register_t<16, access_modes::write_only>;

    using reg32_rw_t = register_t<32, access_modes::read_write>;
    using reg32_ro_t = register_t<32, access_modes::read_only>;
    using reg32_wo_t = register_t<32, access_modes::write_only>;

    using reg64_rw_t = register_t<64, access_modes::read_write>;
    using reg64_ro_t = register_t<64, access_modes::read_only>;
    using reg64_wo_t = register_t<64, access_modes::write_only>;
}