#include <sos/check/checked.hpp>
#include <sos/check/is_checked.hpp>
#include <sos/predicates/always_true.hpp>


static constexpr void test_is_checked() noexcept {
    static_assert(not sos::is_checked_v<int>);
    static_assert(    sos::is_checked_v<sos::checked<int>>);
    static_assert(    sos::is_checked_v<sos::checked<int, sos::always_true_t>>);
}


int main() {
    test_is_checked();
}
