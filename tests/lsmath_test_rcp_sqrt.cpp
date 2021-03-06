
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"

int main()
{
    for (unsigned i = 1; i <= 100; ++i)
    {
        const float baseImpl = 1.f / std::sqrt((float)i);
        const float testImpl = ls::math::inversesqrt<float>((float)i);
        const float errAbs = ls::math::abs(baseImpl - testImpl);
        const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

        std::cout << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
    }

    std::cout << std::endl;

    return 0;
}
