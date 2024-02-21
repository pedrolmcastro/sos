#include <exception>
#include <functional>

#include "sos/policy/policies.hpp"
#include "sos/exceptions/bad_require.hpp"
#include "sos/constraints/constrained.hpp"


using sos::exceptions::bad_require, sos::constraints::constrained, sos::policies::throws_with_bad_require;


static void constrained_construction_fails_if_predicate_fails() noexcept {
    try {
        constrained<std::identity, bool>{throws_with_bad_require, false};
    }
    catch (bad_require const&) {
        return;
    }

    std::terminate(); // ✕ Expected exception was not thrown
}

static consteval void constrained_construction_succeeds_if_predicate_succeeds() noexcept {
    constexpr constrained<std::identity, bool> wrapped{throws_with_bad_require, true};
    static_assert(wrapped.value() == true);
}


int main() {
    constrained_construction_fails_if_predicate_fails();
    constrained_construction_succeeds_if_predicate_succeeds();
}
