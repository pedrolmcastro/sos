#include <cstddef>
#include <optional>

#include <sos/traits/null_instance.hpp>


static constexpr void test_null_instance() noexcept {
    static_assert(sos::null_instance_v<std::nullptr_t> == nullptr);
    static_assert(sos::null_instance_v<std::nullopt_t> == std::optional<int>{});
}


int main() {
    test_null_instance();
}
