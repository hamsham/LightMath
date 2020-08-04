
#ifndef LS_MATH_HALF_HPP
#define LS_MATH_HALF_HPP

#include <cstdint> // uint16_t

#include "lightsky/setup/Api.h" // LS_INLINE
#include "lightsky/setup/Arch.h" // LS_ARCH_X86, LS_ARCH_ARM, LS_ARCH_AARCH64
#include "lightsky/setup/Types.h"

#if defined(LS_ARCH_X86)
    extern "C" {
        #include <immintrin.h>
    }
#elif defined(LS_ARCH_AARCH64)
    #include <arm_neon.h>
#elif defined(LS_ARCH_ARM)
    #include <arm_neon.h>
    #include <arm_fp16.h>
#endif

namespace ls
{
namespace math
{



/**
 * @brief The half-float structure provide IEEE-754-compatible 16-bit float
 * functionality.
 *
 * @note Conversion from float-to-half and half-to-float is currently
 * implemented on x86 and ARM platforms using hardware intrinsics. Other
 * platforms use software-based conversion. All arithmetic operations with
 * half-floats are converted and performed as 32-bit float instructions.
 * Because of this, the half-float structure should be used as a storage
 * format only to maintain good performance.
 */
struct alignas(sizeof(uint16_t)) half
{
    uint16_t bits;

    ~half() noexcept = default;

    half() noexcept = default;
    half(const half& h) noexcept = default;
    half(half&& h) noexcept = default;
    half(const float f) noexcept;
    explicit constexpr half(uint8_t hi, uint8_t lo) noexcept;

    half& operator=(const half& h) noexcept = default;
    half& operator=(half&& h) noexcept = default;

    half& operator=(const float f) noexcept;
    operator float() const noexcept;

    inline half& operator++() noexcept;
    inline half& operator--() noexcept;
    inline half operator++(int) noexcept;
    inline half operator--(int) noexcept;

    constexpr bool operator!() const noexcept;
    constexpr bool operator==(const half& f) const noexcept;
    constexpr bool operator!=(const half& f) const noexcept;

    bool operator>=(const half& f) const noexcept;
    bool operator<=(const half& f) const noexcept;
    bool operator>(const half& f) const noexcept;
    bool operator<(const half& f) const noexcept;

    half operator+(const half& f) const noexcept;
    half operator-(const half& f) const noexcept;
    half operator-() const noexcept;
    half operator*(const half& f) const noexcept;
    half operator/(const half& f) const noexcept;

    inline half& operator+=(const half& f) noexcept;
    inline half& operator-=(const half& f) noexcept;
    inline half& operator*=(const half& f) noexcept;
    inline half& operator/=(const half& f) noexcept;
};

static_assert(sizeof(half) == sizeof(uint16_t), "Incorrect size for half-float.");



} // end math namespace



/*----------------------------------------------------------------------------
 * Type Information
----------------------------------------------------------------------------*/
namespace setup
{
/*-------------------------------------
 * Integral Determination
-------------------------------------*/
template <>
struct IsIntegral<ls::math::half> : public ls::setup::FalseType<ls::math::half>
{
};



/*-------------------------------------
 * Float Determination
-------------------------------------*/
template <>
struct IsFloat<ls::math::half> : public ls::setup::TrueType<ls::math::half>
{
};



} // end setup namespace
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



/*-------------------------------------
 * Construct from a bit pattern
-------------------------------------*/
constexpr LS_INLINE half::half(uint8_t hi, uint8_t lo) noexcept :
    bits{(uint16_t)(((uint16_t)hi << (uint16_t)8u) | (uint16_t)lo)}
{}



/*
 * Prefix Increment
 */
inline LS_INLINE half& half::operator++() noexcept
{
    return *this = ((float)*this) + 1.f;
}

/*
 * Prefix Decrement
 */
inline LS_INLINE half& half::operator--() noexcept
{
    return *this = ((float)*this) - 1.f;
}

/*
 * Postfix Increment
 */
inline LS_INLINE half half::operator++(int) noexcept
{
    const half ret = *this;
    *this = ((float)*this) + 1.f;
    return ret;
}

/*
 * Postfix Decrement
 */
inline LS_INLINE half half::operator--(int) noexcept
{
    const half ret = *this;
    *this = ((float)*this) - 1.f;
    return ret;
}

/*
 * Logical NOT
 */
constexpr LS_INLINE bool half::operator!() const noexcept
{
    return !this->bits;
}

/*
 * Logical Equals
 */
constexpr LS_INLINE bool half::operator==(const half& f) const noexcept
{
    return this->bits == f.bits;
}

/*
 * Logical NEQ
 */
constexpr LS_INLINE bool half::operator!=(const half& f) const noexcept
{
    return this->bits != f.bits;
}

/*
 * Greater-Than or Equals
 */
inline LS_INLINE bool half::operator>=(const half& f) const noexcept
{
    return (float)*this >= (float)f;
}

/*
 * Less-Than or Equals
 */
inline LS_INLINE bool half::operator<=(const half& f) const noexcept
{
    return (float)*this <= (float)f;
}

/*
 * Greater-Than
 */
inline LS_INLINE bool half::operator>(const half& f) const noexcept
{
    return (float)*this > (float)f;
}

/*
 * Less-Than
 */
inline LS_INLINE bool half::operator<(const half& f) const noexcept
{
    return (float)*this < (float)f;
}

/*
 * Addition
 */
inline LS_INLINE half half::operator+(const half& f) const noexcept
{
    return half{(float)*this + (float)f};
}

/*
 * Subtraction
 */
inline LS_INLINE half half::operator-(const half& f) const noexcept
{
    return half{(float)*this - (float)f};
}

/*
 * Negation
 */
inline LS_INLINE half half::operator-() const noexcept
{
    return half{-(float)*this};
}

/*
 * Multiplication
 */
inline LS_INLINE half half::operator*(const half& f) const noexcept
{
    return half{(float)*this * (float)f};
}

/*
 * Division
 */
inline LS_INLINE half half::operator/(const half& f) const noexcept
{
    return half{(float)*this / (float)f};
}

/*
 *  Addition
 */
inline LS_INLINE half& half::operator+=(const half& f) noexcept
{
    return *this = (float)*this + (float)f;
}

/*
 * Subtraction
 */
inline LS_INLINE half& half::operator-=(const half& f) noexcept
{
    return *this = (float)*this - (float)f;
}

/*
 * Multiplication
 */
inline LS_INLINE half& half::operator*=(const half& f) noexcept
{
    return *this = (float)*this * (float)f;
}

/*
 * Division
 */
inline LS_INLINE half& half::operator/=(const half& f) noexcept
{
    return *this = (float)*this / (float)f;
}



/*-----------------------------------------------------------------------------
 * Additional helper functions
-----------------------------------------------------------------------------*/
inline LS_INLINE half abs(half x) noexcept
{
    return ((float)x >= 0.f) ? x : -x;
}



} // end math namespace
} // end ls namespace

#endif /* LS_MATH_HALF_HPP */
