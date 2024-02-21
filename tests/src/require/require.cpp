#include <exception>
#include <functional>

#include "sos/require/require.hpp"
#include "sos/policy/policies.hpp"
#include "sos/exceptions/bad_require.hpp"


using sos::require, sos::policies::unenforced, sos::exceptions::bad_require, sos::policies::throws_with_bad_require;


static consteval void require_succeeds_with_trivial_policy() noexcept {
    require(unenforced, std::identity{}, false);
}

static void require_fails_with_predicate_result_false() noexcept {
    try {
        require(throws_with_bad_require, std::identity{}, false);
    }
    catch (bad_require const&) {
        return;
    }

    std::terminate(); // ✕ Expected exception was not thrown
}


int main() {
    require_succeeds_with_trivial_policy();
    require_fails_with_predicate_result_false();
}
