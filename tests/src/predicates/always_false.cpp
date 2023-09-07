#include <sos/predicates/always_false.hpp>

#include "testable.hpp"
#include "empty_struct.hpp"


static constexpr void test_always_false() noexcept {
    static_assert(not sos::always_false(-1));
    static_assert(not sos::always_false(0U));
    static_assert(not sos::always_false(1L));

    static_assert(not sos::always_false(true));
    static_assert(not sos::always_false(false));

    static_assert(not sos::always_false(empty_struct{}));
    static_assert(not sos::always_false(explicit_testable{true}));
    static_assert(not sos::always_false(nothrow_implicit_testable{false}));
}


int main() {
    test_always_false();
}
