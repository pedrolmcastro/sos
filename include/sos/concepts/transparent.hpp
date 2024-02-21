#ifndef SOS_CONCEPTS_TRANSPARENT_HPP
#define SOS_CONCEPTS_TRANSPARENT_HPP


#include <concepts>


namespace sos::concepts {
    /*
        Specifies that T is a transparent function object
        https://en.cppreference.com/w/cpp/utility/functional#Transparent_function_objects
    */
    template<class T> concept transparent = (
        std::destructible<T> and
        requires(T) { typename T::is_transparent; }
    );
}


#endif
