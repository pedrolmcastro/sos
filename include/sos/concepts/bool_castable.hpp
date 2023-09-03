#ifndef SOS_CONCEPTS_BOOL_CASTABLE_HPP
#define SOS_CONCEPTS_BOOL_CASTABLE_HPP


#include <utility>


namespace sos {
    template<class From>
    concept bool_castable = requires(From&& from) {
        static_cast<bool>(std::forward<From>(from));
    };

    template<class From>
    concept nothrow_bool_castable = bool_castable<From> and requires(From&& from) {
        { static_cast<bool>(std::forward<From>(from)) } noexcept;
    };
}


#endif
