
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"



void test_trig_values(float x, float (*pStdFunc)(float), float (*pLsFunc)(float))
{
    float y = ls::math::radians(x);
    const float baseImpl = pStdFunc(y);
    const float testImpl = pLsFunc(y);
    const float errAbs = ls::math::abs(baseImpl - testImpl);
    const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

    printf("%1.1f, %2.9f, %2.9f, %2.9f, %2.9f", x, baseImpl, testImpl, errAbs, errRel);
}



int main()
{
    constexpr int steps = 540;

    #if 0
        printf("x, std::sin, ls:math::sin, absolute error, relative error\n");
        for (int i = -steps; i <= steps; ++i)
        {
            test_trig_values((float)i, std::sin, ls::math::sin);
            printf("\n");
        }
        printf("\n");
    #endif

    #if 1
        printf("x, std::cos, ls:math::cos, absolute error, relative error\n");
        for (int i = -steps; i <= steps; ++i)
        {
            test_trig_values((float)i, std::cos, ls::math::cos);
            printf("\n");
        }
        printf("\n");
    #endif

    #if 0
        printf("x, std::tan, ls:math::tan, absolute error, relative error\n");
        for (int i = -steps; i <= steps; ++i)
        {
            test_trig_values((float)i, std::tan, ls::math::tan);
            printf("\n");
        }
        printf("\n");
    #endif

    return 0;
}
