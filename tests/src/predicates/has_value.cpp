#include <any>
#include <cassert>
#include <optional>

#include <sos/predicates/has_value.hpp>

#include "container.hpp"
#include "empty_struct.hpp"


static constexpr void test_has_value_testable() noexcept {
    static_assert(    sos::has_value_testable<std::any>);
    static_assert(    sos::has_value_testable<std::optional<int>>);

    static_assert(not sos::has_value_testable<empty_struct>);
    static_assert(    sos::has_value_testable<valued_container<>>);
    static_assert(    sos::has_value_testable<nothrow_valued_container>);
}

static constexpr void test_nothrow_has_value_testable() noexcept {
    static_assert(    sos::nothrow_has_value_testable<std::any>);
    static_assert(    sos::nothrow_has_value_testable<std::optional<int>>);

    static_assert(not sos::nothrow_has_value_testable<empty_struct>);
    static_assert(not sos::nothrow_has_value_testable<valued_container<>>);
    static_assert(    sos::nothrow_has_value_testable<nothrow_valued_container>);
}

static void test_has_value() {
    // REVIEW: use static_assert if std::any becomes constexpr
    assert(not sos::has_value(std::any{}));
    assert(    sos::has_value(std::make_any<int>()));

    static_assert(not sos::has_value(std::optional<int>{}));
    static_assert(    sos::has_value(std::make_optional<int>()));

    static_assert(    sos::has_value(valued_container{true}));
    static_assert(not sos::has_value(valued_container{false}));
    static_assert(    sos::has_value(nothrow_valued_container{true}));
    static_assert(not sos::has_value(nothrow_valued_container{false}));
}


int main() {
    test_has_value_testable();
    test_nothrow_has_value_testable();
    test_has_value();
}
