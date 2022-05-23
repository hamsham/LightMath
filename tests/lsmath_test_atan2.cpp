
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"



void test_atan2(const char* method)
{
    std::cout << "x, std::" << method << ", math::" << method << ", absolute error, relative error\n";

    constexpr int iters = 10;
    constexpr float ratio = LS_PI / (float)iters;

    for (int y = -iters; y <= iters; ++y)
    {
        for (int x = -iters; x <= iters; ++x)
        {
            const float xf = (float)x/ratio;
            const float yf = (float)y/ratio;
            const float baseImpl = std::atan2(yf, xf);
            const float testImpl = ls::math::atan2(yf, xf);
            const float errAbs = ls::math::abs(baseImpl - testImpl);
            const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

            std::cout << (xf+yf+ratio) << ", " << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << '\n';
        }
    }
}



void test_arc_func(const char* method, float (*pStdFunc)(float), float (*pLsFunc)(float))
{
    std::cout << "x, std::" << method << ", math::" << method << ", absolute error, relative error\n";

    constexpr int iters = 100;

    for (int x = -iters; x <= iters; ++x)
    {
        const float i        = LS_PI_OVER_4 * ((float)x / (float)iters);
        const float baseImpl = pStdFunc(i);
        const float testImpl = pLsFunc(i);
        const float errAbs = ls::math::abs(baseImpl - testImpl);
        const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

        std::cout << x << ", " << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << '\n';
    }
}



int main()
{
    //test_atan2("atan2");
    test_arc_func("atan", std::atan, ls::math::atan);
    //test_arc_func("acos", std::acos, ls::math::acos);
    //test_arc_func("asin", std::asin, ls::math::asin);

    std::cout << std::endl;

    return 0;
}
