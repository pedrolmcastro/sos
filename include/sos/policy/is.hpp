#ifndef SOS_POLICY_IS_HPP
#define SOS_POLICY_IS_HPP


#include <type_traits>

#include "sos/policy/policies.hpp"

#include "sos/traits/is_specialization_of.hpp"


namespace sos::policy {
    template<class T> inline constexpr bool is_aborts = std::is_same_v<T, policies::aborts_t>;

    template<class T> inline constexpr bool is_asserts = std::is_same_v<T, policies::asserts_t>;

    template<class T> inline constexpr bool is_exits = false;
    template<int Code> inline constexpr bool is_exits<policies::exits_with_t<Code>> = true;

    template<class T> inline constexpr bool is_quick_exits = false;
    template<int Code> inline constexpr bool is_quick_exits<policies::quick_exits_with_t<Code>> = true;

    template<class T> inline constexpr bool is_terminates = std::is_same_v<T, policies::terminates_t>;

    template<class T> inline constexpr bool is_throws = detail::traits::is_specialization_of<T,policies::throws_with_t>;

    template<class T> inline constexpr bool is_unenforced = std::is_same_v<T, policies::unenforced_t>;
}


#endif
