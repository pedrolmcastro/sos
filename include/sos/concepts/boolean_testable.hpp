#ifndef SOS_CONCEPTS_BOOLEAN_TESTABLE_HPP
#define SOS_CONCEPTS_BOOLEAN_TESTABLE_HPP


#include <utility>
#include <concepts>


namespace sos::detail::concepts {
    template<class B> concept boolean_testable_impl = std::convertible_to<B, bool>;

    /*
        Implementation of the boolean-testable exposition only concept
        https://en.cppreference.com/w/cpp/concepts/boolean-testable
    */
    template<class B> concept boolean_testable = (
        boolean_testable_impl<B> and
        requires(B&& b) { { not std::forward<B>(b) } -> boolean_testable_impl; }
    );
}


#endif
