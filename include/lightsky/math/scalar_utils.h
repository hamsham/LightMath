/*
 * File:   math/scalar_utils.h
 * Author: Miles Lacey
 *
 * Created on March 6, 2014, 10:04 PM
 */

#ifndef LS_MATH_SCALAR_UTILS_H
#define LS_MATH_SCALAR_UTILS_H

#include <climits> // CHAR_BIT
#include <limits> // std::numeric_limits

#include "lightsky/setup/Arch.h"
#include "lightsky/setup/Types.h"

#include "lightsky/math/Types.h"

namespace ls
{
namespace math
{



/**
 * @brief Calculate the greatest common divisor between two integers.
 *
 * @param a
 * @param b
 *
 * @return The greatest common divisor between a & b.
 */
template <typename scalar_t>
constexpr scalar_t gcd(scalar_t a, scalar_t b) noexcept;

/**
 * @brief min
 * Get the minimum of two single numbers.
 * 
 * This function can be run at compile-time.
 *
 * @param a
 *
 * @param b
 *
 * @return The smallest of the two parameters a and b.
 */
template <typename scalar_t>
constexpr scalar_t min(scalar_t a, scalar_t b) noexcept;

/**
 * @brief min
 * Get the minimum of two or more numbers.
 * 
 * This function can be run at compile-time.
 *
 * @param a
 *
 * @param b
 * 
 * @param nums
 *
 * @return The smallest number of the input parameters.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t min(const scalar_t& a, const scalar_t& b, const scalars_t&... nums) noexcept;

/**
 * @brief mix
 * Perform a linear interpolation of x between the two scalars a, b.
 * 
 * @param a
 * 
 * @param b
 *
 * @return The linear "mix" of a and b.
 */
template <typename scalar_t>
constexpr scalar_t mix(scalar_t a, scalar_t b, scalar_t percent) noexcept;

/**
 * @brief max
 * Get the maximum of two single numbers.
 * This function can be run at compile-time.
 *
 * @param a
 *
 * @param b
 *
 * @return The largest number of the two parameters a and b.
 */
template <typename scalar_t>
constexpr scalar_t max(scalar_t a, scalar_t b) noexcept;

/**
 * @brief max
 * Get the maximum of two or more numbers.
 * 
 * This function can be run at compile-time.
 *
 * @param a
 *
 * @param b
 * 
 * @param nums
 *
 * @return The largest number of the input parameters.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t max(const scalar_t& a, const scalar_t& b, const scalars_t&... nums) noexcept;

/**
 * @brief clamp
 * Bind a number to within a certain range.
 *
 * @param n
 * A number that should be constrained to be within a specific range.
 *
 * @param minVal
 * The minimum allowable value that 'n' can be.
 *
 * @param maxVal
 * The maximum allowable value that 'n' can be.
 *
 * @return a number, such that minVal <= n <= maxVal
 */
template <typename scalar_t>
constexpr scalar_t clamp(scalar_t n, scalar_t minVal, scalar_t maxVal) noexcept;

/**
 * @brief Retrieve the nearest integer less than or equal to the input float.
 *
 * @param n
 * A floating-point number.
 *
 * @return A value equal to the nearest integer that is less than or equal to
 * the input parameter.
 */
template <typename floating_t>
constexpr floating_t floor(const floating_t n) noexcept;

/**
 * @brief Retrieve the nearest integer less than or equal to the input float.
 * This overload assumes compile-time knowledge of the range of numbers that a
 * float should reside within.
 *
 * @param n
 * A floating-point number.
 *
 * @return A value equal to the nearest integer that is less than or equal to
 * the input parameter.
 */
template <typename floating_t, typename int_t, int_t range>
constexpr int_t ranged_floor(const floating_t n) noexcept;

/**
 * @brief Retrieve the nearest integer greater than or equal to the input
 * float.
 *
 * @param n
 * A floating-point number.
 *
 * @return A value equal to the nearest integer that is greater than or equal
 * to the input parameter.
 */
template <typename floating_t>
constexpr floating_t ceil(const floating_t n) noexcept;

/**
 * @brief Retrieve the nearest integer greater than or equal to the input
 * float. This overload assumes compile-time knowledge of the range of numbers
 * that a float should reside within.
 *
 * @param n
 * A floating-point number.
 *
 * @return A value equal to the nearest integer that is less than or equal to
 * the input parameter.
 */
template <typename floating_t, typename int_t, int_t range>
constexpr int_t ranged_ceil(const floating_t n) noexcept;

/**
 * @brief Calculate the nearest integer closest to the input parameter.
 *
 * @param n
 * A floating-point number.
 *
 * @return A value equal to the nearest integer to the input parameter.
 */
template <typename floating_t>
constexpr floating_t round(const floating_t n) noexcept;

/**
 * @brief fract
 * Compute the fractional part of a floating-point number.
 *
 * @param n
 * A floating-point number.
 *
 * @return The fractional part of the input float. This is calculated as
 * "x - floor(x)".
 */
template <typename floating_t>
constexpr floating_t fract(const floating_t n) noexcept;

/**
 * @brief fmod
 * Compute remainder of the division of one floating-point number by another.
 *
 * @param n1
 * The dividend.
 *
 * @param n2
 * The divisor.
 *
 * @return The remainder of the division between n1 / n2.
 */
template <typename floating_t>
constexpr floating_t fmod(const floating_t n1, const floating_t n2) noexcept;

/**
 * @brief fmod_1
 * Compute remainder of the division of one floating-point number by 1.
 *
 * @param n
 * The dividend.
 *
 * @return The remainder of the division between n1 / 1.0.
 */
template <typename floating_t>
constexpr floating_t fmod_1(const floating_t n) noexcept;

/**
 * @brief step
 * Generate a step function by comparing two values.
 *
 * step() generates a step function by comparing x to edge. For the return
 * value, 0.0 is returned if x < edge, and 1.0 is returned otherwise.
 *
 * @param edge
 * Specifies the location of the edge of the step function.
 *
 * @param x
 * Specify the value to be used to generate the step function.
 *
 * @return A step function between two values.
 */
template <typename floating_t>
constexpr floating_t step(floating_t edge, floating_t x) noexcept;

/**
 * @brief smoothstep
 * Perform a smooth interpolation of a number along the sub-sequence [a, b].
 *
 * @param a
 * A number within the same sub-sequence that x lies on.
 *
 * @param b
 * A number within the same sub-sequence that x lies on.
 *
 * @return The smooth linear interpolation of x in between the interval a and b.
 */
template <typename floating_t>
constexpr floating_t smoothstep(floating_t a, floating_t b, floating_t x) noexcept;

/**
 * @brief fastSqrt
 * Perform a square root on a single number without using the standard library.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 *
 * @param a number whose square root should be obtained.
 *
 * @return The square root of the input number.
 */
template <typename scalar_t>
inline scalar_t fast_sqrt(typename setup::EnableIf<setup::IsIntegral<scalar_t>::value, scalar_t>::type) noexcept;

template <typename scalar_t>
inline scalar_t fast_sqrt(scalar_t) noexcept;

/**
 * @brief fastInvSqrt
 * Get the inverse square root of a number.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 *
 * @param a number whose square root should be obtained.
 *
 * @return The inverse square root (1/sqrt(x)) of the input number.
 */
template <typename scalar_t>
inline scalar_t inversesqrt(scalar_t) noexcept;

/**
 * @brief Convert a number from degrees to radians. This function can be run at
 * compile-time.
 *
 * @param the value of an angle, in degrees.
 *
 * @return the value of an angle, in radians.
 */
template <typename scalar_t>
constexpr scalar_t radians(scalar_t degrees) noexcept;

/**
 * @brief Convert a number from radians to degrees. This function can be run at
 * compile-time.
 *
 * @param the value of an angle, in radians.
 *
 * @return the value of an angle, in degrees.
 */
template <typename scalar_t>
constexpr scalar_t degrees(scalar_t radians) noexcept;

/**
 * @brief Compute the modulus of num%denom only when necessary.
 *
 * This method only works with positive integers.
 *
 * @param num
 * Numerator
 *
 * @param denom
 * Denominator
 *
 * @return num % denom
 */
template <typename integral_t>
constexpr integral_t fast_mod(const integral_t num, const integral_t denom) noexcept;

/**
 * @brief log2
 * Calculate the log-base2 of a number
 *
 * @param a number
 *
 * @return the log-base2 of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t log2(scalar_t n) noexcept;

/**
 * @brief log2
 * Calculate the log-base2 of a number
 *
 * @param a number
 *
 * @return the log-base2 of a number, using IEEE floating point arithmetic
 */
template <>
inline float log2<float>(float) noexcept;

/**
 * @brief log
 * Calculate the natural log of a number
 *
 * @param a number
 *
 * @return ln(x), using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t log(scalar_t) noexcept;

/**
 * @brief log10
 * Calculate the log-base2 of a number
 *
 * @param a number
 *
 * @return the log-base-10 of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t log10(scalar_t) noexcept;

/**
 * @brief log10
 * Calculate the log-base2 of a number
 *
 * @param a number
 *
 * @return the log-base-10 of a number, using IEEE floating point arithmetic
 */
template <>
inline float log10<float>(float) noexcept;

/**
 * @brief logN
 * Calculate the log-base2 of a number
 *
 * @param baseN
 * The base of the logarithm.
 *
 * @param a number
 *
 * @return the log-baseN of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t logN(scalar_t baseN, scalar_t) noexcept;

/**
 * @brief next_pow2
 * Find the next (greater) power of two that is closest to the value of a number
 *
 * @param An unsigned integral type
 *
 * @return The current or next greatest power of two.
 */
inline uint8_t  next_pow2(uint8_t) noexcept;
inline uint16_t next_pow2(uint16_t) noexcept;
inline uint32_t next_pow2(uint32_t) noexcept;
inline uint64_t next_pow2(uint64_t) noexcept;

/**
 * @brief next_pow2
 * Find the next (greater) power of two that is closest to the value of a number
 *
 * @param A signed integral type
 *
 * @return The current or next greatest power of two.
 */
inline int8_t  next_pow2(int8_t) noexcept;
inline int16_t next_pow2(int16_t) noexcept;
inline int32_t next_pow2(int32_t) noexcept;
inline int64_t next_pow2(int64_t) noexcept;

/**
 * @brief prev_pow2
 * Find the previous (lesser) power of two that is closest to the value of a number
 *
 * @param An unsigned integral type
 *
 * @return The previous power of two.
 */
inline uint8_t  prev_pow2(uint8_t) noexcept;
inline uint16_t prev_pow2(uint16_t) noexcept;
inline uint32_t prev_pow2(uint32_t) noexcept;
inline uint64_t prev_pow2(uint64_t) noexcept;

/**
 * @brief prev_pow2
 * Find the previous (lesser) power of two that is closest to the value of a
 * number.
 *
 * @param A signed integral type
 *
 * @return The previous power of two.
 */
inline int8_t  prev_pow2(int8_t) noexcept;
inline int16_t prev_pow2(int16_t) noexcept;
inline int32_t prev_pow2(int32_t) noexcept;
inline int64_t prev_pow2(int64_t) noexcept;

/**
 * @brief nearest_pow2
 * Find the closest power of two to a number. This may either be greater than
 * or less than the input number.
 *
 * @param A signed integral type
 *
 * @return The current or closest power of two to a number.
 */
template <typename data_t>
inline data_t nearest_pow2(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type) noexcept;

/**
 * @brief is_pow2
 * Determine if a number is a power of two or not.
 *
 * @param A number who's value should be evaluated.
 *
 * @return True if the number is a poiwer of two, false if the number is not a
 * power of two.
 */
template <typename data_t>
constexpr bool is_pow2(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type n) noexcept;

/**
 * @brief factorial
 * Retrieve the factorial of a number
 *
 * @param A number who's factorial is to be calculated.
 *
 * @return The factorial of a given number.
 */
template <typename scalar_t>
constexpr scalar_t factorial(scalar_t) noexcept;

/**
 * @brief pow
 * Evaluate a number to a given power.
 *
 * This function's implmentation will be defined at compile-time for integers
 * and floats.
 *
 * @param x
 *
 * @param y
 *
 * @return x^y
 */
template <typename scalar_t>
constexpr scalar_t pow(
    typename setup::EnableIf<setup::IsIntegral<scalar_t>::value, scalar_t>::type x,
    typename setup::EnableIf<setup::IsIntegral<scalar_t>::value, scalar_t>::type y) noexcept;

template <typename scalar_t>
inline scalar_t pow(scalar_t x, scalar_t y) noexcept;

/**
 * @brief exp
 * Evaluate the exponentiation of e^x.
 *
 * @param x
 * The power X to which e will be raised by.
 *
 * @return E, raised to the power x.
 */
template <typename scalar_t>
inline scalar_t exp(scalar_t x) noexcept;


/**
 * @brief exp2
 * Evaluate the exponentiation of 2^x.
 *
 * @param x
 * The power X to which 2 will be raised by.
 *
 * @return 2, raised to the power x.
 */
template <typename scalar_t>
inline scalar_t exp2(scalar_t x) noexcept;

/**
 * @brief sin
 * Evaluate the sine of an angle at compile-time.
 *
 * @param An angle, in radians, who's sine value is to be calculated.
 *
 * @return The sine of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t sin(typename setup::EnableIf<setup::IsFloat<scalar_t>::value, scalar_t>::type x) noexcept;

template <typename scalar_t>
constexpr scalar_t sin(scalar_t) noexcept;

/**
 * @brief cos
 * Evaluate the cosine of an angle at compile-time.
 *
 * @param An angle, in radians, who's cosine value is to be calculated.
 *
 * @return The cosine of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t cos(typename setup::EnableIf<setup::IsFloat<scalar_t>::value, scalar_t>::type x) noexcept;

template <typename scalar_t>
constexpr scalar_t cos(scalar_t) noexcept;

/**
 * @brief tan
 * Evaluate the tangent of an angle at compile-time.
 *
 * @param An angle, in radians, who's tangent value is to be calculated.
 *
 * @return The tangent of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t tan(scalar_t) noexcept;

/**
 * @brief rcp
 * Evaluate the reciprocal of a decimal scalar.
 *
 * @note This function does not check for division-by-zero.
 *
 * @param The value to be evaluated.
 *
 * @return A reciprocal estimate of the input number.
 */
template <typename scalar_t>
constexpr scalar_t rcp(const scalar_t&) noexcept;

/**
 * @brief sum
 * Evaluate the sum of a series of numbers at compile-time.
 *
 * @param A set of numbers who's values are to be added together.
 *
 * @return The sum of a set of numbers.
 */
template <typename scalar_t>
constexpr scalar_t sum(const scalar_t&) noexcept;

/**
 * @brief sum
 * Evaluate the sum of a series of numbers at compile-time.
 *
 * @param A set of numbers who's values are to be added together.
 *
 * @return The sum of a set of numbers.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t sum(const scalar_t& num, const scalars_t&... nums) noexcept;

/**
 * @brief reciprocal sum
 * Evaluate the reciprocal of a sum.
 *
 * @param A set of numbers who's values are to be added together.
 *
 * @return The inverse of a sequence sum.
 */
template <typename scalar_t>
constexpr scalar_t sum_inv(const scalar_t&) noexcept;

/**
 * @brief reciprocal sum
 * Evaluate the reciprocal of a sum.
 *
 * @param A set of numbers who's values are to be added together.
 *
 * @return The inverse of a sequence sum.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t sum_inv(const scalar_t& num, const scalars_t&... nums) noexcept;

/**
 * @brief average
 * Evaluate the average of a series of numbers at compile-time.
 *
 * @param A set of numbers who's values are to be averaged.
 *
 * @return The average of a set of numbers.
 */
template <typename scalar_t>
constexpr scalar_t average() noexcept;

/**
 * @brief average
 * Evaluate the average of a series of numbers at compile-time.
 *
 * @param A set of numbers who's values are to be averaged.
 *
 * @return The average of a set of numbers.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t average(const scalar_t& num, const scalars_t&... nums) noexcept;

/**
 * @brief Count the number of bits in an integer.
 *
 * @param num
 * A number containing a string of set bits.
 *
 * @return A count of all the set bits in an integer.
 */
constexpr unsigned count_set_bits(const unsigned long long num) noexcept;

/**
 * @brief Count the number of bits in an integer.
 *
 * This version of the bit-count algorithm casts the input type into the
 * largest possible integral data type available (currently unsigned long
 * long). This means that negative values may return a very large value on a
 * two's complement machine.
 *
 * This also means that passing a value of -1 into the function will return the
 * maximum allowable number of bits available for storage on the current CPU.
 *
 * @param num
 * A number containing a string of set bits.
 *
 * @return A count of all the set bits in an integer.
 */
template <typename scalar_t>
constexpr unsigned count_set_bits(const scalar_t num) noexcept;

/**
 * @brief Scale a number from one data type with a range of values to another
 * data type with a range of values.
 *
 * @param num
 * A number which will be linearly scaled from one numerical range to another.
 *
 * @param oldMin
 * The minimum value of the input number's current range of valid values.
 *
 * @param oldMax
 * The maximum value of the input number's current range of valid values.
 *
 * @param newMin
 * The minimum number by which the input number should be scaled to represent.
 *
 * @param newMax
 * The maximum number by which the input number should be scaled to represent.
 *
 * @return The input number, linearly scaled from one numerical range to
 * another.
 */
template <typename in_type, typename out_type>
constexpr out_type scale_to_range(
    const in_type num,
    const out_type oldMin = std::numeric_limits<in_type>::min(),
    const out_type oldMax = std::numeric_limits<in_type>::max(),
    const out_type newMin = std::numeric_limits<out_type>::min(),
    const out_type newMax = std::numeric_limits<out_type>::max()
) noexcept;

/**
 * @brief Retrieve the sign bits of a scalar type.
 *
 * @param x
 * The number to be queried.
 *
 * @returns 1 if the sign bit is set, 0 if x is greater than, or equal to zero.
 */
template <typename data_t>
constexpr int sign_mask(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type) noexcept;

template <typename data_t>
constexpr int sign_mask(data_t x) noexcept;

/**
 * @brief Determine if the sign-bit is set.
 *
 * @param x
 * The number to be queried.
 *
 * @returns 1 if the sign bit is set, 0 if x is greater than, or equal to zero.
 */
template <typename data_t>
constexpr data_t sign(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type) noexcept;

template <typename data_t>
constexpr data_t sign(data_t x) noexcept;

/**
 * @brief Retrieve the absolute value of a number
 *
 * @param x
 *
 * @return A number without the sign bit set.
 */
template <typename data_t>
constexpr data_t abs(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type) noexcept;

template <typename data_t>
constexpr data_t abs(data_t x) noexcept;

/**
 * @brief Perform a fused multiply-and-add calculation
 *
 * @param x
 * An initial operand.
 *
 * @param m
 * A number which will be multiplied against 'x'.
 *
 * @param a
 * The final operand which will be added to 'x*m'.
 *
 * @return (x*m)+a
 */
template <typename data_t>
constexpr data_t fmadd(data_t x, data_t m, data_t a) noexcept;

/**
 * @brief Perform a fused multiply-and-subtract calculation
 *
 * @param x
 * An initial operand.
 *
 * @param m
 * A number which will be multiplied against 'x'.
 *
 * @param a
 * The final operand which will be subtracted from 'x*m'.
 *
 * @return (x*m)-a
 */
template <typename data_t>
constexpr data_t fmsub(data_t x, data_t m, data_t a) noexcept;



} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/scalar_utils_impl.h"

#ifdef LS_ARCH_X86
    #include "lightsky/math/x86/scalarf_utils_impl.h"
#elif defined(LS_ARCH_ARM)
    #include "lightsky/math/arm/scalarf_utils_impl.h"
#endif

#endif /* LS_MATH_SCALAR_UTILS_H */
