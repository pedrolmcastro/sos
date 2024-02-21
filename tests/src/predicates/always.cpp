#include "sos/predicates/always.hpp"


using
    sos::predicates::always_true,
    sos::predicates::always_false,
    sos::predicates::always_true_t,
    sos::predicates::always_false_t
;


static consteval void always_true_casts_to_true() noexcept {
    static_assert(static_cast<bool>(always_true));
}

static consteval void always_true_value_is_true() noexcept {
    static_assert(always_true_t::value);
}

static consteval void always_true_succeeds_with_true() noexcept {
    static_assert(always_true(true));
}

static consteval void always_true_succeeds_with_false() noexcept {
    static_assert(always_true(false));
}

static consteval void always_true_succeeds_without_args() noexcept {
    static_assert(always_true());
}

static consteval void always_true_succeeds_with_lvalue_ref() noexcept {
    constexpr int ref{};
    static_assert(always_true(ref));
}

static consteval void always_true_succeeds_with_multiple_args() noexcept {
    static_assert(always_true(0U, 0.0, '\0', nullptr));
}


static consteval void always_false_casts_to_false() noexcept {
    static_assert(not static_cast<bool>(always_false));
}

static consteval void always_false_value_is_false() noexcept {
    static_assert(not always_false_t::value);
}

static consteval void always_false_fails_with_true() noexcept {
    static_assert(not always_false(true));
}

static consteval void always_false_fails_with_false() noexcept {
    static_assert(not always_false(false));
}

static consteval void always_false_fails_without_args() noexcept {
    static_assert(not always_false());
}

static consteval void always_false_fails_with_lvalue_ref() noexcept {
    constexpr int ref{};
    static_assert(not always_false(ref));
}

static consteval void always_false_fails_with_multiple_args() noexcept {
    static_assert(not always_false(-1, 1.F, 'c', "char[]"));
}


int main() {
    always_true_casts_to_true();
    always_true_value_is_true();
    always_true_succeeds_with_true();
    always_true_succeeds_with_false();
    always_true_succeeds_without_args();
    always_true_succeeds_with_lvalue_ref();
    always_true_succeeds_with_multiple_args();

    always_false_casts_to_false();
    always_false_value_is_false();
    always_false_fails_with_true();
    always_false_fails_with_false();
    always_false_fails_without_args();
    always_false_fails_with_lvalue_ref();
    always_false_fails_with_multiple_args();
}
