#ifndef SOS_CONCEPTS_TRANSPARENT_HPP
#define SOS_CONCEPTS_TRANSPARENT_HPP

#include <type_traits>

namespace sos::concepts {
    namespace detail {
        struct empty {};
    }

    template<class T>
    concept transparent = requires { typename T::is_transparent; };

    struct enable_transparent {
        using is_transparent = std::true_type;

    protected:
        ~enable_transparent() = default;
    };

    template<bool Condition>
    using enable_transparent_if =
        std::conditional_t<Condition, enable_transparent, detail::empty>;
}

#endif
