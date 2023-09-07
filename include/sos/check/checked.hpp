#ifndef SOS_CHECK_CHECKED_HPP
#define SOS_CHECK_CHECKED_HPP


#include <utility>
#include <concepts>
#include <type_traits>

#include <sos/check/check.hpp>
#include <sos/check/policy.hpp>
#include <sos/check/checkable.hpp>
#include <sos/check/is_checked.hpp>
#include <sos/concepts/wrappable.hpp>
#include <sos/predicates/bool_cast.hpp>


namespace sos {
    template<wrappable Element, std::destructible Predicate = bool_cast_t> class checked {
    public:
        static_assert(
            not is_checked_v<Element>,
            "checked<checked<T>> is not supported since it would duplicate runtime checks"
        );


        using element_type = Element;
        using predicate_type = Predicate;


        template<policy Policy> explicit constexpr checked(Policy policy)
            noexcept(
                std::is_nothrow_default_constructible_v<element_type> and
                std::is_nothrow_default_constructible_v<predicate_type> and
                nothrow_checkable<Policy, element_type, predicate_type>
            )
            requires(
                std::default_initializable<element_type> and
                std::default_initializable<predicate_type> and
                checkable<Policy, element_type, predicate_type>
            )
        {
            check(policy);
        }

        template<policy Policy, class OElement> constexpr checked(Policy policy, OElement&& element)
            noexcept(
                std::is_nothrow_constructible_v<element_type, OElement&&> and
                std::is_nothrow_default_constructible_v<predicate_type> and
                nothrow_checkable<Policy, element_type, predicate_type>
            )
            requires(
                std::constructible_from<element_type, OElement&&> and
                std::default_initializable<predicate_type> and
                checkable<Policy, element_type, predicate_type>
            )
            : m_element{std::forward<OElement>(element)}
        {
            check(policy);
        }

        template<policy Policy, class Other> constexpr checked(Policy policy, Other&& other)
            noexcept(
                std::is_nothrow_constructible_v<
                    element_type,
                    decltype(std::forward<Other>(other).get())
                > and
                std::is_nothrow_default_constructible_v<predicate_type> and
                nothrow_checkable<Policy, element_type, predicate_type>
            )
            requires(
                is_checked_v<std::remove_cvref_t<Other>> and
                std::constructible_from<
                    element_type,
                    decltype(std::forward<Other>(other).get())
                > and
                std::default_initializable<predicate_type> and
                checkable<Policy, element_type, predicate_type>
            )
            : checked{policy, std::forward<Other>(other).get()}
        {}

        template<policy Policy, class OElement, class OPredicate>
        constexpr checked(Policy policy, OElement&& element, OPredicate&& predicate)
            noexcept(
                std::is_nothrow_constructible_v<element_type, OElement&&> and
                std::is_nothrow_constructible_v<predicate_type, OPredicate&&> and
                nothrow_checkable<Policy, element_type, predicate_type>
            )
            requires(
                std::constructible_from<element_type, OElement&&> and
                std::constructible_from<predicate_type, OPredicate&&> and
                checkable<Policy, element_type, predicate_type>
            )
            : m_element{std::forward<OElement>(element)}
            , m_predicate{std::forward<OPredicate>(predicate)}
        {
            check(policy);
        }

        template<policy Policy, class ... Args>
        constexpr checked(Policy policy, std::in_place_t, Args&& ... args)
            noexcept(
                std::is_nothrow_constructible_v<element_type, Args&& ...> and
                std::is_nothrow_default_constructible_v<predicate_type> and
                nothrow_checkable<Policy, element_type, predicate_type>
            )
            requires(
                std::constructible_from<element_type, Args&& ...> and
                std::default_initializable<predicate_type> and
                checkable<Policy, element_type, predicate_type>
            )
            : m_element{std::forward<Args>(args) ...}
        {
            check(policy);
        }


        template<policy Policy, class OElement>
        constexpr checked& reset(Policy policy, OElement&& element)
            noexcept(
                std::is_nothrow_assignable_v<element_type&, OElement&&> and
                nothrow_checkable<Policy, element_type, predicate_type>
            )
            requires(
                std::assignable_from<element_type&, OElement&&> and
                checkable<Policy, element_type, predicate_type>
            )
        {
            m_element = std::forward<OElement>(element);
            check(policy);
            return *this;
        }

        template<policy Policy, class Other> constexpr checked& reset(Policy policy, Other&& other)
            noexcept(
                std::is_nothrow_assignable_v<
                    element_type&,
                    decltype(std::forward<Other>(other).get())
                > and
                nothrow_checkable<Policy, element_type, predicate_type>
            )
            requires(
                is_checked_v<std::remove_cvref_t<Other>> and
                std::assignable_from<element_type&, decltype(std::forward<Other>(other).get())> and
                checkable<Policy, element_type, predicate_type>
            )
        {
            return reset(policy, std::forward<Other>(other).get());
        }

        constexpr checked& reset(checked const& other)
            noexcept(std::is_nothrow_copy_assignable_v<checked>)
            requires(std::is_copy_assignable_v<checked>)
        {
            return *this = other;
        }

        constexpr checked& reset(checked&& other)
            noexcept(std::is_nothrow_move_assignable_v<checked>)
            requires(std::is_move_assignable_v<checked>)
        {
            return *this = std::move(other);
        }


        template<policy Policy> constexpr void check(Policy policy) const
            noexcept(nothrow_checkable<Policy, element_type, predicate_type>)
            requires(checkable<Policy, element_type, predicate_type>)
        {
            sos::check(policy, m_element, m_predicate);
        }


        [[nodiscard]] constexpr element_type const& get() const& noexcept {
            return m_element;
        }

        [[nodiscard]] constexpr element_type&& get() && noexcept {
            return std::move(m_element);
        }


        [[nodiscard]] constexpr predicate_type const& predicate() const& noexcept {
            return m_predicate;
        }

        [[nodiscard]] constexpr predicate_type&& predicate() && noexcept {
            return std::move(m_predicate);
        }

    private:
        element_type m_element{};
        predicate_type m_predicate{};
    };


    template<
        policy Policy,
        wrappable Element,
        std::default_initializable Predicate = bool_cast_t,
        class ... Args
    >
    [[nodiscard]] constexpr checked<Element, Predicate> make_checked(Args&& ... args)
        noexcept(
            std::is_nothrow_constructible_v<Element, Args&& ...> and
            nothrow_checkable<Policy, Element, Predicate>
        )
        requires(
            std::constructible_from<Element, Args&& ...> and
            checkable<Policy, Element, Predicate>
        )
    {
        return checked<Element, Predicate>{Policy{}, std::in_place, std::forward<Args>(args) ...};
    }
}


#endif
