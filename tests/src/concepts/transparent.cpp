#include "sos/concepts/transparent.hpp"

#include <functional>

using sos::concepts::enable_transparent_if, sos::concepts::transparent;

template<bool Condition>
struct [[nodiscard]] transparent_if final : enable_transparent_if<Condition> {};

static_assert(transparent<std::plus<>>);
static_assert(transparent<transparent_if<true>>);
static_assert(!transparent<transparent_if<false>>);
static_assert(!transparent<std::default_searcher<int*>>);

int main() {}
