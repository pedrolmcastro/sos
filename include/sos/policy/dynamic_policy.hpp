#ifndef SOS_POLICY_DYNAMIC_POLICY_HPP
#define SOS_POLICY_DYNAMIC_POLICY_HPP


#include <variant>

#include "sos/policy/static_policy.hpp"


namespace sos::detail::policy {
    template<class T> inline constexpr bool is_dynamic_policy = false;

    template<sos::policy::static_policy... Policies> requires(sizeof...(Policies) > 0)
    inline constexpr bool is_dynamic_policy<std::variant<Policies...>> = true;
}


namespace sos::policy {
    // Specifies that T is a dynamic policy i.e. a std::variant of static policies
    template<class T> concept dynamic_policy = detail::policy::is_dynamic_policy<T>;
}


#endif
