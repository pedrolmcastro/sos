#ifndef SOS_POLICY_POLICIES_HPP
#define SOS_POLICY_POLICIES_HPP


#include <cstdlib>
#include <concepts>

#include "sos/concepts/exception_object.hpp"

#include "sos/exceptions/bad_require.hpp"


namespace sos::policy::policies {
    struct aborts_t final {};
    inline constexpr aborts_t aborts{};


    struct asserts_t final {};
    inline constexpr asserts_t asserts{};


    template<int Code> struct exits_with_t final {
        inline static constexpr int code = Code;
    };

    using exits_with_success_t = exits_with_t<EXIT_SUCCESS>;
    inline constexpr exits_with_success_t exits_with_success{};

    using exits_with_failure_t = exits_with_t<EXIT_FAILURE>;
    inline constexpr exits_with_failure_t exits_with_failure{};


    template<int Code> struct quick_exits_with_t final {
        inline static constexpr int code = Code;
    };

    using quick_exits_with_success_t = quick_exits_with_t<EXIT_SUCCESS>;
    inline constexpr quick_exits_with_success_t quick_exits_with_success{};

    using quick_exits_with_failure_t = quick_exits_with_t<EXIT_FAILURE>;
    inline constexpr quick_exits_with_failure_t quick_exits_with_failure{};


    struct terminates_t final {};
    inline constexpr terminates_t terminates{};


    template<detail::concepts::exception_object Exception> requires(std::default_initializable<Exception>)
    struct throws_with_t final {
        using exception_type = Exception;
    };

    using throws_with_bad_require_t = throws_with_t<exceptions::bad_require>;
    inline constexpr throws_with_bad_require_t throws_with_bad_require{};


    struct unenforced_t final {};
    inline constexpr unenforced_t unenforced{};
}


namespace sos {
    namespace policies = policy::policies;
}


#endif
