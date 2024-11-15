#include "sos/predicates/constant.hpp"

using sos::predicates::falsy, sos::predicates::truthy;

static_assert(!falsy);
static_assert(!falsy());
static_assert(!static_cast<bool>(falsy));

static_assert(truthy);
static_assert(truthy());
static_assert(truthy(1, '2', "3"));
static_assert(static_cast<bool>(truthy));

int main() {}
