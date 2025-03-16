#ifndef SOS_CONTRACTS_HANDLE_CONTRACT_VIOLATION_HPP
#define SOS_CONTRACTS_HANDLE_CONTRACT_VIOLATION_HPP

#include "sos/contracts/contract_violation.hpp"

namespace sos::contracts {
    /**
     * @see https://en.cppreference.com/w/cpp/language/contracts#Contract-violation_handler
     */
    void handle_contract_violation(contracts::contract_violation const&);
}

#endif
