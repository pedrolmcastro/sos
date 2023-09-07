#ifndef COMPARABLE_WITH_HPP
#define COMPARABLE_WITH_HPP


#include <cstddef>
#include <optional>


template<class Compared, bool Noexcept = false> struct comparable_with final {
    bool result = true;


    [[nodiscard]] constexpr bool operator==(Compared const&) const noexcept(Noexcept) {
        return result;
    }

    [[nodiscard]] constexpr bool operator==(Compared&&) const noexcept(Noexcept) {
        return result;
    }
};

template<class Compared> using nothrow_comparable_with = comparable_with<Compared, true>;


using comparable_with_nullptr = comparable_with<std::nullptr_t>;
using nothrow_comparable_with_nullptr = nothrow_comparable_with<std::nullptr_t>;

using comparable_with_nullopt = comparable_with<std::nullopt_t>;
using nothrow_comparable_with_nullopt = nothrow_comparable_with<std::nullopt_t>;


#endif
