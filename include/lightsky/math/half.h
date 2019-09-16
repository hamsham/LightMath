
#ifndef LS_MATH_HALF_HPP
#define LS_MATH_HALF_HPP

#include <cstdint> // uint16_t

#include "lightsky/setup/Arch.h" // LS_ARCH_X86, LS_ARCH_ARM, LS_ARCH_AARCH64
#include "lightsky/setup/Api.h" // LS_INLINE

#if defined(LS_ARCH_X86)
    #include <immintrin.h>
#elif defined(LS_ARCH_ARM) || defined(LS_ARCH_AARCH64)
    #include <arm_neon.h>
#endif

#include "lightsky/math/Types.h"

namespace ls
{
namespace math
{



/**
 * @brief The Half-float structure is simply a storage format for 16-bit
 * floating-point numbers.
 *
 * In ARM and x86 hardware, 16-bit floats are  also treated as a storage
 * format, converting to single-precision floats for miscellaneous operations.
 * I have tried to adapt to this while still providing support for standard
 * floating-point operations.
 */
struct alignas(sizeof(uint16_t)) Half
{
    uint16_t bits;

    ~Half() noexcept = default;

    Half() noexcept = default;
    Half(const Half& h) noexcept = default;
    Half(Half&& h) noexcept = default;
    Half(const float f) noexcept;

    Half& operator=(const Half& h) noexcept = default;
    Half& operator=(Half&& h) noexcept = default;

    Half& operator=(const float f) noexcept;
    operator float() const noexcept;

    inline Half& operator++() noexcept;
    inline Half& operator--() noexcept;
    inline Half operator++(int) noexcept;
    inline Half operator--(int) noexcept;

    constexpr bool operator!() const noexcept;
    constexpr bool operator==(const Half& f) const noexcept;
    constexpr bool operator!=(const Half& f) const noexcept;

    bool operator>=(const Half& f) const noexcept;
    bool operator<=(const Half& f) const noexcept;
    bool operator>(const Half& f) const noexcept;
    bool operator<(const Half& f) const noexcept;

    Half operator+(const Half& f) const noexcept;
    Half operator-(const Half& f) const noexcept;
    Half operator-() const noexcept;
    Half operator*(const Half& f) const noexcept;
    Half operator/(const Half& f) const noexcept;

    inline Half& operator+=(const Half& f) noexcept;
    inline Half& operator-=(const Half& f) noexcept;
    inline Half& operator*=(const Half& f) noexcept;
    inline Half& operator/=(const Half& f) noexcept;
};



/*----------------------------------------------------------------------------
 * Type Information
----------------------------------------------------------------------------*/
/*-------------------------------------
 * Integral Determination
-------------------------------------*/
template <>
struct IsIntegral<Half> : public utils::FalseType<Half>
{
};



/*-------------------------------------
 * Float Determination
-------------------------------------*/
template <>
struct IsFloat<Half> : public utils::TrueType<Half>
{
};



} // end math namespace
} // end ls namespace



/*-----------------------------------------------------------------------------
 * Platform-specific methods needed for inlining
-----------------------------------------------------------------------------*/
#if defined(LS_ARCH_X86) && !defined(LS_COMPILER_MSC) // :-(
    #include "lightsky/math/x86/half_impl.h"
#elif defined(LS_ARCH_ARM) || defined(LS_ARCH_AARCH64)
    #include "lightsky/math/arm/half_impl.h"
#else
    #include "lightsky/math/generic/half_impl.h"
#endif



/*-----------------------------------------------------------------------------
 * Method Implementations
-----------------------------------------------------------------------------*/
namespace ls
{
namespace math
{



/*
 * Prefix Increment
 */
inline LS_INLINE Half& Half::operator++() noexcept
{
    return *this = ((float)*this) + 1.f;
}

/*
 * Prefix Decrement
 */
inline LS_INLINE Half& Half::operator--() noexcept
{
    return *this = ((float)*this) - 1.f;
}

/*
 * Postfix Increment
 */
inline LS_INLINE Half Half::operator++(int) noexcept
{
    const Half ret = *this;
    *this = ((float)*this) + 1.f;
    return ret;
}

/*
 * Postfix Decrement
 */
inline LS_INLINE Half Half::operator--(int) noexcept
{
    const Half ret = *this;
    *this = ((float)*this) - 1.f;
    return ret;
}

/*
 * Logical NOT
 */
constexpr LS_INLINE bool Half::operator!() const noexcept
{
    return !this->bits;
}

/*
 * Logical Equals
 */
constexpr LS_INLINE bool Half::operator==(const Half& f) const noexcept
{
    return this->bits == f.bits;
}

/*
 * Logical NEQ
 */
constexpr LS_INLINE bool Half::operator!=(const Half& f) const noexcept
{
    return this->bits != f.bits;
}

/*
 * Greater-Than or Equals
 */
inline LS_INLINE bool Half::operator>=(const Half& f) const noexcept
{
    return (float)*this >= (float)f;
}

/*
 * Less-Than or Equals
 */
inline LS_INLINE bool Half::operator<=(const Half& f) const noexcept
{
    return (float)*this <= (float)f;
}

/*
 * Greater-Than
 */
inline LS_INLINE bool Half::operator>(const Half& f) const noexcept
{
    return (float)*this > (float)f;
}

/*
 * Less-Than
 */
inline LS_INLINE bool Half::operator<(const Half& f) const noexcept
{
    return (float)*this < (float)f;
}

/*
 * Addition
 */
inline LS_INLINE Half Half::operator+(const Half& f) const noexcept
{
    return Half{(float)*this + (float)f};
}

/*
 * Subtraction
 */
inline LS_INLINE Half Half::operator-(const Half& f) const noexcept
{
    return Half{(float)*this - (float)f};
}

/*
 * Negation
 */
inline LS_INLINE Half Half::operator-() const noexcept
{
    return Half{-(float)*this};
}

/*
 * Multiplication
 */
inline LS_INLINE Half Half::operator*(const Half& f) const noexcept
{
    return Half{(float)*this * (float)f};
}

/*
 * Division
 */
inline LS_INLINE Half Half::operator/(const Half& f) const noexcept
{
    return Half{(float)*this / (float)f};
}

/*
 *  Addition
 */
inline LS_INLINE Half& Half::operator+=(const Half& f) noexcept
{
    return *this = (float)*this + (float)f;
}

/*
 * Subtraction
 */
inline LS_INLINE Half& Half::operator-=(const Half& f) noexcept
{
    return *this = (float)*this - (float)f;
}

/*
 * Multiplication
 */
inline LS_INLINE Half& Half::operator*=(const Half& f) noexcept
{
    return *this = (float)*this * (float)f;
}

/*
 * Division
 */
inline LS_INLINE Half& Half::operator/=(const Half& f) noexcept
{
    return *this = (float)*this / (float)f;
}



} // end math namespace
} // end ls namespace

#endif /* LS_MATH_HALF_HPP */
