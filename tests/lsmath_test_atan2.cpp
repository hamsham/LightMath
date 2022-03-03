
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"



void test_atan2()
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
}



void test_acos()
{
    for (int x = -10; x <= 10; ++x)
    {
        const float i        = LS_TWO_PI * ((float)x / 10.f);
        const float baseImpl = std::acos(i);
        const float testImpl = ls::math::acos(i);
        const float errAbs = ls::math::abs(baseImpl - testImpl);
        const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

        std::cout << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
    }
}



void test_asin()
{
    for (int x = -10; x <= 10; ++x)
    {
        const float i        = LS_TWO_PI * ((float)x / 10.f);
        const float baseImpl = std::asin(i);
        const float testImpl = ls::math::asin(i);
        const float errAbs   = ls::math::abs(baseImpl - testImpl);
        const float errRel   = 100.f * (errAbs / ls::math::abs(baseImpl));

        std::cout << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
    }
}



int main()
{
    test_atan2();
    //test_acos();
    //test_asin();

    std::cout << std::endl;

    return 0;
}
