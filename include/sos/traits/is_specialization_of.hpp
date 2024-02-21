#ifndef SOS_TRAITS_IS_SPECIALIZATION_OF_HPP
#define SOS_TRAITS_IS_SPECIALIZATION_OF_HPP


#include <type_traits>


namespace sos::detail::traits {
    /*
        Tests if T is a specialization of the template Primary i.e. T == Primary<Args...>
        https://open-std.org/JTC1/SC22/WG21/docs/papers/2020/p2098r1.pdf
    */
    template<class T, template<class...> class Primary>
    inline constexpr bool is_specialization_of{false};

    template<template<class...> class Primary, class... Args>
    inline constexpr bool is_specialization_of<Primary<Args...>, Primary>{true};
}


#endif
