#include <map>
#include <list>
#include <regex>
#include <string>
#include <vector>
#include <cassert>
#include <initializer_list>

#include <sos/predicates/is_empty.hpp>

#include "container.hpp"
#include "empty_struct.hpp"


static constexpr void test_empty_testable() noexcept {
    static_assert(    sos::empty_testable<int[10]>);
    static_assert(    sos::empty_testable<std::string>);
    static_assert(    sos::empty_testable<std::vector<int>>);
    static_assert(    sos::empty_testable<std::initializer_list<int>>);

    static_assert(not sos::empty_testable<empty_struct>);
    static_assert(    sos::empty_testable<sized_container<>>);
    static_assert(    sos::empty_testable<emptiable_container<>>);
    static_assert(    sos::empty_testable<nothrow_sized_container>);
    static_assert(    sos::empty_testable<nothrow_emptiable_container>);
}

static constexpr void test_nothrow_empty_testable() noexcept {
    static_assert(    sos::nothrow_empty_testable<std::cmatch>);
    static_assert(    sos::nothrow_empty_testable<std::list<int>>);
    static_assert(    sos::nothrow_empty_testable<std::map<int, int>>);

    static_assert(not sos::nothrow_empty_testable<empty_struct>);
    static_assert(not sos::nothrow_empty_testable<sized_container<>>);
    static_assert(not sos::nothrow_empty_testable<emptiable_container<>>);
    static_assert(    sos::nothrow_empty_testable<nothrow_sized_container>);
    static_assert(    sos::nothrow_empty_testable<nothrow_emptiable_container>);
}

static void test_is_empty() {
    // REVIEW: use static_assert if std::string becomes constexpr
    assert(    sos::is_empty(std::string{}));
    assert(not sos::is_empty(std::string{"string"}));

    // REVIEW: use static_assert if std::vector becomes constexpr
    assert(    sos::is_empty(std::vector<int>{}));
    assert(not sos::is_empty(std::vector{1, 2, 3}));

    static_assert(    sos::is_empty(sized_container{0}));
    static_assert(not sos::is_empty(nothrow_sized_container{1}));

    static_assert(    sos::is_empty(emptiable_container{true}));
    static_assert(not sos::is_empty(nothrow_emptiable_container{false}));
}


int main() {
    test_empty_testable();
    test_nothrow_empty_testable();
    test_is_empty();
}
