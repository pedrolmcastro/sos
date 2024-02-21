#ifndef SOS_TRAITS_MAKE_TRANSPARENT_HPP
#define SOS_TRAITS_MAKE_TRANSPARENT_HPP


#include <type_traits>


namespace sos::detail::traits {
    struct make_opaque {
        protected:
        ~make_opaque() = default;
    };
}

namespace sos::traits {
    /*
        Adds the transparent function object tag to a publically derived type
        https://en.cppreference.com/w/cpp/utility/functional#Transparent_function_objects
    */
    struct make_transparent {
        public:
        using is_transparent = std::true_type;

        protected:
        ~make_transparent() = default;
    };

    template<bool Condition> using make_transparent_if =
        std::conditional_t<Condition, make_transparent, detail::traits::make_opaque>
    ;
}


#endif
