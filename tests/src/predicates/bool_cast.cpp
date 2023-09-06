#include <bitset>
#include <memory>
#include <string>
#include <cstddef>
#include <optional>
#include <functional>

#include <sos/predicates/bool_cast.hpp>

#include "testable.hpp"
#include "empty_struct.hpp"


static constexpr void test_bool_castable() noexcept {
    static_assert(    sos::bool_castable<bool>);
    static_assert(    sos::bool_castable<void*>);
    static_assert(not sos::bool_castable<std::string>);
    static_assert(    sos::bool_castable<std::nullptr_t>);
    static_assert(not sos::bool_castable<std::weak_ptr<int>>);
    static_assert(    sos::bool_castable<std::unique_ptr<int>>);
    static_assert(    sos::bool_castable<std::bitset<10>::reference>);

    static_assert(not sos::bool_castable<empty_struct>);
    static_assert(    sos::bool_castable<explicit_testable>);
    static_assert(    sos::bool_castable<implicit_testable>);
    static_assert(    sos::bool_castable<nothrow_explicit_testable>);
    static_assert(    sos::bool_castable<nothrow_implicit_testable>);
}

static constexpr void test_nothrow_bool_castable() noexcept {
    static_assert(    sos::nothrow_bool_castable<int*>);
    static_assert(    sos::nothrow_bool_castable<bool>);
    static_assert(    sos::nothrow_bool_castable<unsigned>);
    static_assert(    sos::nothrow_bool_castable<std::optional<int>>);
    static_assert(    sos::nothrow_bool_castable<std::shared_ptr<int>>);
    static_assert(    sos::nothrow_bool_castable<std::function<void()>>);

    static_assert(not sos::nothrow_bool_castable<empty_struct>);
    static_assert(not sos::nothrow_bool_castable<explicit_testable>);
    static_assert(not sos::nothrow_bool_castable<implicit_testable>);
    static_assert(    sos::nothrow_bool_castable<nothrow_explicit_testable>);
    static_assert(    sos::nothrow_bool_castable<nothrow_implicit_testable>);
}

static constexpr void test_bool_cast() noexcept {
    static_assert(    sos::bool_cast(true));
    static_assert(not sos::bool_cast(false));

    static_assert(    sos::bool_cast(-1));
    static_assert(not sos::bool_cast(0U));
    static_assert(    sos::bool_cast(1L));

    static_assert(not sos::bool_cast(NULL));
    static_assert(not sos::bool_cast(nullptr));

    static_assert(not sos::bool_cast(std::optional<int>{}));
    static_assert(    sos::bool_cast(std::make_optional<int>()));

    static_assert(    sos::bool_cast(explicit_testable{true}));
    static_assert(not sos::bool_cast(implicit_testable{false}));
    static_assert(    sos::bool_cast(nothrow_explicit_testable{true}));
    static_assert(not sos::bool_cast(nothrow_implicit_testable{false}));
}


int main() {
    test_bool_castable();
    test_nothrow_bool_castable();
    test_bool_cast();
}
