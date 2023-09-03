#include <map>
#include <list>
#include <regex>
#include <string>
#include <vector>
#include <initializer_list>

#include <sos/concepts/empty_testable.hpp>

#include "container.hpp"
#include "empty_struct.hpp"


using sos::empty_testable;
using sos::nothrow_empty_testable;


static constexpr void test_empty_testable() noexcept {
    static_assert(    empty_testable<int[10]>);
    static_assert(    empty_testable<std::string>);
    static_assert(    empty_testable<std::vector<int>>);
    static_assert(    empty_testable<std::initializer_list<int>>);

    static_assert(not empty_testable<empty_struct>);
    static_assert(    empty_testable<sized_container<>>);
    static_assert(    empty_testable<emptiable_container<>>);
    static_assert(    empty_testable<nothrow_sized_container>);
    static_assert(    empty_testable<nothrow_emptiable_container>);
}

static constexpr void test_nothrow_empty_testable() noexcept {
    static_assert(    nothrow_empty_testable<std::cmatch>);
    static_assert(    nothrow_empty_testable<std::list<int>>);
    static_assert(    nothrow_empty_testable<std::map<int, int>>);

    static_assert(not nothrow_empty_testable<empty_struct>);
    static_assert(not nothrow_empty_testable<sized_container<>>);
    static_assert(not nothrow_empty_testable<emptiable_container<>>);
    static_assert(    nothrow_empty_testable<nothrow_sized_container>);
    static_assert(    nothrow_empty_testable<nothrow_emptiable_container>);
}


int main() {
    test_empty_testable();
    test_nothrow_empty_testable();
}
