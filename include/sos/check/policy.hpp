#ifndef SOS_CHECK_POLICY_HPP
#define SOS_CHECK_POLICY_HPP


#include <concepts>


namespace sos {
    struct throws_t final {};
    struct asserts_t final {};
    struct terminates_t final {};
    struct unenforced_t final {};

    inline constexpr throws_t throws{};
    inline constexpr asserts_t asserts{};
    inline constexpr terminates_t terminates{};
    inline constexpr unenforced_t unenforced{};


    template<class Type> concept policy = (
        std::same_as<Type, throws_t> or
        std::same_as<Type, asserts_t> or
        std::same_as<Type, terminates_t> or
        std::same_as<Type, unenforced_t>
    );
}


#endif
