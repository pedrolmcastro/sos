#include <variant>
#include <functional>

#include "sos/concepts/transparent.hpp"


using sos::concepts::transparent;


static consteval void transparent_rejects_untagged_object() noexcept {
    static_assert(not transparent<std::monostate>);
}

static consteval void transparent_accepts_transparent_function_object() noexcept {
    static_assert(transparent<std::logical_not<>>);
}


int main() {
    transparent_rejects_untagged_object();
    transparent_accepts_transparent_function_object();
}
