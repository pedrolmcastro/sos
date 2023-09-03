#include <memory>
#include <string>
#include <cstddef>
#include <optional>

#include <sos/concepts/oneway_equality_comparable_with_null.hpp>

#include "empty_struct.hpp"
#include "comparable_with.hpp"


using sos::oneway_equality_comparable_with_nullptr;
using sos::oneway_equality_comparable_with_nullopt;
using sos::nothrow_oneway_equality_comparable_with_nullptr;
using sos::nothrow_oneway_equality_comparable_with_nullopt;


static constexpr void test_oneway_equality_comparable_with_nullptr() noexcept {
    static_assert(    oneway_equality_comparable_with_nullptr<void*>);
    static_assert(    oneway_equality_comparable_with_nullptr<std::nullptr_t>);
    static_assert(    oneway_equality_comparable_with_nullptr<std::unique_ptr<int>>);

    static_assert(not oneway_equality_comparable_with_nullptr<empty_struct>);
    static_assert(    oneway_equality_comparable_with_nullptr<comparable_with<std::nullptr_t>>);
    static_assert(    oneway_equality_comparable_with_nullptr<nothrow_comparable_with<std::nullptr_t>>);
}

static constexpr void test_nothrow_oneway_equality_comparable_with_nullptr() noexcept {
    static_assert(    nothrow_oneway_equality_comparable_with_nullptr<char*>);
    static_assert(    nothrow_oneway_equality_comparable_with_nullptr<std::nullptr_t>);
    static_assert(    nothrow_oneway_equality_comparable_with_nullptr<std::shared_ptr<int>>);

    static_assert(not nothrow_oneway_equality_comparable_with_nullptr<empty_struct>);
    static_assert(not nothrow_oneway_equality_comparable_with_nullptr<comparable_with<std::nullptr_t>>);
    static_assert(    nothrow_oneway_equality_comparable_with_nullptr<nothrow_comparable_with<std::nullptr_t>>);
}


static constexpr void test_oneway_equality_comparable_with_nullopt() noexcept {
    static_assert(    oneway_equality_comparable_with_nullopt<std::optional<int>>);

    static_assert(not oneway_equality_comparable_with_nullopt<empty_struct>);
    static_assert(    oneway_equality_comparable_with_nullopt<comparable_with<std::nullopt_t>>);
    static_assert(    oneway_equality_comparable_with_nullopt<nothrow_comparable_with<std::nullopt_t>>);
}

static constexpr void test_nothrow_oneway_equality_comparable_with_nullopt() noexcept {
    static_assert(    nothrow_oneway_equality_comparable_with_nullopt<std::optional<std::string>>);

    static_assert(not nothrow_oneway_equality_comparable_with_nullopt<empty_struct>);
    static_assert(not nothrow_oneway_equality_comparable_with_nullopt<comparable_with<std::nullopt_t>>);
    static_assert(    nothrow_oneway_equality_comparable_with_nullopt<nothrow_comparable_with<std::nullopt_t>>);
}


int main() {
    test_oneway_equality_comparable_with_nullptr();
    test_nothrow_oneway_equality_comparable_with_nullptr();

    test_oneway_equality_comparable_with_nullopt();
    test_nothrow_oneway_equality_comparable_with_nullopt();
}
