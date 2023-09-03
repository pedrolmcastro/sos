#ifndef SOS_CONCEPTS_NULL_HPP
#define SOS_CONCEPTS_NULL_HPP


#include <cstddef>
#include <concepts>
#include <optional>


namespace sos {
    template<class Type>
    concept null = std::same_as<Type, std::nullptr_t> or std::same_as<Type, std::nullopt_t>;
}


#endif
