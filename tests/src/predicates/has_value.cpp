#include <any>
#include <cassert>
#include <optional>

#include <sos/predicates/has_value.hpp>

#include "container.hpp"


using sos::has_value;


static void test_has_value() {
    assert(not has_value(std::any{}));
    assert(    has_value(std::make_any<int>()));

    static_assert(not has_value(std::optional<int>{}));
    static_assert(    has_value(std::make_optional<int>()));

    static_assert(    has_value(valued_container{true}));
    static_assert(not has_value(valued_container{false}));
    static_assert(    has_value(nothrow_valued_container{true}));
    static_assert(not has_value(nothrow_valued_container{false}));
}


int main() {
    test_has_value();
}
