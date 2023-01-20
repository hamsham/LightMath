/*
 * File:   math/types.h
 * Author: Miles Lacey
 *
 * This file contains macros which describe globally used math
 * objects/types.
 */

#ifndef LS_MATH_TYPES_H
#define LS_MATH_TYPES_H

#include <cmath>
#include <cstdint>



/*
 * Floating Point Values & Precision
 */
#ifdef LS_MATH_HIGH_PREC

    #define LS_FLOAT        double
    #define LS_INT          int64_t
    #define LS_UINT         uint64_t

    #define LS_ROUND(x)     (std::round((x)))
    #define LS_CEIL(x)      (std::ceil((x)))
    #define LS_FLOOR(x)     (std::floor((x)))
    #define LS_DEG2RAD(x)   ((x) * 0.01745329251994329577) // x * (PI / 180)
    #define LS_RAD2DEG(x)   ((x) * 57.2957795130823208768) // x * (180 / PI)

    #define LS_PI           3.14159265358979323846
    #define LS_TWO_PI       6.28318530717958647693
    #define LS_PI_OVER_2    1.57079632679489661923
    #define LS_PI_OVER_3    1.04719755119659774615
    #define LS_PI_OVER_4    0.78539816339744830962
    #define LS_PI_OVER_6    0.52359877559829887307
    #define LS_PI_INVERSE   0.31830988618379067153 // 1 / pi
    #define LS_E            2.71828182845904523536
    #define LS_EPSILON      1.0e-9

    #define LS_LOG(x)       std::log((x))
    #define LS_LOG2(x)      std::log2((x))
    #define LS_LOG10(x)     std::log10((x))
    #define LS_EXP(x)       std::exp((x))
    #define LS_EXP2(x)      std::exp2((x))
    #define LS_POW(x, y)    std::pow((x), (y))
    #define LS_SIN(x)       std::sin((x))
    #define LS_COS(x)       std::cos((x))
    #define LS_TAN(x)       std::tan((x))
    #define LS_SQRT(x)      std::sqrt((x))

#else /* LS_MATH_HIGH_PREC */

    #define LS_FLOAT        float
    #define LS_INT          int32_t
    #define LS_UINT         uint32_t

    #define LS_ROUND(x)     (ls::math::round((x)))
    #define LS_CEIL(x)      (ls::math::ceil((x)))
    #define LS_FLOOR(x)     (ls::math::floor((x)))
    #define LS_DEG2RAD(x)   ((x) * 0.01745329251994329577f) // x * (PI / 180)
    #define LS_RAD2DEG(x)   ((x) * 57.2957795130823208768f) // x * (180 / PI)

    #define LS_PI           3.14159265358979323846f
    #define LS_TWO_PI       6.28318530717958647693f
    #define LS_PI_OVER_2    1.57079632679489661923f
    #define LS_PI_OVER_3    1.04719755119659774615f
    #define LS_PI_OVER_4    0.78539816339744830962f
    #define LS_PI_OVER_6    0.52359877559829887307f
    #define LS_PI_INVERSE   0.31830988618379067153f // 1 / pi
    #define LS_E            2.71828182845904523536f
    #define LS_EPSILON      1.0e-6f

    #define LS_LOG(x)       ls::math::log((x))
    #define LS_LOG2(x)      ls::math::log2((x))
    #define LS_LOG10(x)     ls::math::log10((x))
    #define LS_EXP(x)       ls::math::exp((x))
    #define LS_EXP2(x)      ls::math::exp2((x))
    #define LS_POW(x, y)    ls::math::pow((x), (y))
    #define LS_SIN(x)       ls::math::sin((x))
    #define LS_COS(x)       ls::math::cos((x))
    #define LS_TAN(x)       ls::math::tan((x))
    #define LS_SQRT(x)      ls::math::fast_sqrt((x))

#endif /* LS_MATH_HIGH_PREC */



#endif /* LS_MATH_TYPES_H */
