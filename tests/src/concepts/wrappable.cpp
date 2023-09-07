#include <sos/concepts/wrappable.hpp>

#include "empty_struct.hpp"


static constexpr void test_wrappable() noexcept {
    static_assert(    sos::wrappable<int>);
    static_assert(not sos::wrappable<int const>);
    static_assert(not sos::wrappable<int volatile>);

    static_assert(    sos::wrappable<int*>);
    static_assert(    sos::wrappable<int const*>);

    static_assert(not sos::wrappable<int&>);
    static_assert(not sos::wrappable<int&&>);
    static_assert(not sos::wrappable<int const&>);

    static_assert(not sos::wrappable<void>);
    static_assert(    sos::wrappable<void*>);

    static_assert(    sos::wrappable<empty_struct>);
}


int main() {
    test_wrappable();
}
