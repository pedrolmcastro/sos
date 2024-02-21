#ifndef SOS_POLICY_POLICY_HPP
#define SOS_POLICY_POLICY_HPP


#include "sos/policy/static_policy.hpp"
#include "sos/policy/dynamic_policy.hpp"


namespace sos::policy {
    template<class T> concept policy = static_policy<T> or dynamic_policy<T>;
}


#endif
