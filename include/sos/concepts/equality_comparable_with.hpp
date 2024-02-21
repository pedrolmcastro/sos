#ifndef SOS_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP
#define SOS_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP


#include <concepts>
#include <type_traits>

#include "sos/concepts/boolean_testable.hpp"


namespace sos::detail::concepts {
    template<class T, class U> concept weakly_equality_comparable_with = (
        requires(std::remove_reference_t<T> const& t, std::remove_reference_t<U> const& u) {
            { t == u } -> boolean_testable;
            { t != u } -> boolean_testable;
            { u == t } -> boolean_testable;
            { u != t } -> boolean_testable;
        }
    );

    template<class T, class U, class C = std::common_reference_t<T const&, U const&>>
    concept comparison_common_type_with_impl = (
        std::same_as<std::common_reference_t<T const&, U const&>, std::common_reference_t<U const&, T const&>> and
        requires {
            requires std::convertible_to<T const&, C const&> or std::convertible_to<T, C const&>;
            requires std::convertible_to<U const&, C const&> or std::convertible_to<U, C const&>;
        }
    );

    template<class T, class U> concept comparison_common_type_with = (
        comparison_common_type_with_impl<std::remove_cvref_t<T>, std::remove_cvref_t<U>>
    );

    /*
        Implementation of std::equality_comparable_with allowing move only types
        https://en.cppreference.com/w/cpp/concepts/equality_comparable

        Todo: Remove this in C++23 since it was standardized
    */
    template<class T, class U> concept equality_comparable_with = (
        std::equality_comparable<T> and
        std::equality_comparable<U> and
        comparison_common_type_with<T, U> and
        weakly_equality_comparable_with<T, U> and
        std::equality_comparable<std::common_reference_t<
            std::remove_reference_t<T> const&,
            std::remove_reference_t<U> const&
        >>
    );
}


#endif
