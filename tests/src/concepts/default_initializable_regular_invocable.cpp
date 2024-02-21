#include <string>
#include <variant>
#include <functional>

#include "sos/concepts/default_initializable_regular_invocable.hpp"


using sos::concepts::default_initializable_predicate, sos::concepts::default_initializable_regular_invocable;


static consteval void default_initializable_regular_invocable_accepts_function_object() noexcept {
    static_assert(default_initializable_regular_invocable<std::logical_not<>, bool>);
    static_assert(default_initializable_regular_invocable<std::plus<>, std::string, std::string>);
}


static consteval void default_initializable_regular_invocable_rejects_function_ptr() noexcept {
    static_assert(not default_initializable_regular_invocable<void(*)()>);
}

static consteval void default_initializable_regular_invocable_rejects_std_function() noexcept {
    static_assert(not default_initializable_regular_invocable<std::function<void()>>);
}

static consteval void default_initializable_regular_invocable_rejects_non_invocable() noexcept {
    static_assert(not default_initializable_regular_invocable<std::monostate>);
}

static consteval void default_initializable_regular_invocable_rejects_member_function_ptr() noexcept {
    static_assert(not default_initializable_regular_invocable<bool(std::string::*)(), std::string&>);
}

static consteval void default_initializable_regular_invocable_rejects_non_default_initializable() noexcept {
    struct non_default_initializable_invocable_t {
        non_default_initializable_invocable_t() = delete;
        void operator()();
    };

    static_assert(not default_initializable_regular_invocable<non_default_initializable_invocable_t>);
}

static consteval void default_initializable_regular_invocable_rejects_invocable_with_invalid_args() noexcept {
    static_assert(not default_initializable_regular_invocable<std::plus<>>);
}


static consteval void default_initializable_predicate_accepts_predicate() noexcept {
    static_assert(default_initializable_predicate<std::logical_not<>, bool>);
}

static consteval void default_initializable_predicate_rejects_non_predicate() noexcept {
    static_assert(not default_initializable_predicate<std::plus<>, std::string, std::string>);
}


int main() {
    default_initializable_regular_invocable_accepts_function_object();

    default_initializable_regular_invocable_rejects_function_ptr();
    default_initializable_regular_invocable_rejects_std_function();
    default_initializable_regular_invocable_rejects_non_invocable();
    default_initializable_regular_invocable_rejects_member_function_ptr();
    default_initializable_regular_invocable_rejects_non_default_initializable();
    default_initializable_regular_invocable_rejects_invocable_with_invalid_args();

    default_initializable_predicate_accepts_predicate();
    default_initializable_predicate_rejects_non_predicate();
}
