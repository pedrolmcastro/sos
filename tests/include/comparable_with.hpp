#ifndef COMPARABLE_WITH
#define COMPARABLE_WITH


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


#endif
