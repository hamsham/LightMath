
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"

int main()
{
    float minRelError = 0.f;
    float minAbsError = 0.f;
    float maxRelError = 0.f;
    float maxAbsError = 0.f;

    std::cout << "x, 1/std::sqrt(), math::inversesqrt(), absolute error, relative error,\n";

    for (int i = 1, j = 0; i <= 10000; ++i, ++j)
    {
        const float baseImpl = 1.f / std::sqrt((float)i);
        const float testImpl = ls::math::inversesqrt<float>((float)i);
        const float errAbs = ls::math::abs(baseImpl - testImpl);
        const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

        if (!j)
        {
            minAbsError = errAbs;
            minRelError = errRel;
            maxAbsError = errAbs;
            maxRelError = errRel;
        }
        else
        {
            minAbsError = ls::math::min(minAbsError, errAbs);
            minRelError = ls::math::min(minRelError, errRel);
            maxAbsError = ls::math::max(maxAbsError, errAbs);
            maxRelError = ls::math::max(maxRelError, errRel);
        }

        std::cout << i << ", " << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
    }

    std::cout << std::endl;

    std::cout
        << "Absolute Error:"
        << "\n\tMin: " << minAbsError
        << "\n\tMax: " << maxAbsError
        << "\nRelative Error:"
        << "\n\tMin: " << minRelError
        << "\n\tMax: " << maxRelError
        << std::endl;

    return 0;
}
