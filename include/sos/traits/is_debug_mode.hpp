#ifndef SOS_TRAITS_IS_DEBUG_MODE_HPP
#define SOS_TRAITS_IS_DEBUG_MODE_HPP


namespace sos::traits {
    inline constexpr bool is_debug_mode{
        #ifdef NDEBUG
            false
        #else
            true
        #endif
    };
}


#endif
