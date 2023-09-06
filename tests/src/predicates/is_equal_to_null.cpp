#include <memory>
#include <cassert>
#include <cstddef>
#include <optional>

#include <sos/predicates/is_equal_to_null.hpp>

#include "empty_struct.hpp"
#include "comparable_with.hpp"


static constexpr void test_oneway_equality_comparable_with_nullptr() noexcept {
    static_assert(    sos::oneway_equality_comparable_with_nullptr<void*>);
    static_assert(    sos::oneway_equality_comparable_with_nullptr<std::nullptr_t>);
    static_assert(    sos::oneway_equality_comparable_with_nullptr<std::unique_ptr<int>>);

    static_assert(not sos::oneway_equality_comparable_with_nullptr<empty_struct>);
    static_assert(    sos::oneway_equality_comparable_with_nullptr<comparable_with<std::nullptr_t>>);
    static_assert(    sos::oneway_equality_comparable_with_nullptr<nothrow_comparable_with<std::nullptr_t>>);
}

static constexpr void test_nothrow_oneway_equality_comparable_with_nullptr() noexcept {
    static_assert(    sos::nothrow_oneway_equality_comparable_with_nullptr<char*>);
    static_assert(    sos::nothrow_oneway_equality_comparable_with_nullptr<std::nullptr_t>);
    static_assert(    sos::nothrow_oneway_equality_comparable_with_nullptr<std::shared_ptr<int>>);

    static_assert(not sos::nothrow_oneway_equality_comparable_with_nullptr<empty_struct>);
    static_assert(not sos::nothrow_oneway_equality_comparable_with_nullptr<comparable_with<std::nullptr_t>>);
    static_assert(    sos::nothrow_oneway_equality_comparable_with_nullptr<nothrow_comparable_with<std::nullptr_t>>);
}

static void test_is_equal_to_nullptr() {
    // REVIEW: use static_assert if std::unique_ptr becomes constexpr
    assert(    sos::is_equal_to_nullptr(std::unique_ptr<int>{}));
    assert(not sos::is_equal_to_nullptr(std::make_unique<int>()));

    static_assert(    sos::is_equal_to_nullptr(nullptr));
    static_assert(    sos::is_equal_to_nullptr(static_cast<void*>(NULL)));

    static_assert(    sos::is_equal_to_nullptr(comparable_with<std::nullptr_t>{true}));
    static_assert(not sos::is_equal_to_nullptr(comparable_with<std::nullptr_t>{false}));
    static_assert(    sos::is_equal_to_nullptr(nothrow_comparable_with<std::nullptr_t>{true}));
    static_assert(not sos::is_equal_to_nullptr(nothrow_comparable_with<std::nullptr_t>{false}));
}


static constexpr void test_oneway_equality_comparable_with_nullopt() noexcept {
    static_assert(    sos::oneway_equality_comparable_with_nullopt<std::optional<int>>);

    static_assert(not sos::oneway_equality_comparable_with_nullopt<empty_struct>);
    static_assert(    sos::oneway_equality_comparable_with_nullopt<comparable_with<std::nullopt_t>>);
    static_assert(    sos::oneway_equality_comparable_with_nullopt<nothrow_comparable_with<std::nullopt_t>>);
}

static constexpr void test_nothrow_oneway_equality_comparable_with_nullopt() noexcept {
    static_assert(    sos::nothrow_oneway_equality_comparable_with_nullopt<std::optional<double>>);

    static_assert(not sos::nothrow_oneway_equality_comparable_with_nullopt<empty_struct>);
    static_assert(not sos::nothrow_oneway_equality_comparable_with_nullopt<comparable_with<std::nullopt_t>>);
    static_assert(    sos::nothrow_oneway_equality_comparable_with_nullopt<nothrow_comparable_with<std::nullopt_t>>);
}

static constexpr void test_is_equal_to_nullopt() noexcept {
    static_assert(    sos::is_equal_to_nullopt(std::optional<int>{}));
    static_assert(not sos::is_equal_to_nullopt(std::make_optional<int>()));

    static_assert(    sos::is_equal_to_nullopt(comparable_with<std::nullopt_t>{true}));
    static_assert(not sos::is_equal_to_nullopt(comparable_with<std::nullopt_t>{false}));
    static_assert(    sos::is_equal_to_nullopt(nothrow_comparable_with<std::nullopt_t>{true}));
    static_assert(not sos::is_equal_to_nullopt(nothrow_comparable_with<std::nullopt_t>{false}));
}


int main() {
    test_oneway_equality_comparable_with_nullptr();
    test_nothrow_oneway_equality_comparable_with_nullptr();
    test_is_equal_to_nullptr();

    test_oneway_equality_comparable_with_nullopt();
    test_nothrow_oneway_equality_comparable_with_nullopt();
    test_is_equal_to_nullopt();
}
