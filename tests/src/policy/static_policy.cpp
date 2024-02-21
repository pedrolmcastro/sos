#include <variant>
#include <exception>

#include "sos/policy/static_policy.hpp"


using namespace sos::policies;

using sos::policy::static_policy;


static consteval void static_policy_accepts_static_policy() noexcept {
    static_assert(static_policy<aborts_t>);
    static_assert(static_policy<asserts_t>);
    static_assert(static_policy<terminates_t>);
    static_assert(static_policy<unenforced_t>);
    static_assert(static_policy<exits_with_success_t>);
    static_assert(static_policy<exits_with_failure_t>);
    static_assert(static_policy<throws_with_bad_require_t>);
    static_assert(static_policy<quick_exits_with_success_t>);
    static_assert(static_policy<quick_exits_with_failure_t>);
}

static consteval void static_policy_accepts_custom_code_exits_with() noexcept {
    static_assert(static_policy<exits_with_t<2>>);
}

static consteval void static_policy_accepts_custom_code_quick_exits_with() noexcept {
    static_assert(static_policy<quick_exits_with_t<3>>);
}

static consteval void static_policy_accepts_custom_exception_throws_with() noexcept {
    static_assert(static_policy<throws_with_t<std::exception>>);
}


static consteval void static_policy_rejects_non_policy() noexcept {
    static_assert(not static_policy<int>);
    static_assert(not static_policy<int*>);
}

static consteval void static_policy_rejects_policy_ptr() noexcept {
    static_assert(not static_policy<aborts_t*>);
}

static consteval void static_policy_rejects_policy_ref() noexcept {
    static_assert(not static_policy<aborts_t&>);
    static_assert(not static_policy<aborts_t&&>);
}

static consteval void static_policy_rejects_dynamic_policy() noexcept {
    static_assert(not static_policy<std::variant<aborts_t, asserts_t>>);
}

static consteval void static_policy_rejects_cv_qualified_policy() noexcept {
    static_assert(not static_policy<aborts_t const>);
    static_assert(not static_policy<aborts_t volatile>);
}


int main() {
    static_policy_accepts_static_policy();
    static_policy_accepts_custom_code_exits_with();
    static_policy_accepts_custom_code_quick_exits_with();
    static_policy_accepts_custom_exception_throws_with();

    static_policy_rejects_non_policy();
    static_policy_rejects_policy_ptr();
    static_policy_rejects_policy_ref();
    static_policy_rejects_dynamic_policy();
    static_policy_rejects_cv_qualified_policy();
}
