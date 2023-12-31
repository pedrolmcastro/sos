#ifndef SOS_SOS_HPP
#define SOS_SOS_HPP


#if __cplusplus < 202002L
    #error "sos requires C++20 standard or later"
#endif


#include <sos/check/check.hpp>
#include <sos/check/policy.hpp>
#include <sos/check/checked.hpp>
#include <sos/check/checkable.hpp>
#include <sos/check/is_checked.hpp>
#include <sos/check/failed_check.hpp>

#include <sos/concepts/wrappable.hpp>

#include <sos/predicates/is_null.hpp>
#include <sos/predicates/is_empty.hpp>
#include <sos/predicates/bool_cast.hpp>
#include <sos/predicates/has_value.hpp>
#include <sos/predicates/is_filled.hpp>
#include <sos/predicates/always_true.hpp>
#include <sos/predicates/is_not_null.hpp>
#include <sos/predicates/always_false.hpp>

#include <sos/traits/is_debug.hpp>
#include <sos/traits/transparent.hpp>
#include <sos/traits/null_instance.hpp>


#endif
