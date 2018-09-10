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

    #define LS_ROUND(x)     (std::floor(0.5 + x))
    #define LS_DEG2RAD(x)   (x * 0.01745329251994329577) // x * (PI / 180)
    #define LS_RAD2DEG(x)   (x * 57.2957795130823208768) // x * (180 / PI)

    #define LS_PI           3.14159265358979323846
    #define LS_TWO_PI       6.28318530717958647693
    #define LS_PI_OVER_2    1.57079632679489661923
    #define LS_PI_OVER_3    1.04719755119659774615
    #define LS_PI_OVER_4    0.78539816339744830962
    #define LS_PI_OVER_6    0.52359877559829887307
    #define LS_PI_INVERSE   0.31830988618379067153 // 1 / pi
    #define LS_E            2.71828182845904523536
    #define LS_EPSILON      1.0e-9

    #define LS_SIN(x)       sin(x)
    #define LS_COS(x)       cos(x)
    #define LS_TAN(x)       tan(x)
    #define LS_SQRT(x)      sqrt(x)
#else /* LS_MATH_HIGH_PREC */
    #define LS_FLOAT        float
    #define LS_INT          int32_t
    #define LS_UINT         uint32_t

    #define LS_ROUND(x)     (std::floor(0.5f + x))
    #define LS_DEG2RAD(x)   (x * 0.01745329251994329577f) // x * (PI / 180)
    #define LS_RAD2DEG(x)   (x * 57.2957795130823208768f) // x * (180 / PI)

    #define LS_PI           3.14159265358979323846f
    #define LS_TWO_PI       6.28318530717958647693f
    #define LS_PI_OVER_2    1.57079632679489661923f
    #define LS_PI_OVER_3    1.04719755119659774615f
    #define LS_PI_OVER_4    0.78539816339744830962f
    #define LS_PI_OVER_6    0.52359877559829887307f
    #define LS_PI_INVERSE   0.31830988618379067153f // 1 / pi
    #define LS_E            2.71828182845904523536f
    #define LS_EPSILON      1.0e-6f

    #define LS_SIN(x)       sinf(x)
    #define LS_COS(x)       cosf(x)
    #define LS_TAN(x)       tanf(x)
    #define LS_SQRT(x)      ls::math::fast_sqrt(x)
#endif /* LS_MATH_HIGH_PREC */



namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
 * Replacement for std::is_integral
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Integer Specialization
-------------------------------------*/
template <typename data_t>
struct IsIntegral
{
    typedef data_t value_type;

    static constexpr bool value = true;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Float Specialization
-------------------------------------*/
template <>
struct IsIntegral<float>
{
    typedef float value_type;

    static constexpr bool value = false;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Double Specialization
-------------------------------------*/
template <>
struct IsIntegral<double>
{
    typedef double value_type;

    static constexpr bool value = false;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Long Double Specialization
-------------------------------------*/
template <>
struct IsIntegral<long double>
{
    typedef long double value_type;

    static constexpr bool value = false;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Boolean Cast Implementation
-------------------------------------*/
template <typename data_t>
constexpr IsIntegral<data_t>::operator bool() const noexcept
{
    return IsIntegral<data_t>::value;
}



/*-------------------------------------
 * Functor Call Implementation
-------------------------------------*/
template <typename data_t>
constexpr bool IsIntegral<data_t>::operator() () const noexcept
{
    return IsIntegral<data_t>::value;
}



/*-----------------------------------------------------------------------------
 * Replacement for std::is_floating_point
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Float Specialization
-------------------------------------*/
template <typename data_t>
struct IsFloat
{
    typedef data_t value_type;

    static constexpr bool value = false;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Float Specialization
-------------------------------------*/
template <>
struct IsFloat<float>
{
    typedef float value_type;

    static constexpr bool value = true;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Double Specialization
-------------------------------------*/
template <>
struct IsFloat<double>
{
    typedef double value_type;

    static constexpr bool value = true;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Long Double Specialization
-------------------------------------*/
template <>
struct IsFloat<long double>
{
    typedef long double value_type;

    static constexpr bool value = true;

    constexpr explicit operator bool() const noexcept;

    constexpr bool operator() () const noexcept;
};



/*-------------------------------------
 * Boolean Cast Implementation
-------------------------------------*/
template <typename data_t>
constexpr IsFloat<data_t>::operator bool() const noexcept
{
    return IsFloat<data_t>::value;
}



/*-------------------------------------
 * Functor Call Implementation
-------------------------------------*/
template <typename data_t>
constexpr bool IsFloat<data_t>::operator() () const noexcept
{
    return IsFloat<data_t>::value;
}


} // end math namespace
} // end ls namespace

#endif /* LS_MATH_TYPES_H */
