#include <cassert>
#include <optional>
#include <exception>

#include <sos/check/check.hpp>
#include <sos/check/policy.hpp>
#include <sos/predicates/is_null.hpp>
#include <sos/predicates/is_empty.hpp>
#include <sos/predicates/is_filled.hpp>

#include "container.hpp"


static void test_check() {
    sos::check(sos::throws, true);

    try {
        sos::check(sos::throws, false);
        std::terminate();
    }
    catch (sos::failed_check const&) {}


    sos::check(sos::asserts, nullptr, sos::is_nullptr);
    sos::check(sos::asserts, std::optional<int>{}, sos::is_nullopt);

    sos::check(sos::terminates, sized_container{0}, sos::is_empty);
    sos::check(sos::terminates, sized_container{1}, sos::is_filled);

    sos::check(sos::unenforced, 0, sos::bool_cast);
    sos::check(sos::unenforced, 1, sos::bool_cast);
}


int main() {
    test_check();
}
