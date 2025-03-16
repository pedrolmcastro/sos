#ifndef SOS_CONTRACTS_INVOKE_DEFAULT_CONTRACT_VIOLATION_HANDLER_HPP
#define SOS_CONTRACTS_INVOKE_DEFAULT_CONTRACT_VIOLATION_HANDLER_HPP

#include "sos/contracts/assertion_kind.hpp"
#include "sos/contracts/contract_violation.hpp"

#include <cstdio>
#include <cstdlib>
#include <format>
#include <string>
#include <string_view>

namespace sos::contracts {
    /**
     * @see https://en.cppreference.com/w/cpp/contracts/invoke_default_contract_violation_handler
     */
    [[noreturn]] inline void invoke_default_contract_violation_handler(
        contract_violation const& violation
    ) {
        using namespace std::string_literals;
        using namespace std::string_view_literals;

        auto const comment{violation.comment()};
        auto const location{violation.location()};

        auto const message{std::format(
            "{}:{}:{}: {}{} failed\n",
            location.file_name(),
            location.line(),
            location.function_name(),
            ([kind = violation.kind()]() {
                switch (kind) {
                    case assertion_kind::assert:
                        return "Assertion"sv;

                    case assertion_kind::post:
                        return "Postcondition"sv;

                    case assertion_kind::pre:
                        return "Precondition"sv;
                }
            })(),
            *comment ? std::format(" '{}'", comment) : ""s
        )};

        std::fputs(message.c_str(), stderr);
        std::abort();
    }
}

#endif
