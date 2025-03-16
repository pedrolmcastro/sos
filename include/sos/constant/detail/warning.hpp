#ifndef SOS_CONSTANT_DETAIL_WARNING_HPP
#define SOS_CONSTANT_DETAIL_WARNING_HPP

namespace sos::constant::detail {
    template<bool> consteval void warning() noexcept {}

    template<>
    [[deprecated(
        "Non-terminating constant evaluated contract assertion failed"
    )]]
    consteval void warning<false>() noexcept {}
}

#endif
