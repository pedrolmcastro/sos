#ifndef SOS_CONTRACTS_DETECTION_MODE_HPP
#define SOS_CONTRACTS_DETECTION_MODE_HPP

namespace sos::contracts {
    /** @see https://en.cppreference.com/w/cpp/contracts/detection_mode */
    enum class detection_mode {
        predicate_false = 1,
        evaluation_exception,
    };
}

#endif
