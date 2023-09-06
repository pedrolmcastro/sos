#include <cstddef>

#include <sos/check/policy.hpp>
#include <sos/predicates/is_null.hpp>
#include <sos/predicates/is_empty.hpp>
#include <sos/predicates/has_value.hpp>

#define NDEBUG 1 // Force release mode
#include <sos/check/checkable.hpp>

#include "testable.hpp"
#include "container.hpp"
#include "empty_struct.hpp"
#include "comparable_with.hpp"


static constexpr void test_noop_checkable() noexcept {
    static_assert(not sos::noop_checkable<sos::throws_t, empty_struct>);
    static_assert(not sos::noop_checkable<sos::throws_t, explicit_testable>);
    static_assert(not sos::noop_checkable<sos::throws_t, nothrow_implicit_testable>);

    static_assert(    sos::noop_checkable<sos::asserts_t, empty_struct>);
    static_assert(    sos::noop_checkable<sos::asserts_t, explicit_testable>);
    static_assert(    sos::noop_checkable<sos::asserts_t, nothrow_implicit_testable>);

    static_assert(    sos::noop_checkable<sos::unenforced_t, empty_struct>);
    static_assert(    sos::noop_checkable<sos::unenforced_t, explicit_testable>);
    static_assert(    sos::noop_checkable<sos::unenforced_t, nothrow_implicit_testable>);
}

static constexpr void test_checkable() noexcept {
    static_assert(    sos::checkable<sos::throws_t, void*>);
    static_assert(not sos::checkable<sos::throws_t, empty_struct>);
    static_assert(    sos::checkable<sos::throws_t, explicit_testable>);
    static_assert(    sos::checkable<sos::throws_t, nothrow_implicit_testable>);

    static_assert(not sos::checkable<sos::terminates_t, sized_container<>>);
    static_assert(    sos::checkable<sos::terminates_t, sized_container<>, sos::is_empty_t>);
    static_assert(not sos::checkable<sos::terminates_t, valued_container<>, sos::is_empty_t>);
    static_assert(    sos::checkable<sos::terminates_t, emptiable_container<>, sos::is_empty_t>);
}

static constexpr void test_nothrow_checkable() noexcept {
    static_assert(not sos::nothrow_checkable<sos::throws_t, empty_struct>);
    static_assert(not sos::nothrow_checkable<sos::throws_t, explicit_testable>);
    static_assert(not sos::nothrow_checkable<sos::throws_t, nothrow_implicit_testable>);

    static_assert(    sos::nothrow_checkable<sos::asserts_t, valued_container<>>);
    static_assert(    sos::nothrow_checkable<sos::asserts_t, valued_container<>, sos::has_value_t>);
    static_assert(    sos::nothrow_checkable<sos::asserts_t, nothrow_valued_container, sos::has_value_t>);

    static_assert(    sos::nothrow_checkable<sos::unenforced_t, comparable_with<std::nullptr_t>>);
    static_assert(    sos::nothrow_checkable<sos::unenforced_t, comparable_with<std::nullptr_t>, sos::is_null<std::nullptr_t>>);
    static_assert(    sos::nothrow_checkable<sos::unenforced_t, nothrow_comparable_with<std::nullptr_t>, sos::is_null<std::nullptr_t>>);
}


int main() {
    test_noop_checkable();
    test_checkable();
    test_nothrow_checkable();
}
