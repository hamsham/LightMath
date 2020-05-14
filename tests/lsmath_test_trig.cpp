
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"




void test_trig_values(float x, float (*pStdFunc)(float), float (*pLsFunc)(float))
{
    x = ls::math::radians(360.f / x);
    const float baseImpl = pStdFunc(x);
    const float testImpl = pLsFunc(x);
    const float errAbs = ls::math::abs(baseImpl - testImpl);
    const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

    printf("%2.9f, %2.9f, %2.9f, %2.9f,", baseImpl, testImpl, errAbs, errRel);
}




int main()
{
    printf("std::sin,ls:math::sin,absolute error,relative error,\n");
    for (int i = -360; i <= 360; ++i)
    {
        test_trig_values((float)i, std::sin, ls::math::sin);
        printf("\n");
    }
    printf("\n");

    printf("std::cos,ls:math::cos,absolute error,relative error,\n");
    for (int i = -360; i <= 360; ++i)
    {
        test_trig_values((float)i, std::cos, ls::math::cos);
        printf("\n");
    }
    printf("\n");

    printf("std::tan,ls:math::tan,absolute error,relative error,\n");
    for (int i = -360; i <= 360; ++i)
    {
        test_trig_values((float)i, std::tan, ls::math::tan);
        printf("\n");
    }
    printf("\n");

    return 0;
}
