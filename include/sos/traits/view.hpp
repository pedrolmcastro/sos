#ifndef SOS_TRAITS_VIEW_HPP
#define SOS_TRAITS_VIEW_HPP


#include <concepts>
#include <type_traits>


namespace sos::detail::traits {
    template<class T> inline constexpr bool is_viewable{
        std::is_object_v<T> and
        std::destructible<T> and
        not std::is_array_v<T> and
        not std::is_const_v<T> and
        not std::is_volatile_v<T>
    };

    template<class T> requires(is_viewable<T>) inline constexpr bool is_cheaply_trivially_copy_constructible{
        (sizeof(T) <= 2 * sizeof(void*)) and
        std::is_trivially_copy_constructible_v<T>
    };


    /*
        Alias to the most efficient between T const and T const& for in parameters or getters
        https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-in
    */
    template<class T> requires(is_viewable<T>)
    using view = std::conditional_t<is_cheaply_trivially_copy_constructible<T>, T const, T const&>;
}


#endif
