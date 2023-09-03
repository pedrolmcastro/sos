#ifndef SOS_TRAITS_NULL_INSTANCE_HPP
#define SOS_TRAITS_NULL_INSTANCE_HPP


#include <cstddef>
#include <concepts>
#include <optional>


namespace sos {
    template<class Type>
    concept null = std::same_as<Type, std::nullptr_t> or std::same_as<Type, std::nullopt_t>;


    template<null Null> struct null_instance;

    template<> struct null_instance<std::nullptr_t> final {
        static inline constexpr auto value = nullptr;
    };

    template<> struct null_instance<std::nullopt_t> final {
        static inline constexpr auto value = std::nullopt;
    };

    template<null Null> inline constexpr auto null_instance_v = null_instance<Null>::value;
}


#endif
