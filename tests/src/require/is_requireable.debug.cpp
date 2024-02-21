#undef NDEBUG // Force debug mode


#include <variant>
#include <functional>

#include "sos/policy/policies.hpp"
#include "sos/require/is_requireable.hpp"


using
    sos::is_requireable,
    sos::policies::aborts_t,
    sos::policies::asserts_t,
    sos::is_nothrow_requireable,
    sos::policies::unenforced_t,
    sos::is_trivially_requireable,
    sos::policies::throws_with_bad_require_t
;


static consteval void is_requireable_succeeds_with_static_policy() noexcept {
    static_assert(is_requireable<aborts_t, std::logical_not<>, bool>);
}

static consteval void is_requireable_succeeds_with_dynamic_policy() noexcept {
    static_assert(is_requireable<std::variant<asserts_t, unenforced_t>, std::logical_not<>, bool>);
}


static consteval void is_requireable_fails_with_invalid_policy() noexcept {
    static_assert(not is_requireable<int, std::logical_not<>, int>);
}

static consteval void is_requireable_fails_with_invalid_predicate() noexcept {
    static_assert(not is_requireable<unenforced_t, std::monostate, bool>);
}

static consteval void is_requireable_fails_with_invalid_args_for_predicate() noexcept {
    static_assert(not is_requireable<unenforced_t, std::logical_not<>, std::monostate>);
}


static consteval void is_trivially_requireable_succeeds_with_unenforced_in_debug() noexcept {
    static_assert(is_trivially_requireable<unenforced_t, std::logical_not<>, bool>);
}


static consteval void is_trivially_requireable_fails_with_dynamic_policy() noexcept {
    static_assert(not is_trivially_requireable<std::variant<asserts_t, unenforced_t>, std::logical_not<>, bool>);
}

static consteval void is_trivially_requireable_fails_with_invalid_policy() noexcept {
    static_assert(not is_trivially_requireable<int, std::logical_not<>, int>);
}

static consteval void is_trivially_requireable_fails_with_asserts_in_debug() noexcept {
    static_assert(not is_trivially_requireable<asserts_t, std::logical_not<>, bool>);
}

static consteval void is_trivially_requireable_fails_with_invalid_predicate() noexcept {
    static_assert(not is_trivially_requireable<unenforced_t, std::monostate, bool>);
}

static consteval void is_trivially_requireable_fails_with_non_trivial_policy() noexcept {
    static_assert(not is_trivially_requireable<aborts_t, std::logical_not<>, bool>);
}

static consteval void is_trivially_requireable_fails_with_invalid_args_for_predicate() noexcept {
    static_assert(not is_trivially_requireable<unenforced_t, std::logical_not<>, std::monostate>);
}


static consteval void is_nothrow_requireable_succeeds_with_trivial_policy() noexcept {
    struct throwing_convertible_to_bool_t {
        operator bool() const noexcept(false);
    };

    static_assert(is_nothrow_requireable<unenforced_t, std::logical_not<>, throwing_convertible_to_bool_t>);
}

static consteval void is_nothrow_requireable_succeeds_with_nothrow_predicate() noexcept {
    static_assert(is_nothrow_requireable<aborts_t, std::logical_not<>, bool>);
}


static consteval void is_nothrow_requireable_fails_with_throws() noexcept {
    static_assert(not is_nothrow_requireable<throws_with_bad_require_t, std::logical_not<>, bool>);
}

static consteval void is_nothrow_requireable_fails_with_dynamic_policy() noexcept {
    static_assert(not is_nothrow_requireable<std::variant<asserts_t, unenforced_t>, std::logical_not<>, bool>);
}

static consteval void is_nothrow_requireable_fails_with_invalid_policy() noexcept {
    static_assert(not is_nothrow_requireable<int, std::logical_not<>, int>);
}

static consteval void is_nothrow_requireable_fails_with_invalid_predicate() noexcept {
    static_assert(not is_nothrow_requireable<unenforced_t, std::monostate, bool>);
}

static consteval void is_nothrow_requireable_fails_with_throwing_predicate() noexcept {
    struct throwing_convertible_to_bool_t {
        operator bool() noexcept(false);
    };

    static_assert(not is_nothrow_requireable<aborts_t, std::logical_not<>, throwing_convertible_to_bool_t>);
}

static consteval void is_nothrow_requireable_fails_with_invalid_args_for_predicate() noexcept {
    static_assert(not is_nothrow_requireable<unenforced_t, std::logical_not<>, std::monostate>);
}


int main() {
    is_requireable_succeeds_with_static_policy();
    is_requireable_succeeds_with_dynamic_policy();

    is_requireable_fails_with_invalid_policy();
    is_requireable_fails_with_invalid_predicate();
    is_requireable_fails_with_invalid_args_for_predicate();

    is_trivially_requireable_succeeds_with_unenforced_in_debug();

    is_trivially_requireable_fails_with_dynamic_policy();
    is_trivially_requireable_fails_with_invalid_policy();
    is_trivially_requireable_fails_with_asserts_in_debug();
    is_trivially_requireable_fails_with_invalid_predicate();
    is_trivially_requireable_fails_with_non_trivial_policy();
    is_trivially_requireable_fails_with_invalid_args_for_predicate();

    is_nothrow_requireable_succeeds_with_trivial_policy();
    is_nothrow_requireable_succeeds_with_nothrow_predicate();

    is_nothrow_requireable_fails_with_throws();
    is_nothrow_requireable_fails_with_dynamic_policy();
    is_nothrow_requireable_fails_with_invalid_policy();
    is_nothrow_requireable_fails_with_invalid_predicate();
    is_nothrow_requireable_fails_with_throwing_predicate();
    is_nothrow_requireable_fails_with_invalid_args_for_predicate();
}
