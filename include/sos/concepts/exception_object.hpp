#ifndef SOS_CONCEPTS_EXCEPTION_OBJECT_HPP
#define SOS_CONCEPTS_EXCEPTION_OBJECT_HPP


#include <concepts>
#include <type_traits>


namespace sos::detail::concepts {
    /*
        Specifies that T can be used as an exception object
        https://en.cppreference.com/w/cpp/language/throw#The_exception_object
    */
    template<class T> concept exception_object = (
        not std::is_void_v<T> and
        not std::is_abstract_v<T> and
        std::copy_constructible<T> and
        std::same_as<T, std::decay_t<T>>
    );
}


#endif
