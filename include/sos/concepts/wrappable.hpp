#ifndef SOS_CONCEPTS_WRAPPABLE_HPP
#define SOS_CONCEPTS_WRAPPABLE_HPP


#include <concepts>
#include <type_traits>


namespace sos {
    template<class Wrapped> concept wrappable = (
        std::destructible<Wrapped> and
        not std::is_const_v<Wrapped> and
        not std::is_volatile_v<Wrapped> and
        not std::is_reference_v<Wrapped>
    );
}


#endif
