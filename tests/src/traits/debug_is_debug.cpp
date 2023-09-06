#undef NDEBUG // Force debug mode
#include <sos/traits/is_debug.hpp>


static constexpr void test_is_debug() noexcept {
    static_assert(    sos::is_debug);
}


int main() {
    test_is_debug();
}
