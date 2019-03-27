
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"




void test_log_values(float x, float (*pStdFunc)(float), float (*pLsFunc)(float))
{
    x = ls::math::radians(100.f / x);
    const float baseImpl = pStdFunc(x);
    const float testImpl = pLsFunc(x);
    const float errAbs = ls::math::abs(baseImpl - testImpl);
    const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

    printf("%2.9f, %2.9f, %2.9f, %2.9f,", baseImpl, testImpl, errAbs, errRel);
}




int main()
{
    printf("std::log,ls:math::log,absolute error,relative error,std::log2,ls:math::log2,absolute error,relative error,std::log10,ls:math::log10,absolute error,relative error,\n");

    for (unsigned i = 1; i <= 100; ++i)
    {
        test_log_values((float)i, std::log, ls::math::log);
        test_log_values((float)i, std::log2, ls::math::log2);
        test_log_values((float)i, std::log10, ls::math::log10);
        printf("\n");
    }

    printf("\n");

    return 0;
}
