#include <array>
#include <cassert>
#include <forward_list>
#include <unordered_set>

#include <sos/predicates/is_filled.hpp>

#include "container.hpp"


static void test_is_filled() {
    // REVIEW: use static_assert if std::forward_list becomes constexpr
    assert(not sos::is_filled(std::forward_list<int>{}));
    assert(    sos::is_filled(std::forward_list<int>{1}));

    // REVIEW: use static_assert if std::unordered_set becomes constexpr
    assert(not sos::is_filled(std::unordered_set<int>{}));
    assert(    sos::is_filled(std::unordered_set<int>{1}));

    static_assert(not sos::is_filled(std::array<int, 0>{}));
    static_assert(    sos::is_filled(std::array<int, 10>{}));

    static_assert(not sos::is_filled(sized_container{0}));
    static_assert(    sos::is_filled(nothrow_sized_container{1}));

    static_assert(not sos::is_filled(emptiable_container{true}));
    static_assert(    sos::is_filled(nothrow_emptiable_container{false}));
}


int main() {
    test_is_filled();
}
