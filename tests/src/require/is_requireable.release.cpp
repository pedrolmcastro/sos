#define NDEBUG 1 // Force release mode


#include <functional>

#include "sos/policy/policies.hpp"
#include "sos/require/is_requireable.hpp"


using sos::policies::aborts_t, sos::policies::asserts_t, sos::policies::unenforced_t, sos::is_trivially_requireable;


static consteval void is_trivially_requireable_succeeds_with_asserts_in_release() noexcept {
    static_assert(is_trivially_requireable<asserts_t, std::logical_not<>, bool>);
}

static consteval void is_trivially_requireable_succeeds_with_unenforced_in_release() noexcept {
    static_assert(is_trivially_requireable<unenforced_t, std::logical_not<>, bool>);
}


static consteval void is_trivially_requireable_fails_with_non_trivial_policy() noexcept {
    static_assert(not is_trivially_requireable<aborts_t, std::logical_not<>, bool>);
}


int main() {
    is_trivially_requireable_succeeds_with_asserts_in_release();
    is_trivially_requireable_succeeds_with_unenforced_in_release();

    is_trivially_requireable_fails_with_non_trivial_policy();
}
