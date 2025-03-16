#include "sos/predicates/constant.hpp"

using sos::predicates::falsy, sos::predicates::truthy;

static_assert(not falsy);
static_assert(not falsy());
static_assert(not static_cast<bool>(falsy));

static_assert(truthy);
static_assert(truthy());
static_assert(truthy(1, '2', "3"));
static_assert(static_cast<bool>(truthy));

int main() {}
