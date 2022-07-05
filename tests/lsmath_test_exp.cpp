
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "lightsky/math/scalar_utils.h"



namespace chrono = std::chrono;
typedef chrono::steady_clock::time_point hr_time;
typedef chrono::nanoseconds hr_prec;



int main()
{
    float minRelError = std::numeric_limits<float>::max();
    float minAbsError = std::numeric_limits<float>::max();
    float maxRelError = std::numeric_limits<float>::min();
    float maxAbsError = std::numeric_limits<float>::min();
    constexpr int maxIters = 88;

    uint64_t stdTime = 0;
    uint64_t lsTime = 0;
    hr_time t1, t2;

    std::cout << "x, std::exp(), math::exp(), absolute error, relative error,\n";

    for (int i = -maxIters; i <= maxIters; ++i)
    {
        //const float testVal = 2.f * (float)i / (float)maxIters;
        const float testVal = (float)i;

        t1 = chrono::steady_clock::now();
        const float baseImpl = std::exp(testVal);
        t2 = chrono::steady_clock::now();
        stdTime += chrono::duration_cast<hr_prec>(t2 - t1).count();

        t1 = chrono::steady_clock::now();
        const float testImpl = ls::math::exp(testVal);
        t2 = chrono::steady_clock::now();
        lsTime += chrono::duration_cast<hr_prec>(t2 - t1).count();

        const float errAbs = ls::math::abs(baseImpl - testImpl);
        const float errRel = 100.f * (errAbs / ls::math::abs(baseImpl));

        minAbsError = ls::math::min(minAbsError, errAbs);
        minRelError = ls::math::min(minRelError, errRel);
        maxAbsError = ls::math::max(maxAbsError, errAbs);
        maxRelError = ls::math::max(maxRelError, errRel);

        std::cout << testVal << ", " << baseImpl << ", " << testImpl << ", " << errAbs << ", " << errRel << ",\n";
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

    return 0;
}
