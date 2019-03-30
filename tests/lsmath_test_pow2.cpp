
#include <cassert>
#include <cstdio>

#include "lightsky/math/scalar_utils.h"

int main()
{
    uint32_t p, n, c;

    p = n = c = (uint32_t)-5;

    for (unsigned i = 0; i < 100; ++i, ++p, ++n, ++c)
    {
        uint32_t p0 = ls::math::prev_pow2(p);
        uint32_t n0 = ls::math::next_pow2(n);
        uint32_t c0 = ls::math::nearest_pow2<uint32_t>(c);
        printf("%u,%u,%u,%u,%u,%u\n", p, p0, n, n0, c, c0);

        assert(!p0 || ls::math::is_pow2<uint32_t>(p0));
        assert(!n0 || ls::math::is_pow2<uint32_t>(n0));
        assert(!c0 || ls::math::is_pow2<uint32_t>(c0));
    }

    return 0;
}
