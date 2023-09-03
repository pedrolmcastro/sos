#include <any>
#include <optional>

#include <sos/concepts/has_value_testable.hpp>

#include "container.hpp"
#include "empty_struct.hpp"


using sos::has_value_testable;
using sos::nothrow_has_value_testable;


static constexpr void test_has_value_testable() noexcept {
    static_assert(    has_value_testable<std::any>);
    static_assert(    has_value_testable<std::optional<int>>);

    static_assert(not has_value_testable<empty_struct>);
    static_assert(    has_value_testable<valued_container<>>);
    static_assert(    has_value_testable<nothrow_valued_container>);
}

static constexpr void test_nothrow_has_value_testable() noexcept {
    static_assert(    nothrow_has_value_testable<std::any>);
    static_assert(    nothrow_has_value_testable<std::optional<int>>);

    static_assert(not nothrow_has_value_testable<empty_struct>);
    static_assert(not nothrow_has_value_testable<valued_container<>>);
    static_assert(    nothrow_has_value_testable<nothrow_valued_container>);
}


int main() {
    test_has_value_testable();
    test_nothrow_has_value_testable();
}
