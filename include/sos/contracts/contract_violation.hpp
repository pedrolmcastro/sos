#ifndef SOS_CONTRACTS_CONTRACT_VIOLATION_HPP
#define SOS_CONTRACTS_CONTRACT_VIOLATION_HPP

#include "sos/contracts/assertion_kind.hpp"
#include "sos/contracts/detection_mode.hpp"
#include "sos/contracts/evaluation_semantic.hpp"

#include <concepts>
#include <exception>
#include <source_location>
#include <string>
#include <type_traits>
#include <utility>

namespace sos::contracts {
    namespace detail {
        template<class Predicate>
        void invoke_contract_violation_handler(
            contracts::assertion_kind const,
            contracts::evaluation_semantic const,
            std::source_location&&,
            Predicate const&
        );
    }

    /** @see https://en.cppreference.com/w/cpp/contracts/contract_violation */
    class [[nodiscard]] contract_violation final {
    public:
        contract_violation() = delete;
        contract_violation(contract_violation&&) = delete;
        contract_violation(contract_violation const&) = delete;
        contract_violation& operator=(contract_violation&&) = delete;
        contract_violation& operator=(contract_violation const&) = delete;

        /**
         * @post return != nullptr
         * @post return points to a null-terminated character array
         */
        [[nodiscard]] constexpr char const* comment() const noexcept {
            return m_comment.c_str();
        }

        [[nodiscard]] contracts::detection_mode detection_mode() const noexcept {
            return evaluation_exception()
                       ? contracts::detection_mode::evaluation_exception
                       : contracts::detection_mode::predicate_false;
        }

        [[nodiscard]] std::exception_ptr evaluation_exception() const noexcept {
            return m_evaluation_exception;
        }

        [[nodiscard]] constexpr bool is_terminating() const noexcept {
            return m_semantic == evaluation_semantic::enforce;
        }

        [[nodiscard]] constexpr assertion_kind kind() const noexcept {
            return m_kind;
        }

        [[nodiscard]] constexpr std::source_location location() const noexcept {
            return m_location;
        }

        /**
         * @post return != evaluation_semantic::ignore
         * @post return != evaluation_semantic::quick_enforce
         */
        [[nodiscard]] constexpr evaluation_semantic semantic() const noexcept {
            return m_semantic;
        }

    private:
        template<class Predicate>
        friend void detail::invoke_contract_violation_handler(
            assertion_kind const,
            evaluation_semantic const,
            std::source_location&&,
            Predicate const&
        );

        /**
         * @pre semantic != evaluation_semantic::ignore
         * @pre semantic != evaluation_semantic::quick_enforce
         */
        contract_violation(
            assertion_kind const kind,
            evaluation_semantic const semantic,
            std::source_location&& location
        ) noexcept(std::is_nothrow_move_constructible_v<std::exception_ptr>) :
            m_location{std::move(location)},
            m_kind{kind},
            m_semantic{semantic} {}

        /**
         * @pre semantic != evaluation_semantic::ignore
         * @pre semantic != evaluation_semantic::quick_enforce
         */
        template<class Comment>
            requires std::constructible_from<std::string, Comment&&>
        contract_violation(
            assertion_kind const kind,
            evaluation_semantic const semantic,
            std::source_location&& location,
            Comment&& comment
            // clang-format off
        ) noexcept(
            std::is_nothrow_move_constructible_v<std::exception_ptr> and
            std::is_nothrow_constructible_v<std::string, Comment&&>
        ) :
            // clang-format on
            m_comment{std::forward<Comment>(comment)},
            m_location{std::move(location)},
            m_kind{kind},
            m_semantic{semantic} {}

        std::string m_comment{};
        std::exception_ptr m_evaluation_exception{std::current_exception()};
        std::source_location m_location;
        assertion_kind m_kind;
        /**
         * @invariant m_semantic != evaluation_semantic::ignore
         * @invariant m_semantic != evaluation_semantic::quick_enforce
         */
        evaluation_semantic m_semantic;
    };
}

#endif
