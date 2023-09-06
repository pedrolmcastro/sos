#include <sos/check/policy.hpp>

#include "empty_struct.hpp"


static constexpr void test_policy() noexcept {
    static_assert(not sos::policy<int>);
    static_assert(not sos::policy<empty_struct>);

    static_assert(    sos::policy<sos::throws_t>);
    static_assert(    sos::policy<sos::asserts_t>);
    static_assert(    sos::policy<sos::terminates_t>);
    static_assert(    sos::policy<sos::unenforced_t>);

    static_assert(not sos::policy<sos::throws_t&>);
    static_assert(not sos::policy<sos::asserts_t&&>);
    static_assert(not sos::policy<sos::terminates_t const>);
    static_assert(not sos::policy<sos::unenforced_t volatile>);
}


int main() {
    test_policy();
}
