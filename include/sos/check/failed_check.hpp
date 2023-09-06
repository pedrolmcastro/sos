#ifndef SOS_CHECK_FAILED_CHECK_HPP
#define SOS_CHECK_FAILED_CHECK_HPP


#include <exception>


namespace sos {
    struct failed_check final : std::exception {
        [[nodiscard]] constexpr char const* what() const noexcept override {
            return "predicate returned 'false' when invoked with the checked value";
        }
    };
}


#endif
