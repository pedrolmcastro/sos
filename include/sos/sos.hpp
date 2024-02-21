#ifndef SOS_SOS_HPP
#define SOS_SOS_HPP


#if __cplusplus < 202002L
    #error "sos requires the C++20 standard or later"
#endif


#include "sos/concepts/transparent.hpp"
#include "sos/concepts/default_initializable_regular_invocable.hpp"

#include "sos/constraints/constrained.hpp"

#include "sos/exceptions/bad_require.hpp"

#include "sos/policy/is.hpp"
#include "sos/policy/policy.hpp"
#include "sos/policy/policies.hpp"
#include "sos/policy/static_policy.hpp"
#include "sos/policy/dynamic_policy.hpp"

#include "sos/predicates/always.hpp"
#include "sos/predicates/is_null.hpp"
#include "sos/predicates/is_empty.hpp"
#include "sos/predicates/negation.hpp"
#include "sos/predicates/bool_cast.hpp"

#include "sos/require/require.hpp"
#include "sos/require/is_requireable.hpp"

#include "sos/traits/is_debug_mode.hpp"
#include "sos/traits/make_transparent.hpp"


#endif
