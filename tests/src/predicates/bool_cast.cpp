#include <memory>
#include <cassert>
#include <optional>
#include <functional>

#include "sos/predicates/bool_cast.hpp"


using sos::predicates::bool_cast, sos::predicates::not_bool_cast;


static consteval void bool_cast_succeeds_with_true() noexcept {
    static_assert(        bool_cast(true));
    static_assert(not not_bool_cast(true));
}

static consteval void bool_cast_succeeds_with_populated_ptr() noexcept {
    constexpr int variable{};

    static_assert(        bool_cast(&variable));
    static_assert(not not_bool_cast(&variable));
}

static consteval void bool_cast_succeeds_with_positive_number() noexcept {
    static_assert(        bool_cast(1));
    static_assert(not not_bool_cast(1));

    static_assert(        bool_cast(2UL));
    static_assert(not not_bool_cast(2UL));

    static_assert(        bool_cast(3.4E5));
    static_assert(not not_bool_cast(3.4E5));
}

static consteval void bool_cast_succeeds_with_negative_number() noexcept {
    static_assert(        bool_cast(-1LL));
    static_assert(not not_bool_cast(-1LL));

    static_assert(        bool_cast(-2.F));
    static_assert(not not_bool_cast(-2.F));
}

static consteval void bool_cast_succeeds_with_populated_optional() noexcept {
    constexpr std::optional optional{0};

    static_assert(        bool_cast(optional));
    static_assert(not not_bool_cast(optional));
}

static consteval void bool_cast_succeeds_with_populated_function_ptr() noexcept {
    constexpr auto lambda = []{};

    static_assert(        bool_cast(+lambda));
    static_assert(not not_bool_cast(+lambda));
}


static consteval void bool_cast_fails_with_null() noexcept {
    static_assert(not bool_cast(NULL));
    static_assert(not_bool_cast(NULL));

    static_assert(not bool_cast(nullptr));
    static_assert(not_bool_cast(nullptr));
}

static consteval void bool_cast_fails_with_zero() noexcept {
    static_assert(not bool_cast(0));
    static_assert(not_bool_cast(0));

    static_assert(not bool_cast(0U));
    static_assert(not_bool_cast(0U));

    static_assert(not bool_cast(0L));
    static_assert(not_bool_cast(0L));

    static_assert(not bool_cast(0LL));
    static_assert(not_bool_cast(0LL));

    static_assert(not bool_cast(0.));
    static_assert(not_bool_cast(0.));

    static_assert(not bool_cast(0.F));
    static_assert(not_bool_cast(0.F));

    static_assert(not bool_cast(0.L));
    static_assert(not_bool_cast(0.L));
}

static consteval void bool_cast_fails_with_false() noexcept {
    static_assert(not bool_cast(false));
    static_assert(not_bool_cast(false));
}

static consteval void bool_cast_fails_with_empty_optional() noexcept {
    constexpr std::optional<int> optional{};

    static_assert(not bool_cast(optional));
    static_assert(not_bool_cast(optional));
}

static void bool_cast_fails_with_empty_smart_ptr() noexcept {
    std::unique_ptr<int> const unique{};
    assert(not bool_cast(unique));
    assert(not_bool_cast(unique));

    std::shared_ptr<int> const shared{};
    assert(not bool_cast(shared));
    assert(not_bool_cast(shared));
}

static void bool_cast_fails_with_empty_std_function() noexcept {
    std::function<void()> const function{};

    assert(not bool_cast(function));
    assert(not_bool_cast(function));
}


int main() {
    bool_cast_succeeds_with_true();
    bool_cast_succeeds_with_populated_ptr();
    bool_cast_succeeds_with_positive_number();
    bool_cast_succeeds_with_negative_number();
    bool_cast_succeeds_with_populated_optional();
    bool_cast_succeeds_with_populated_function_ptr();

    bool_cast_fails_with_null();
    bool_cast_fails_with_zero();
    bool_cast_fails_with_false();
    bool_cast_fails_with_empty_optional();
    bool_cast_fails_with_empty_smart_ptr();
    bool_cast_fails_with_empty_std_function();
}
