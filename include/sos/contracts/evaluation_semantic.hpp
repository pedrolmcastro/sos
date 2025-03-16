#ifndef SOS_CONTRACTS_EVALUATION_SEMANTIC_HPP
#define SOS_CONTRACTS_EVALUATION_SEMANTIC_HPP

namespace sos::contracts {
    /** @see https://en.cppreference.com/w/cpp/contracts/evaluation_semantic */
    enum class evaluation_semantic {
        ignore = 1,
        observe,
        enforce,
        quick_enforce,
    };
}

#endif
