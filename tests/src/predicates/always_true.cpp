#include <sos/predicates/always_true.hpp>

#include "testable.hpp"
#include "empty_struct.hpp"


static constexpr void test_always_true() noexcept {
    static_assert(    sos::always_true(-1));
    static_assert(    sos::always_true(0U));
    static_assert(    sos::always_true(1L));

    static_assert(    sos::always_true(true));
    static_assert(    sos::always_true(false));

    static_assert(    sos::always_true(empty_struct{}));
    static_assert(    sos::always_true(explicit_testable{true}));
    static_assert(    sos::always_true(nothrow_implicit_testable{false}));
}


int main() {
    test_always_true();
}
