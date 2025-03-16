#ifndef SOS_CONTRACTS_ASSERTION_KIND_HPP
#define SOS_CONTRACTS_ASSERTION_KIND_HPP

namespace sos::contracts {
    /** @see https://en.cppreference.com/w/cpp/contracts/assertion_kind */
    enum class assertion_kind {
        pre = 1,
        post,
        assert,
    };
}

#endif
