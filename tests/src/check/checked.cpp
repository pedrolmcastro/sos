#include <cassert>
#include <utility>
#include <concepts>
#include <optional>
#include <exception>
#include <type_traits>

#include <sos/check/policy.hpp>
#include <sos/check/checked.hpp>
#include <sos/check/failed_check.hpp>
#include <sos/predicates/is_empty.hpp>
#include <sos/predicates/has_value.hpp>
#include <sos/predicates/is_filled.hpp>

#include "testable.hpp"
#include "container.hpp"


static constexpr void test_checked_constructible() noexcept {
    static_assert(not std::constructible_from<
        sos::checked<emptiable_container<>>,
        sos::throws_t
    >);

    static_assert(    std::constructible_from<
        sos::checked<emptiable_container<>>,
        sos::unenforced_t
    >);

    static_assert(    std::constructible_from<
        sos::checked<emptiable_container<>, sos::is_empty_t>,
        sos::throws_t
    >);

    static_assert(    std::constructible_from<
        sos::checked<emptiable_container<>, sos::is_empty_t>,
        sos::unenforced_t
    >);
}

static constexpr void test_checked_nothrow_constructible() noexcept {
    static_assert(not std::is_nothrow_constructible_v<
        sos::checked<emptiable_container<>, sos::is_empty_t>,
        sos::throws_t
    >);

    static_assert(not std::is_nothrow_constructible_v<
        sos::checked<emptiable_container<>, sos::is_empty_t>,
        sos::terminates_t
    >);

    static_assert(    std::is_nothrow_constructible_v<
        sos::checked<emptiable_container<>, sos::is_empty_t>,
        sos::unenforced_t
    >);


    static_assert(not std::is_nothrow_constructible_v<
        sos::checked<nothrow_emptiable_container, sos::is_empty_t>,
        sos::throws_t
    >);

    static_assert(    std::is_nothrow_constructible_v<
        sos::checked<nothrow_emptiable_container, sos::is_empty_t>,
        sos::terminates_t
    >);

    static_assert(    std::is_nothrow_constructible_v<
        sos::checked<nothrow_emptiable_container, sos::is_empty_t>,
        sos::unenforced_t
    >);
}


static void test_checked_reset() {
    auto checked = sos::make_checked<sos::asserts_t, int>(1);
    assert(checked.get() == 1);

    checked.reset(sos::asserts, 2);
    assert(checked.get() == 2);

    checked.reset(sos::asserts, sos::make_checked<sos::asserts_t, float>(3.0f));
    assert(std::move(checked).get() == 3);
}

static constexpr void test_checked_unenforced() noexcept {
    constexpr auto checked = sos::checked<std::optional<int>, sos::has_value_t>{
        sos::unenforced,
        std::optional<int>{},
        sos::has_value
    };

    static_assert(checked.get() == std::nullopt);
}


static void test_checked_construction_fail() {
    try {
        sos::checked<sized_container<>, sos::is_filled_t>{sos::throws, sized_container{0}};
        std::terminate();
    }
    catch (sos::failed_check const&) {}
}

static void test_make_checked_fail() {
    try {
        (void)sos::make_checked<sos::throws_t, explicit_testable>(false);
        std::terminate();
    }
    catch (sos::failed_check const&) {}
}

static void test_checked_reset_fail() {
    auto checked = sos::make_checked<sos::throws_t, bool>(true);

    try {
        checked.reset(sos::throws, false);
        std::terminate();
    }
    catch (sos::failed_check const&) {}
}


int main() {
    test_checked_constructible();
    test_checked_nothrow_constructible();

    test_checked_reset();
    test_checked_unenforced();

    test_checked_construction_fail();
    test_make_checked_fail();
    test_checked_reset_fail();
}
