
#include <chrono>
#include <iostream>
#include <iomanip>

#include "lightsky/math/scalar_utils.h"



namespace chrono = std::chrono;
typedef chrono::steady_clock::time_point hr_time;
typedef chrono::nanoseconds hr_prec;



inline LS_INLINE float rsqrt_test(float input, uint32_t magic = 0x5F1FFFF9u) noexcept
{
    union
    {
        float f;
        uint32_t u;
    } y = {input};
    y.u = magic - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - input * y.f * y.f);
}



void find_magic() noexcept
{
    constexpr int maxIters = 10000;
    unsigned magic = 0;
    double absError = std::numeric_limits<double>::max();
    double relError = std::numeric_limits<double>::max();

    for (unsigned i = 0x5F100000; i < 0x5F200000; ++i)
    {
        double maxAbsError = 0.0;
        double maxRelError = 0.0;

        for (int j = 1; j <= maxIters; ++j)
        {
            const double baseImpl = (double)(1.f / std::sqrt((float)j));
            const double testImpl = (double)rsqrt_test((float)j, i);

            const double errAbs = ls::math::abs(baseImpl - testImpl);
            const double errRel = 100.0 * (errAbs / ls::math::abs(baseImpl));

            maxAbsError = ls::math::max(maxAbsError, errAbs);
            maxRelError = ls::math::max(maxRelError, errRel);
        }

        if (maxAbsError < absError && maxRelError < relError)
        {
            absError = maxAbsError;
            relError = maxRelError;
            magic = i;

            //printf("Magic (%%err=%f): 0x%X\n", absError, magic);
        }
    }

    std::cout
        << "Magic: 0x" << std::hex << magic << std::dec << 'u'
        << "\n\tAbs Error: " << absError
        << "\n\tRel Error: " << relError
        << std::endl;
}



int main()
{
    float minRelError = 0.f;
    float minAbsError = 0.f;
    float maxRelError = 0.f;
    float maxAbsError = 0.f;
    constexpr int maxIters = 10000;

    uint64_t stdTime = 0;
    uint64_t lsTime = 0;

    //std::cout << "x, 1.f/std::sqrt(), math::inversesqrt(), absolute error, relative error,\n";

    for (int i = 1, j = 0; i <= maxIters; ++i, ++j)
    {
        hr_time t1, t2;

        t1 = chrono::steady_clock::now();
        const float baseImpl = 1.f / std::sqrt((float)i);
        t2 = chrono::steady_clock::now();
        stdTime += chrono::duration_cast<hr_prec>(t2 - t1).count();

        t1 = chrono::steady_clock::now();
        const float testImpl = ls::math::inversesqrt<float>((float)i);
        t2 = chrono::steady_clock::now();
        lsTime += chrono::duration_cast<hr_prec>(t2 - t1).count();

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

        //std::cout << i << ", " << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
    }

    std::cout << std::endl;

    std::cout << std::setprecision(std::numeric_limits<float>::digits)
        << "Absolute Error:"
        << "\n\tMin: " << minAbsError
        << "\n\tMax: " << maxAbsError
        << "\nRelative Error:"
        << "\n\tMin: " << minRelError
        << "\n\tMax: " << maxRelError
        << "\nTiming:"
        << "\n\tStd (ns): " << stdTime
        << "\n\tLS (ns):  " << lsTime
        << std::endl;

    find_magic();

    return 0;
}
