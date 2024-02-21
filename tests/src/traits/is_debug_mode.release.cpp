#define NDEBUG 1 // Force release mode


#include "sos/traits/is_debug_mode.hpp"


using sos::traits::is_debug_mode;


static consteval void is_debug_mode_fails_in_release() noexcept {
    static_assert(not is_debug_mode);
}


int main() {
    is_debug_mode_fails_in_release();
}
