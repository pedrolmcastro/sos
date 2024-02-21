#ifndef SOS_PREDICATES_FROM_PREDICATE_HPP
#define SOS_PREDICATES_FROM_PREDICATE_HPP


namespace sos::predicates {
    struct from_predicate_t final {
        explicit from_predicate_t() = default;
    };

    inline constexpr from_predicate_t from_predicate{};
}


#endif
