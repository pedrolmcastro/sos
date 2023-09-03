#include <cstddef>
#include <optional>

#include <sos/predicates/bool_cast.hpp>

#include "testable.hpp"


using sos::bool_cast;


static constexpr void test_bool_cast() noexcept {
    static_assert(    bool_cast(true));
    static_assert(not bool_cast(false));

    static_assert(    bool_cast(-1));
    static_assert(not bool_cast(0U));
    static_assert(    bool_cast(1L));

    static_assert(not bool_cast(NULL));
    static_assert(not bool_cast(nullptr));

    static_assert(not bool_cast(std::optional<int>{}));
    static_assert(    bool_cast(std::make_optional<int>()));

    static_assert(    bool_cast(explicit_testable{true}));
    static_assert(not bool_cast(implicit_testable{false}));
    static_assert(    bool_cast(nothrow_explicit_testable{true}));
    static_assert(not bool_cast(nothrow_implicit_testable{false}));
}


int main() {
    test_bool_cast();
}
