#ifndef TESTABLE_HPP
#define TESTABLE_HPP


template<bool Explicit = false, bool Noexcept = false> struct testable final {
    bool result = true;


    [[nodiscard]] constexpr explicit(Explicit) operator bool() const noexcept(Noexcept) {
        return result;
    }
};

using explicit_testable = testable<true, false>;
using implicit_testable = testable<false, false>;
using nothrow_explicit_testable = testable<true, true>;
using nothrow_implicit_testable = testable<false, true>;


#endif
