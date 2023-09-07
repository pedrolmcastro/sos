#ifndef SOS_CHECK_IS_CHECKED_HPP
#define SOS_CHECK_IS_CHECKED_HPP


#include <concepts>
#include <type_traits>

#include <sos/concepts/wrappable.hpp>


namespace sos {
    template<wrappable, std::destructible> class checked;


    template<class Tested>
    struct is_checked final : std::false_type {};

    template<wrappable Checked, std::destructible Predicate>
    struct is_checked<checked<Checked, Predicate>> final : std::true_type {};


    template<class Tested> inline constexpr bool is_checked_v = is_checked<Tested>::value;
}


#endif
