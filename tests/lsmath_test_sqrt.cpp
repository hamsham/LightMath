
#include <chrono>
#include <iostream>
#include <iomanip>

#include "lightsky/math/scalar_utils.h"



namespace chrono = std::chrono;
typedef chrono::steady_clock::time_point hr_time;
typedef chrono::nanoseconds hr_prec;



inline LS_INLINE float sqrt_test(float input, uint32_t magic = 0x1FBB67AEu) noexcept
{
    const float f = (float)input;
    union
    {
        float f;
        uint32_t i;
    } y;

    y.f = f;
    y.i >>= 1u;
    y.i += magic;
    float f1 = y.f;
    f1 = (f / f1) + f1;
    f1 = (f / f1) + (f1 * 0.25f);
    //f1 = 0.5f * (f1 + f / f1);
    //f1 = 0.5f * (f1 + f / f1);

    return f1;
}



void find_magic() noexcept
{
    constexpr int maxIters = 1000;
    unsigned magic = 0;
    double absError = std::numeric_limits<double>::max();

    for (unsigned i = 0x1F000000; i < 0x1FF00000; ++i)
    {
        double maxAbsError = 0.0;

        for (int j = 1; j <= maxIters; ++j)
        {
            const double baseImpl = (double)std::sqrt((float)j);
            const double testImpl = (double)sqrt_test((float)j, i);

            const double errAbs = ls::math::abs(baseImpl - testImpl);
            const double errRel = 100.0 * (errAbs / ls::math::abs(baseImpl));

            maxAbsError = ls::math::max(maxAbsError, errRel);
        }

        if (maxAbsError < absError)
        {
            absError = maxAbsError;
            magic = i;

            //printf("Magic (%%err=%f): 0x%X\n", absError, magic);
        }
    }

    std::cout << "Magic (%err=" << absError << "): 0x" << std::hex << magic << 'u' << std::endl;
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

    //std::cout << "x, std::sqrt(), math::fast_sqrt(), absolute error, relative error,\n";

    for (int i = 1, j = 0; i <= maxIters; ++i, ++j)
    {
        hr_time t1, t2;

        t1 = chrono::steady_clock::now();
        const float baseImpl = std::sqrt((float)i);
        t2 = chrono::steady_clock::now();
        stdTime += chrono::duration_cast<hr_prec>(t2 - t1).count();

        t1 = chrono::steady_clock::now();
        const float testImpl = ls::math::fast_sqrt<float>((float)i);
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

    //find_magic();

    return 0;
}
