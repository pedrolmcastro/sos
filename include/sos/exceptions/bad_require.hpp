#ifndef SOS_EXCEPTIONS_BAD_REQUIRE_HPP
#define SOS_EXCEPTIONS_BAD_REQUIRE_HPP


#include <exception>


namespace sos::exceptions {
    struct bad_require final : std::exception {
        [[nodiscard]] constexpr char const * what() const noexcept override {
            return "sos::require: predicate not satisfied";
        }
    };
}


#endif
