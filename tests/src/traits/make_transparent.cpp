#include "sos/concepts/transparent.hpp"
#include "sos/traits/make_transparent.hpp"


using sos::concepts::transparent, sos::traits::make_transparent, sos::traits::make_transparent_if;


static consteval void make_transparent_tags_derived() noexcept {
    struct derived_from_make_transparent_t : make_transparent {};
    static_assert(transparent<derived_from_make_transparent_t>);
}


static consteval void make_transparent_if_true_tags_derived() noexcept {
    struct derived_from_make_transparent_if_true_t : make_transparent_if<true> {};
    static_assert(transparent<derived_from_make_transparent_if_true_t>);
}

static consteval void make_transparent_if_false_doesnt_tag_derived() noexcept {
    struct derived_from_make_transparent_if_false_t : make_transparent_if<false> {};
    static_assert(not transparent<derived_from_make_transparent_if_false_t>);
}


int main() {
    make_transparent_tags_derived();

    make_transparent_if_true_tags_derived();
    make_transparent_if_false_doesnt_tag_derived();
}
