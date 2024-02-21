#include <memory>
#include <cassert>
#include <functional>

#include "sos/predicates/is_null.hpp"


using sos::predicates::is_null, sos::predicates::is_not_null;


static consteval void is_null_succeeds_with_null() noexcept {
    static_assert(        is_null(nullptr));
    static_assert(not is_not_null(nullptr));

    static_assert(        is_null(static_cast<void const *>(NULL)));
    static_assert(not is_not_null(static_cast<void const *>(NULL)));
}

static void is_null_succeeds_with_empty_smart_ptr() noexcept {
    std::unique_ptr<int> unique{};
    assert(        is_null(unique));
    assert(not is_not_null(unique));

    std::shared_ptr<int> shared{};
    assert(        is_null(shared));
    assert(not is_not_null(shared));
}

static consteval void is_null_succeeds_with_null_function_ptr() noexcept {
    constexpr void (*function_ptr)(){};

    static_assert(       is_null(function_ptr));
    static_assert(not is_not_null(function_ptr));
}


static consteval void is_null_fails_with_populated_ptr() noexcept {
    constexpr int pointee{};

    static_assert(not is_null(&pointee));
    static_assert(is_not_null(&pointee));
}

static void is_null_fails_with_populated_smart_ptr() noexcept {
    auto const unique = std::make_unique<int>();
    assert(not is_null(unique));
    assert(is_not_null(unique));

    auto const shared = std::make_shared<int>();
    assert(not is_null(shared));
    assert(is_not_null(shared));
}

static consteval void is_null_fails_with_populated_function_ptr() noexcept {
    void function();

    static_assert(not is_null(&function));
    static_assert(is_not_null(&function));
}


int main() {
    is_null_succeeds_with_null();
    is_null_succeeds_with_empty_smart_ptr();
    is_null_succeeds_with_null_function_ptr();

    is_null_fails_with_populated_ptr();
    is_null_fails_with_populated_smart_ptr();
    is_null_fails_with_populated_function_ptr();
}
