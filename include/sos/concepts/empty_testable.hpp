#ifndef SOS_CONCEPTS_EMPTY_TESTABLE_HPP
#define SOS_CONCEPTS_EMPTY_TESTABLE_HPP


#include <ranges>
#include <utility>


namespace sos {
    template<class Tested>
    concept empty_testable = requires(Tested&& tested) {
        std::ranges::empty(std::forward<Tested>(tested));
    };

    template<class Tested>
    concept nothrow_empty_testable = empty_testable<Tested> and requires(Tested&& tested) {
        { std::ranges::empty(std::forward<Tested>(tested)) } noexcept;
    };
}


#endif
