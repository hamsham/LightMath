
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/vec_utils.h"



int main()
{
    for (unsigned i = 1; i <= 100; ++i)
    {
        const float baseImpl = std::exp(1.f / (float)i);
        const float testImpl = ls::math::exp(ls::math::vec4{1.f / (float)i})[0];
        const float errAbs = ls::math::abs(baseImpl - testImpl);
        const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

        std::cout << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
    }

    std::cout << std::endl;

    return 0;
}
