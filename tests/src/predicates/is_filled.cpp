#include <array>
#include <cassert>
#include <forward_list>
#include <unordered_set>

#include <sos/predicates/is_filled.hpp>

#include "container.hpp"


using sos::is_filled;


static void test_is_filled() {
    assert(not is_filled(std::forward_list<int>{}));
    assert(    is_filled(std::forward_list<int>{1}));

    assert(not is_filled(std::unordered_set<int>{}));
    assert(    is_filled(std::unordered_set<int>{1}));

    static_assert(not is_filled(std::array<int, 0>{}));
    static_assert(    is_filled(std::array<int, 10>{}));

    static_assert(not is_filled(sized_container{0}));
    static_assert(    is_filled(nothrow_sized_container{1}));

    static_assert(not is_filled(emptiable_container{true}));
    static_assert(    is_filled(nothrow_emptiable_container{false}));
}


int main() {
    test_is_filled();
}
