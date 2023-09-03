#include <string>
#include <vector>
#include <cassert>

#include <sos/predicates/is_empty.hpp>

#include "container.hpp"


using sos::is_empty;


static void test_is_empty() {
    assert(    is_empty(std::string{}));
    assert(not is_empty(std::string{"string"}));

    assert(    is_empty(std::vector<int>{}));
    assert(not is_empty(std::vector{1, 2, 3}));

    static_assert(    is_empty(sized_container{0}));
    static_assert(not is_empty(nothrow_sized_container{1}));

    static_assert(    is_empty(emptiable_container{true}));
    static_assert(not is_empty(nothrow_emptiable_container{false}));
}


int main() {
    test_is_empty();
}
