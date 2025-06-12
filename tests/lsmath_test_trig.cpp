
#include <cmath>
#include <iostream>

#include "lightsky/math/scalar_utils.h"


// Un-vectorized from v_sincos(), in:
// https://github.com/GaijinEntertainment/vecmath/blob/master/dag_vecMath_trig.h
// BSD license as of Jun 11, 2025
void math_sincos(float theta, float& s, float& c) noexcept
{
    float xl;
    xl = theta * (float)(2.0 * LS_PI_INVERSE);
    xl = xl + (theta >= 0.f ? 0.5f : -0.5f);

    const int q = (int)xl;

    const int offsetSin = q & 3;
    const int offsetCos = 1 + offsetSin;

    const float qf = (float)q;
    const float p1 = theta - (qf * 1.57079625129f);
    xl = p1 - (qf * 7.54978995489e-8f);

    const float xl2 = xl * xl;
    const float xl3 = xl2 * xl;

    const float ct1 = (-0.0013602249f * xl2) + 0.0416566950f;
    const float st1 = (-0.0001950727f * xl2) + 0.0083320758f;

    const float ct2 = (ct1 * xl2) + -0.4999990225f;
    const float st2 = (st1 * xl2) + -0.1666665247f;

    const float cx = (ct2 * xl2) + 1.f;
    const float sx = (st2 * xl3) + xl;

    int sinMask = !(offsetSin & 1);
    int cosMask = !(offsetCos & 1);
    s = sinMask ? sx : cx;
    c = cosMask ? sx : cx;

    sinMask = !(offsetSin & 2);
    cosMask = !(offsetCos & 2);

    s = sinMask ? s : -s;
    c = cosMask ? c : -c;
}



float math_sin(float theta) noexcept
{
    float s, c;
    math_sincos(theta, s, c);
    return s;
}



float math_cos(float theta) noexcept
{
    float s, c;
    math_sincos(theta, s, c);
    return c;
}



void test_trig_values(float x, float (*pStdFunc)(float), float (*pLsFunc)(float))
{
    float y = ls::math::radians(x);
    const float baseImpl = pStdFunc(y);
    const float testImpl = pLsFunc(y);
    const float errAbs = ls::math::abs(baseImpl - testImpl);
    const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

    printf("%1.1f | %2.9f | %2.9f | %2.9f | %2.9f", x, baseImpl, testImpl, errAbs, errRel);
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
