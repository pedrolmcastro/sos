#undef NDEBUG // Force debug mode


#include "sos/traits/is_debug_mode.hpp"


using sos::traits::is_debug_mode;


static consteval void is_debug_mode_succeeds_in_debug() noexcept {
    static_assert(is_debug_mode);
}


int main() {
    is_debug_mode_succeeds_in_debug();
}
