#include <string>
#include <functional>
#include <type_traits>

#include "sos/predicates/negation.hpp"
#include "sos/concepts/transparent.hpp"


using sos::predicates::not_fn, sos::predicates::negation, sos::concepts::transparent;


static consteval void negation_negates_invoke_result() noexcept {
    constexpr std::logical_not original{};
    constexpr negation<std::logical_not<>> wrapped{};

    static_assert(wrapped(true) == not original(true));
    static_assert(wrapped(false) == not original(false));
}

static consteval void negation_of_negation_keeps_invoke_result() noexcept {
    constexpr std::logical_not original{};
    constexpr negation<negation<std::logical_not<>>> wrapped{};

    static_assert(wrapped(true) == original(true));
    static_assert(wrapped(false) == original(false));
}


static consteval void negation_is_transparent_if_wrapped_is_transparent() noexcept {
    static_assert(transparent<negation<std::logical_not<>>>);
}

static consteval void negation_is_not_transparent_if_wrapped_is_not_transparent() noexcept {
    struct opaque_predicate_t {
        bool operator()();
    };

    static_assert(not transparent<negation<opaque_predicate_t>>);
}


static consteval void negation_is_invocable_if_wrapped_is_predicate() noexcept {
    struct predicate_only_for_bool_t {
        void operator()();                   // ✕ No return
        bool operator()(bool);               // ✓ Valid predicate
        std::string operator()(std::string); // ✕ Return is not boolean-testable
    };

    static_assert(not std::is_invocable_v<negation<predicate_only_for_bool_t>>);
    static_assert(    std::is_invocable_v<negation<predicate_only_for_bool_t>, bool>);
    static_assert(not std::is_invocable_v<negation<predicate_only_for_bool_t>, bool, bool>);
    static_assert(not std::is_invocable_v<negation<predicate_only_for_bool_t>, std::string>);
}

static consteval void negation_is_nothrow_invocable_if_wrapped_is_nothrow_predicate() noexcept {
    struct nothrow_only_on_move_predicate_t {
        bool operator()() const&;
        bool operator()() const&& noexcept;
    };

    static_assert(not std::is_nothrow_invocable_v<negation<nothrow_only_on_move_predicate_t>&>);
    static_assert(    std::is_nothrow_invocable_v<negation<nothrow_only_on_move_predicate_t>&&>);
}

static consteval void negation_is_move_only_invocable_if_wrapped_is_move_only_predicate() noexcept {
    struct move_only_predicate_t {
        bool operator()() const&&;
    };

    static_assert(not std::is_invocable_v<negation<move_only_predicate_t>&>);
    static_assert(    std::is_invocable_v<negation<move_only_predicate_t>&&>);
    static_assert(not std::is_invocable_v<negation<move_only_predicate_t> const&>);
    static_assert(    std::is_invocable_v<negation<move_only_predicate_t> const&&>);
}


static consteval void not_fn_decays_function() noexcept {
    bool function(int);
    static_assert(std::is_same_v<decltype(not_fn(function)), negation<bool(*)(int)>>);
}

static consteval void not_fn_decays_rvalue_ref() noexcept {
    static_assert(std::is_same_v<decltype(not_fn(std::logical_not{})), negation<std::logical_not<>>>);
}

static consteval void not_fn_decays_const_lvalue_ref() noexcept {
    constexpr std::logical_not predicate{};
    static_assert(std::is_same_v<decltype(not_fn(predicate)), negation<std::logical_not<>>>);
}


int main() {
    negation_negates_invoke_result();
    negation_of_negation_keeps_invoke_result();

    negation_is_transparent_if_wrapped_is_transparent();
    negation_is_not_transparent_if_wrapped_is_not_transparent();

    negation_is_invocable_if_wrapped_is_predicate();
    negation_is_nothrow_invocable_if_wrapped_is_nothrow_predicate();
    negation_is_move_only_invocable_if_wrapped_is_move_only_predicate();

    not_fn_decays_function();
    not_fn_decays_rvalue_ref();
    not_fn_decays_const_lvalue_ref();
}
