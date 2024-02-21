#include <variant>

#include "sos/policy/policies.hpp"
#include "sos/policy/dynamic_policy.hpp"


using namespace sos::policies;

using sos::policy::dynamic_policy;


static consteval void dynamic_policy_accepts_static_policy_variant() noexcept {
    static_assert(dynamic_policy<std::variant<throws_with_bad_require_t>>);
    static_assert(dynamic_policy<std::variant<terminates_t, unenforced_t>>);
    static_assert(dynamic_policy<std::variant<aborts_t, aborts_t, asserts_t>>);
}


static consteval void dynamic_policy_rejects_empty_variant() noexcept {
    static_assert(not dynamic_policy<std::variant<>>);
}

static consteval void dynamic_policy_rejects_static_policy() noexcept {
    static_assert(not dynamic_policy<terminates_t>);
}

static consteval void dynamic_policy_rejects_non_policy_variant() noexcept {
    static_assert(not dynamic_policy<std::variant<int>>);
    static_assert(not dynamic_policy<std::variant<int, exits_with_success_t>>);
    static_assert(not dynamic_policy<std::variant<exits_with_success_t, int>>);
}

static consteval void dynamic_policy_rejects_nested_static_policy_variant() noexcept {
    static_assert(not dynamic_policy<std::variant<aborts_t, std::variant<asserts_t>>>);
}


int main() {
    dynamic_policy_accepts_static_policy_variant();

    dynamic_policy_rejects_empty_variant();
    dynamic_policy_rejects_static_policy();
    dynamic_policy_rejects_non_policy_variant();
    dynamic_policy_rejects_nested_static_policy_variant();
}
