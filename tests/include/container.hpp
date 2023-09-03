#ifndef CONTAINER_HPP
#define CONTAINER_HPP


#include <cstddef>


template<bool Noexcept = false> struct emptiable_container final {
    bool is_empty = true;


    [[nodiscard]] constexpr bool empty() const noexcept(Noexcept) {
        return is_empty;
    }
};

using nothrow_emptiable_container = emptiable_container<true>;


template<bool Noexcept = false> struct sized_container final {
    std::size_t contained = 0;


    [[nodiscard]] constexpr std::size_t size() const noexcept(Noexcept) {
        return contained;
    }
};

using nothrow_sized_container = sized_container<true>;


template<bool Noexcept = false> struct valued_container final {
    bool has = true;


    [[nodiscard]] constexpr bool has_value() const noexcept(Noexcept) {
        return has;
    }
};

using nothrow_valued_container = valued_container<true>;


#endif
