#include <memory>
#include <cassert>
#include <cstddef>
#include <optional>

#include <sos/predicates/is_not_equal_to_null.hpp>

#include "comparable_with.hpp"


using sos::is_not_equal_to_nullptr;
using sos::is_not_equal_to_nullopt;


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

static constexpr void test_is_not_equal_to_nullopt() noexcept {
    static_assert(not is_not_equal_to_nullopt(std::optional<int>{}));
    static_assert(    is_not_equal_to_nullopt(std::make_optional<int>()));

    static_assert(not is_not_equal_to_nullopt(comparable_with<std::nullopt_t>{true}));
    static_assert(    is_not_equal_to_nullopt(comparable_with<std::nullopt_t>{false}));
    static_assert(not is_not_equal_to_nullopt(nothrow_comparable_with<std::nullopt_t>{true}));
    static_assert(    is_not_equal_to_nullopt(nothrow_comparable_with<std::nullopt_t>{false}));
}


int main() {
    test_is_not_equal_to_nullptr();
    test_is_not_equal_to_nullopt();
}
