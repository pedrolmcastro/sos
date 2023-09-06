#define NDEBUG 1 // Force release mode
#include <sos/traits/is_debug.hpp>


static constexpr void test_is_debug() noexcept {
    static_assert(not sos::is_debug);
}


int main() {
    test_is_debug();
}
