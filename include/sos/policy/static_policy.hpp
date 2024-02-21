#ifndef SOS_POLICY_STATIC_POLICY_HPP
#define SOS_POLICY_STATIC_POLICY_HPP


#include <concepts>

#include "sos/policy/is.hpp"
#include "sos/policy/policies.hpp"


namespace sos::policy {
    template<class T> concept static_policy = (
        is_exits<T> or
        is_aborts<T> or
        is_throws<T> or
        is_asserts<T> or
        is_terminates<T> or
        is_unenforced<T> or
        is_quick_exits<T>
    );
}


#endif
