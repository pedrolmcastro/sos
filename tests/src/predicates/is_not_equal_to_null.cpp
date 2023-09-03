#include <memory>
#include <cassert>
#include <cstddef>
#include <optional>

#include <sos/predicates/is_not_equal_to_null.hpp>

#include "empty_struct.hpp"
#include "comparable_with.hpp"


using sos::is_not_equal_to_nullptr;
using sos::oneway_inequality_comparable_with_nullptr;
using sos::nothrow_oneway_inequality_comparable_with_nullptr;

using sos::is_not_equal_to_nullopt;
using sos::oneway_inequality_comparable_with_nullopt;
using sos::nothrow_oneway_inequality_comparable_with_nullopt;


static constexpr void test_oneway_inequality_comparable_with_nullptr() noexcept {
    static_assert(    oneway_inequality_comparable_with_nullptr<void*>);
    static_assert(    oneway_inequality_comparable_with_nullptr<std::nullptr_t>);
    static_assert(not oneway_inequality_comparable_with_nullptr<std::weak_ptr<int>>);

    static_assert(not oneway_inequality_comparable_with_nullptr<empty_struct>);
    static_assert(    oneway_inequality_comparable_with_nullptr<comparable_with<std::nullptr_t>>);
    static_assert(    oneway_inequality_comparable_with_nullptr<nothrow_comparable_with<std::nullptr_t>>);
}

static constexpr void test_nothrow_oneway_inequality_comparable_with_nullptr() noexcept {
    static_assert(    nothrow_oneway_inequality_comparable_with_nullptr<char*>);
    static_assert(    nothrow_oneway_inequality_comparable_with_nullptr<std::nullptr_t>);
    static_assert(    nothrow_oneway_inequality_comparable_with_nullptr<std::shared_ptr<int>>);

    static_assert(not nothrow_oneway_inequality_comparable_with_nullptr<empty_struct>);
    static_assert(not nothrow_oneway_inequality_comparable_with_nullptr<comparable_with<std::nullptr_t>>);
    static_assert(    nothrow_oneway_inequality_comparable_with_nullptr<nothrow_comparable_with<std::nullptr_t>>);
}

static void test_is_not_equal_to_nullptr() {
    assert(not is_not_equal_to_nullptr(std::shared_ptr<int>{}));
    assert(    is_not_equal_to_nullptr(std::make_shared<int>()));

    static_assert(not is_not_equal_to_nullptr(nullptr));
    static_assert(not is_not_equal_to_nullptr(static_cast<void*>(NULL)));

    static_assert(not is_not_equal_to_nullptr(comparable_with<std::nullptr_t>{true}));
    static_assert(    is_not_equal_to_nullptr(comparable_with<std::nullptr_t>{false}));
    static_assert(not is_not_equal_to_nullptr(nothrow_comparable_with<std::nullptr_t>{true}));
    static_assert(    is_not_equal_to_nullptr(nothrow_comparable_with<std::nullptr_t>{false}));
}


static constexpr void test_oneway_inequality_comparable_with_nullopt() noexcept {
    static_assert(    oneway_inequality_comparable_with_nullopt<std::optional<float>>);

    static_assert(not oneway_inequality_comparable_with_nullopt<empty_struct>);
    static_assert(    oneway_inequality_comparable_with_nullopt<comparable_with<std::nullopt_t>>);
    static_assert(    oneway_inequality_comparable_with_nullopt<nothrow_comparable_with<std::nullopt_t>>);
}

static constexpr void test_nothrow_oneway_inequality_comparable_with_nullopt() noexcept {
    static_assert(    nothrow_oneway_inequality_comparable_with_nullopt<std::optional<char>>);

    static_assert(not nothrow_oneway_inequality_comparable_with_nullopt<empty_struct>);
    static_assert(not nothrow_oneway_inequality_comparable_with_nullopt<comparable_with<std::nullopt_t>>);
    static_assert(    nothrow_oneway_inequality_comparable_with_nullopt<nothrow_comparable_with<std::nullopt_t>>);
}

static constexpr void test_is_not_equal_to_nullopt() noexcept {
    static_assert(not is_not_equal_to_nullopt(std::optional<int>{}));
    static_assert(    is_not_equal_to_nullopt(std::make_optional<int>()));

    static_assert(not is_not_equal_to_nullopt(comparable_with<std::nullopt_t>{true}));
    static_assert(    is_not_equal_to_nullopt(comparable_with<std::nullopt_t>{false}));
    static_assert(not is_not_equal_to_nullopt(nothrow_comparable_with<std::nullopt_t>{true}));
    static_assert(    is_not_equal_to_nullopt(nothrow_comparable_with<std::nullopt_t>{false}));
}


int main() {
    test_oneway_inequality_comparable_with_nullptr();
    test_nothrow_oneway_inequality_comparable_with_nullptr();
    test_is_not_equal_to_nullptr();

    test_oneway_inequality_comparable_with_nullopt();
    test_nothrow_oneway_inequality_comparable_with_nullopt();
    test_is_not_equal_to_nullopt();
}
