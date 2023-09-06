#ifndef SOS_TRAITS_IS_DEBUG_HPP
#define SOS_TRAITS_IS_DEBUG_HPP


namespace sos {
    inline constexpr bool is_debug = (
        #ifdef NDEBUG
            false
        #else
            true
        #endif
    );
}


#endif
