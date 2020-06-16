
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"



int main()
{
    for (int y = -10; y <= 10; ++y)
    {
        for (int x = -10; x <= 10; ++x)
        {
            const float baseImpl = std::atan2((float)y, (float)x);
            const float testImpl = ls::math::atan2((float)y, (float)x);
            const float errAbs = ls::math::abs(baseImpl - testImpl);
            const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

            std::cout << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
        }
    }

    std::cout << std::endl;

    return 0;
}
