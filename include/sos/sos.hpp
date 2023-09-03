#ifndef SOS_HPP
#define SOS_HPP


#if __cplusplus < 202002L
    #error "sos requires C++20 standard or later"
#endif


#include <sos/predicates/is_empty.hpp>
#include <sos/predicates/bool_cast.hpp>
#include <sos/predicates/has_value.hpp>
#include <sos/predicates/is_filled.hpp>
#include <sos/predicates/is_equal_to_null.hpp>
#include <sos/predicates/is_not_equal_to_null.hpp>

#include <sos/traits/transparent.hpp>
#include <sos/traits/null_instance.hpp>


#endif
