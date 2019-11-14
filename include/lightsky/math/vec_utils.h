/*
 * File:   math/vec_utils.h
 * Author: Miles Lacey
 *
 * Created on January 8, 2013, 3:14 PM
 */

#ifndef LS_MATH_VEC_UTILS_H
#define LS_MATH_VEC_UTILS_H

#include "lightsky/setup/Arch.h"
#include "lightsky/setup/Compiler.h"

 // MSVC defines its own min/max functions.
#ifdef LS_COMPILER_MSC
    #ifdef min
        #undef min
    #endif /* min */

    #ifdef max
        #undef max
    #endif /* max */
#endif /* LS_COMPILER_MSC */

#include "lightsky/math/Types.h"
#include "lightsky/math/scalar_utils.h"

#include "lightsky/math/vec2.h"
#include "lightsky/math/vec3.h"
#include "lightsky/math/vec4.h"

namespace ls {
namespace math {

/*-----------------------------------------------------------------------------
    2D Vectors
-----------------------------------------------------------------------------*/
/**
 *  @brief sum
 *  Retrieve the sum of all components in a 2D vector.
 *
 *  @param v
 *
 *  @return the sum of elements within v.
 */
template <typename N> constexpr
N sum(const vec2_t<N>& v);

/**
 *  @brief reciprocal sum
 *  Retrieve the reciprocal of the sum sum of all vector elements.
 *
 *  @param v
 *
 *  @return the reciprocal of the sum of elements within v.
 */
template <typename N> constexpr
N sum_inv(const vec2_t<N>& v);

/**
 *  @brief dot
 *  Retrieve the dot product of a 2D vector.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return the 2D dot product of v1 & v2.
 */
template <typename N> constexpr
N dot(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief cross
 *  Retrieve the cross product of two 2D vectors.
 *  This method was developed my Allen Chou:
 *      http://allenchou.net/2013/07/cross-product-of-2d-vectors/
 *  This is useful in determining if the second vector is on the left or right
 *  side of the first.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return a scalar which can determine if v2 is on the left or right side of
 *  v1. If the returned value is positive, v2 is on the left of v1, if it's
 *  negative, v2 is on the right of v1.
 */
template <typename N> constexpr
N cross(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief normalize
 *  Normalize the vector v so that its points lie within a unit-sphere.
 *
 *  @param v
 *
 *  @return a normalized 2D vector.
 */
template <typename N> inline
vec2_t<N> normalize(const vec2_t<N>& v);

/**
 *  @brief lengthSquared
 *  Retrieve the square of the length/magnitude of a 2D vector. This is faster
 *  than calling length() as no square roots are performed.
 *
 *  @param v
 *  A 2D vector.
 *
 *  @return The square of the length/magnitude of a 2D vector.
 */
template <typename N> constexpr
N length_squared(const vec2_t<N>& v);

/**
 *  @brief length
 *  Retrieve the length/magnitude of a 2D vector.
 *
 *  @param v
 *  A 2D vector.
 *
 *  @return The length/magnitude of a 2D vector.
 */
template <typename N> inline
N length(const vec2_t<N>& v);

/**
 *  @brief rotate
 *  Rotate a 2D vector by a number of radians.
 *
 *  @param v
 *  A 2D vector that is to be rotated.
 *
 *  @param angle
 *  The number of radians that a 2D vector is to be rotated by.
 *
 *  @return A rotated 2D vector.
 */
template <typename N> inline
vec2_t<N> rotate(const vec2_t<N>& v, N angle);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two 2D vectors placed around the origin
 *  of the Cartesian coordinate plane.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angle_between(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two points in 2D space, with a
 *  specified origin.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @param origin
 *  The point in 2D space that two points use as their origin.
 *
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angle_between(const vec2_t<N>& v1, const vec2_t<N>& v2, const vec2_t<N>& origin);

/**
 *  @brief min
 *  Retrieve the component-wise minimum of two vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A vector with the minimum X/Y values extracted from either of the
 *  input vectors.
 */
template <typename N> constexpr
vec2_t<N> min(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief mix
 *  Retrieve the linear interpolation of one vector towards another, moved by
 *  a certain percentage.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @param percent
 *  The percentage (clamped from [0, 1]) to which v2 should be interpolated
 *  towards v2.
 *
 *  @return An interpolated vector value between v1 and v2, according to the
 *  percentage N.
 */
template <typename N> constexpr
vec2_t<N> mix(const vec2_t<N>& v1, const vec2_t<N>& v2, N percent);

/**
 *  @brief max
 *  Retrieve the component-wise maximum of two vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A vector with the maximum X/Y values extracted from either of the
 *  input vectors.
 */
template <typename N> constexpr
vec2_t<N> max(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief project
 *  Project one vector onto another and retrieve the result.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return The vector projection of v1 onto v2.
 */
template <typename N> inline
vec2_t<N> project(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief reflect
 *  Reflect a vector v around a normal vector.
 *
 *  @param v
 *
 *  @param norm
 *  The normal vector from which v will be reflected.
 *
 *  @return
 *  The reflection of v around the normal vector 'norm'.
 */
template <typename N> constexpr
vec2_t<N> reflect(const vec2_t<N>& v, const vec2_t<N>& norm);

/**
 *  @brief mid
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return the midpoint between v1 and v2.
 */
template <typename N> constexpr
vec2_t<N> mid(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief rcp
 *
 *  Estimate the reciprocal of all elements in the input vector.
 *
 *  @param v
 *
 *  @return the element-wise reciprocal between v.
 */
template <typename N> constexpr
vec2_t<N> rcp(const vec2_t<N>& v);

/**
 * @brief Retrieve the sign bits of a vector type.
 *
 * @param x
 * The number to be queried.
 *
 * @returns A value of 1 in each of the lower 2 bits of the return value if
 * the signs are set.
 */
template <typename N> constexpr
int sign_mask(const vec2_t<N>& x) noexcept;

/**
 * @brief Retrieve the component-wise signs of a vector type.
 *
 * @param x
 * The number to be queried.
 *
 * @returns A value of 1 in each of component of the return value if the sign
 * within x are set.
 */
template <typename N> constexpr
vec2_t<N> sign(const vec2_t<N>& x) noexcept;

/**
 *  @brief floor
 *
 *  Calculate the floating-point floor of all vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded down to the nearest integer.
 */
template <typename N> constexpr
vec2_t<N> floor(const vec2_t<N>& v);

/**
 *  @brief ceil
 *
 *  Calculate the floating-point ceiling of all vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded up to the nearest integer.
 */
template <typename N> constexpr
vec2_t<N> ceil(const vec2_t<N>& v);

/**
 *  @brief round
 *
 *  Round all floating-point vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded to the nearest integer.
 */
template <typename N> constexpr
vec2_t<N> round(const vec2_t<N>& v);

/**
 * @brief log2
 * Calculate the log-base2 of a vector
 *
 * @param a vector
 *
 * @return A vector with the log-base2 of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec2_t<N> log2(const vec2_t<N>& n) noexcept;

/**
 * @brief fastLog
 * Calculate the natural log of a vector
 *
 * @param a vector
 *
 * @return ln(vec2), using IEEE floating point arithmetic
 */
template <typename N>
inline vec2_t<N> log(const vec2_t<N>&) noexcept;

/**
 * @brief log2
 * Calculate the log-base2 of a vector
 *
 * @param a vector
 *
 * @return A vector with the log-base2 of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec2_t<N> log10(const vec2_t<N>&) noexcept;

/**
 * @brief logN
 * Calculate the log-base2 of a vector
 *
 * @param baseN
 * The base of the logarithm.
 *
 * @param a vector
 *
 * @return A vector with the log-baseN of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec2_t<N> logN(const vec2_t<N>& baseN, const vec2_t<N>& n) noexcept;

/**
 * @brief pow
 * Evaluate a vector to a given power.
 *
 * Powers are calculated component-wise.
 *
 * @param x
 *
 * @param y
 *
 * @return x^y
 */
template <typename N>
constexpr vec2_t<N> pow(
    const typename utils::EnableIf<IsIntegral<N>::value, vec2_t<N>>::type& x,
    const typename utils::EnableIf<IsIntegral<N>::value, vec2_t<N>>::type& y) noexcept;

template <typename N>
inline vec2_t<N> pow(const vec2_t<N>& x, const vec2_t<N>& y) noexcept;

/**
 * @brief pow
 * Evaluate the exponentiation of e^x.
 *
 * @param x
 * The power X to which e will be raised by, per vector component.
 *
 * @return E, raised to the power x.
 */
template <typename N>
inline vec2_t<N> exp(vec2_t<N> x) noexcept;

/**
 * @brief pow
 * Evaluate the exponentiation of e^x.
 *
 * @param x
 * The power X to which e will be raised by, per vector component.
 *
 * @return E, raised to the power x.
 */
template <typename N>
inline vec2_t<N> exp2(vec2_t<N> x) noexcept;

/**
 * @brief Perform a fused multiply-and-add calculation on a vector.
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
template <typename N>
constexpr vec2_t<N> fmadd(const vec2_t<N>& x, const vec2_t<N>& m, const vec2_t<N>& a) noexcept;

/**
 * @brief Perform a fused multiply-and-sub calculation on a vector.
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
template <typename N>
constexpr vec2_t<N> fmsub(const vec2_t<N>& x, const vec2_t<N>& m, const vec2_t<N>& a) noexcept;



/*-----------------------------------------------------------------------------
    3D Vectors
-----------------------------------------------------------------------------*/
/**
 *  @brief sum
 *  Retrieve the sum of all components in a 3D vector.
 *
 *  @param v
 *
 *  @return the sum of elements within v.
 */
template <typename N> constexpr
N sum(const vec3_t<N>& v);

/**
 *  @brief reciprocal sum
 *  Retrieve the reciprocal of the sum sum of all vector elements.
 *
 *  @param v
 *
 *  @return the reciprocal of the sum of elements within v.
 */
template <typename N> constexpr
N sum_inv(const vec3_t<N>& v);

/**
 *  @brief dot
 *  Retrieve the dot product of a 3D vector.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return the 3D dot product of v1 & v2.
 */
template <typename N> constexpr
N dot(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief cross
 *  Retrieve the cross product of two 3D vectors. This result is perpendicular
 *  to the two input vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A 3D vector which represents the axis of rotation of two 3D
 *  vectors.
 */
template <typename N> constexpr
vec3_t<N> cross(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief normalize
 *  Normalize the vector v so that its points lie within a unit-sphere.
 *
 *  @param v
 *
 *  @return a normalized 4D vector.
 */
template <typename N> inline
vec3_t<N> normalize(const vec3_t<N>& v);

/**
 *  @brief lengthSquared
 *  Retrieve the square of the length/magnitude of a 3D vector. This is faster
 *  than calling length() as no square roots are performed.
 *
 *  @param v
 *  A 3D vector.
 *
 *  @return The square of the length/magnitude of a 3D vector.
 */
template <typename N> constexpr
N length_squared(const vec3_t<N>& v);

/**
 *  @brief length
 *  Retrieve the length/magnitude of a 3D vector.
 *
 *  @param v
 *  A 3D vector.
 *
 *  @return The length/magnitude of a 3D vector.
 */
template <typename N> inline
N length(const vec3_t<N>& v);

/**
 *  @brief xRotation
 *  Retrieve a unit vector that has been rotated around the cartesian X-Axis
 *  by a certain number of radians.
 *
 *  @param angle
 *  The number of radians that a 3D vector is to be rotated by.
 *
 *  @return A 3D vector rotated by 'angle' radians around the cartesian X-Axis.
 */
template <typename N> inline
vec3_t<N> x_rotation(N angle);

/**
 *  @brief xRotation
 *  Retrieve a unit vector that has been rotated around the cartesian Y-Axis
 *  by a certain number of radians.
 *
 *  @param angle
 *  The number of radians that a 3D vector is to be rotated by.
 *
 *  @return A 3D vector rotated by 'angle' radians around the cartesian Y-Axis.
 */
template <typename N> inline
vec3_t<N> y_rotation(N angle);

/**
 *  @brief xRotation
 *  Retrieve a unit vector that has been rotated around the cartesian Z-Axis
 *  by a certain number of radians.
 *
 *  @param angle
 *  The number of radians that a 3D vector is to be rotated by.
 *
 *  @return A 3D vector rotated by 'angle' radians around the cartesian Z-Axis.
 */
template <typename N> inline
vec3_t<N> z_rotation(N angle);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two 3D vectors placed around the origin
 *  of the Cartesian coordinate plane.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angle_between(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two points in 3D space, with a
 *  specified origin.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @param origin
 *  The point in 3D space that two points use as their origin.
 *
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angle_between(const vec3_t<N>& v1, const vec3_t<N>& v2, const vec3_t<N>& origin);

/**
 *  @brief min
 *  Retrieve the component-wise minimum of two vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A vector with the minimum X/Y/Z values extracted from either of the
 *  input vectors.
 */
template <typename N> constexpr
vec3_t<N> min(const vec3_t<N>&, const vec3_t<N>&);

/**
 *  @brief mix
 *  Retrieve the linear interpolation of one vector towards another, moved by
 *  a certain percentage.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @param percent
 *  The percentage (clamped from [0, 1]) to which v2 should be interpolated
 *  towards v2.
 *
 *  @return An interpolated vector value between v1 and v2, according to the
 *  percentage N.
 */
template <typename N> constexpr
vec3_t<N> mix(const vec3_t<N>&, const vec3_t<N>&, N);

/**
 *  @brief max
 *  Retrieve the component-wise maximum of two vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A vector with the maximum X/Y/Z values extracted from either of the
 *  input vectors.
 */
template <typename N> constexpr
vec3_t<N> max(const vec3_t<N>&, const vec3_t<N>&);

/**
 *  @brief project
 *  Project one vector onto another and retrieve the result.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return The vector projection of v1 onto v2.
 */
template <typename N> inline
vec3_t<N> project(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief reflect
 *  Reflect a vector v around a normal vector.
 *
 *  @param v
 *
 *  @param norm
 *  The normal vector from which v will be reflected.
 *
 *  @return
 *  The reflection of v around the normal vector 'norm'.
 */
template <typename N> constexpr
vec3_t<N> reflect(const vec3_t<N>& v1, const vec3_t<N>& norm);

/**
 *  @brief mid
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return the midpoint between v1 and v2.
 */
template <typename N> constexpr
vec3_t<N> mid(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief rcp
 *
 *  Estimate the reciprocal of all elements in the input vector.
 *
 *  @param v
 *
 *  @return the element-wise reciprocal between v.
 */
template <typename N> constexpr
vec3_t<N> rcp(const vec3_t<N>& v);

/**
 * @brief Retrieve the sign bits of a vector type.
 *
 * @param x
 * The number to be queried.
 *
 * @returns A value of 1 in each of the lower 3 bits of the return value if
 * the signs are set.
 */
template <typename N> constexpr
int sign_mask(const vec3_t<N>& x) noexcept;

/**
 * @brief Retrieve the component-wise signs of a vector type.
 *
 * @param x
 * The number to be queried.
 *
 * @returns A value of 1 in each of component of the return value if the sign
 * within x are set.
 */
template <typename N> constexpr
vec3_t<N> sign(const vec3_t<N>& x) noexcept;

/**
 *  @brief floor
 *
 *  Calculate the floating-point floor of all vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded down to the nearest integer.
 */
template <typename N> constexpr
vec3_t<N> floor(const vec3_t<N>& v);

/**
 *  @brief ceil
 *
 *  Calculate the floating-point ceiling of all vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded up to the nearest integer.
 */
template <typename N> constexpr
vec3_t<N> ceil(const vec3_t<N>& v);

/**
 *  @brief round
 *
 *  Round all floating-point vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded to the nearest integer.
 */
template <typename N> constexpr
vec3_t<N> round(const vec3_t<N>& v);

/**
 * @brief log2
 * Calculate the log-base2 of a vector
 *
 * @param a vector
 *
 * @return A vector with the log-base2 of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec3_t<N> log2(const vec3_t<N>& n) noexcept;

/**
 * @brief fastLog
 * Calculate the natural log of a vector
 *
 * @param a vector
 *
 * @return ln(vec3), using IEEE floating point arithmetic
 */
template <typename N>
inline vec3_t<N> log(const vec3_t<N>&) noexcept;

/**
 * @brief log2
 * Calculate the log-base2 of a vector
 *
 * @param a vector
 *
 * @return A vector with the log-base2 of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec3_t<N> log10(const vec3_t<N>&) noexcept;

/**
 * @brief logN
 * Calculate the log-base2 of a vector
 *
 * @param baseN
 * The base of the logarithm.
 *
 * @param a vector
 *
 * @return A vector with the log-baseN of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec3_t<N> logN(const vec3_t<N>& baseN, const vec3_t<N>& n) noexcept;

/**
 * @brief pow
 * Evaluate a vector to a given power.
 *
 * Powers are calculated component-wise.
 *
 * @param x
 *
 * @param y
 *
 * @return x^y
 */
template <typename N>
constexpr vec3_t<N> pow(
    const typename utils::EnableIf<IsIntegral<N>::value, vec3_t<N>>::type& x,
    const typename utils::EnableIf<IsIntegral<N>::value, vec3_t<N>>::type& y) noexcept;

template <typename N>
inline vec3_t<N> pow(const vec3_t<N>& x, const vec3_t<N>& y) noexcept;

/**
 * @brief pow
 * Evaluate the exponentiation of e^x.
 *
 * @param x
 * The power X to which e will be raised by, per vector component.
 *
 * @return E, raised to the power x.
 */
template <typename N>
inline vec3_t<N> exp(vec3_t<N> x) noexcept;

/**
 * @brief pow
 * Evaluate the exponentiation of e^x.
 *
 * @param x
 * The power X to which e will be raised by, per vector component.
 *
 * @return E, raised to the power x.
 */
template <typename N>
inline vec3_t<N> exp2(vec3_t<N> x) noexcept;

/**
 * @brief Perform a fused multiply-and-add calculation on a vector.
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
template <typename N>
constexpr vec3_t<N> fmadd(const vec3_t<N>& x, const vec3_t<N>& m, const vec3_t<N>& a) noexcept;

/**
 * @brief Perform a fused multiply-and-sub calculation on a vector.
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
template <typename N>
constexpr vec3_t<N> fmsub(const vec3_t<N>& x, const vec3_t<N>& m, const vec3_t<N>& a) noexcept;



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/**
 *  @brief sum
 *  Retrieve the sum of all components in a 4D vector.
 *
 *  @param v
 *
 *  @return the sum of elements within v.
 */
template <typename N> constexpr
N sum(const vec4_t<N>& v);

/**
 *  @brief reciprocal sum
 *  Retrieve the reciprocal of the sum sum of all vector elements.
 *
 *  @param v
 *
 *  @return the reciprocal of the sum of elements within v.
 */
template <typename N> constexpr
N sum_inv(const vec4_t<N>& v);

/**
 *  @brief dot
 *  Retrieve the dot product of two 4D vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return the 4D dot product of v1 & v2.
 */
template <typename N> constexpr
N dot(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief cross
 *  Retrieve the cross product of two 4D vectors, treated as though they were
 *  3D vectors. This result is 3D perpendicular to the two input vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A 4D vector which represents the axis of rotation of two 4D
 *  vectors. The final component is set to zero.
 */
template <typename N> constexpr
vec4_t<N> cross(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief normalize
 *  Normalize the vector v so that its points lie within a unit-sphere.
 *
 *  @param v
 *
 *  @return a normalized 4D vector.
 */
template <typename N> inline
vec4_t<N> normalize(const vec4_t<N>& v);

/**
 *  @brief lengthSquared
 *  Retrieve the square of the length/magnitude of a 4D vector. This is faster
 *  than calling length() as no square roots are performed.
 *
 *  @param v
 *  A 4D vector.
 *
 *  @return The square of the length/magnitude of a 4D vector.
 */
template <typename N> constexpr
N length_squared(const vec4_t<N>& v);

/**
 *  @brief length
 *  Retrieve the length/magnitude of a 4D vector.
 *
 *  @param v
 *  A 4D vector.
 *
 *  @return The length/magnitude of a 4D vector.
 */
template <typename N> inline
N length(const vec4_t<N>& v);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two 4D vectors placed around the origin
 *  of the Cartesian coordinate plane.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angle_between(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two points in 4D space, with a
 *  specified origin.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @param origin
 *  The point in 4D space that two points use as their origin.
 *
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angle_bewteen(const vec4_t<N>& v1, const vec4_t<N>& v2, const vec4_t<N>& origin);

/**
 *  @brief min
 *  Retrieve the component-wise minimum of two vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A vector with the minimum X/Y/Z/W values extracted from either of the
 *  input vectors.
 */
template <typename N> constexpr
vec4_t<N> min(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief mix
 *  Retrieve the linear interpolation of one vector towards another, moved by
 *  a certain percentage.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @param percent
 *  The percentage (clamped from [0, 1]) to which v2 should be interpolated
 *  towards v2.
 *
 *  @return An interpolated vector value between v1 and v2, according to the
 *  percentage N.
 */
template <typename N> constexpr
vec4_t<N> mix(const vec4_t<N>& v1, const vec4_t<N>& v2, N percent);

/**
 *  @brief max
 *  Retrieve the component-wise maximum of two vectors.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return A vector with the maximum X/Y/Z/W values extracted from either of the
 *  input vectors.
 */
template <typename N> constexpr
vec4_t<N> max(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief project
 *  Project one vector onto another and retrieve the result.
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return The vector projection of v1 onto v2.
 */
template <typename N> inline
vec4_t<N> project(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief reflect
 *  Reflect a vector v around a normal vector.
 *
 *  @param v
 *
 *  @param norm
 *  The normal vector from which v will be reflected.
 *
 *  @return
 *  The reflection of v around the normal vector 'norm'.
 */
template <typename N> constexpr
vec4_t<N> reflect(const vec4_t<N>& v1, const vec4_t<N>& norm);

/**
 *  @brief mid
 *
 *  @param v1
 *
 *  @param v2
 *
 *  @return the midpoint between v1 and v2.
 */
template <typename N> constexpr
vec4_t<N> mid(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief rcp
 *
 *  Estimate the reciprocal of all elements in the input vector.
 *
 *  @param v
 *
 *  @return the element-wise reciprocal between v.
 */
template <typename N> constexpr
vec4_t<N> rcp(const vec4_t<N>& v);

/**
 * @brief Retrieve the sign bits of a vector type.
 *
 * @param x
 * The number to be queried.
 *
 * @returns A value of 1 in each of the lower 4 bits of the return value if
 * the signs are set.
 */
template <typename N> constexpr
int sign_mask(const vec4_t<N>& x) noexcept;

/**
 * @brief Retrieve the component-wise signs of a vector type.
 *
 * @param x
 * The number to be queried.
 *
 * @returns A value of 1 in each of component of the return value if the sign
 * within x are set.
 */
template <typename N> constexpr
vec4_t<N> sign(const vec4_t<N>& x) noexcept;

/**
 *  @brief floor
 *
 *  Calculate the floating-point floor of all vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded down to the nearest integer.
 */
template <typename N> constexpr
vec4_t<N> floor(const vec4_t<N>& v);

/**
 *  @brief ceil
 *
 *  Calculate the floating-point ceiling of all vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded up to the nearest integer.
 */
template <typename N> constexpr
vec4_t<N> ceil(const vec4_t<N>& v);

/**
 *  @brief round
 *
 *  Round all floating-point vector elements.
 *
 *  @param v
 *
 *  @return A vector with all elements rounded to the nearest integer.
 */
template <typename N> constexpr
vec4_t<N> round(const vec4_t<N>& v);

/**
 * @brief log2
 * Calculate the log-base2 of a vector
 *
 * @param a vector
 *
 * @return A vector with the log-base2 of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec4_t<N> log2(const vec4_t<N>&) noexcept;

/**
 * @brief fastLog
 * Calculate the natural log of a vector
 *
 * @param a vector
 *
 * @return ln(vec3), using IEEE floating point arithmetic
 */
template <typename N>
inline vec4_t<N> log(const vec4_t<N>&) noexcept;

/**
 * @brief log2
 * Calculate the log-base2 of a vector
 *
 * @param a vector
 *
 * @return A vector with the log-base2 of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec4_t<N> log10(const vec4_t<N>&) noexcept;

/**
 * @brief logN
 * Calculate the log-base2 of a vector
 *
 * @param baseN
 * The base of the logarithm.
 *
 * @param a vector
 *
 * @return A vector with the log-baseN of a number, using IEEE floating point
 * arithmetic
 */
template <typename N>
inline vec4_t<N> logN(const vec4_t<N>& baseN, const vec4_t<N>& n) noexcept;

/**
 * @brief pow
 * Evaluate a vector to a given power.
 *
 * Powers are calculated component-wise.
 *
 * @param x
 *
 * @param y
 *
 * @return x^y
 */
template <typename N>
constexpr vec4_t<N> pow(
    const typename utils::EnableIf<IsIntegral<N>::value, vec4_t<N>>::type& x,
    const typename utils::EnableIf<IsIntegral<N>::value, vec4_t<N>>::type& y) noexcept;

template <typename N>
inline vec4_t<N> pow(const vec4_t<N>& x, const vec4_t<N>& y) noexcept;

/**
 * @brief pow
 * Evaluate the exponentiation of e^x.
 *
 * @param x
 * The power X to which e will be raised by, per vector component.
 *
 * @return E, raised to the power x.
 */
template <typename N>
inline vec4_t<N> exp(vec4_t<N> x) noexcept;

/**
 * @brief pow
 * Evaluate the exponentiation of e^x.
 *
 * @param x
 * The power X to which e will be raised by, per vector component.
 *
 * @return E, raised to the power x.
 */
template <typename N>
inline vec4_t<N> exp2(vec4_t<N> x) noexcept;

/**
 * @brief Perform a fused multiply-and-add calculation on a vector.
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
template <typename N>
constexpr vec4_t<N> fmadd(const vec4_t<N>& x, const vec4_t<N>& m, const vec4_t<N>& a) noexcept;

/**
 * @brief Perform a fused multiply-and-sub calculation on a vector.
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
template <typename N>
constexpr vec4_t<N> fmsub(const vec4_t<N>& x, const vec4_t<N>& m, const vec4_t<N>& a) noexcept;



/*-----------------------------------------------------------------------------
    Vector Casting
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Casts to 2D Vectors
-------------------------------------*/
/**
 * @brief Perform a truncating cast from a 3D vector to a 2D vector.
 *
 * @param v
 * A 3D Vector of type N.
 *
 * @return A 2D Vector containing the X and Y elements of v.
 */
template <typename N>
constexpr vec2_t<N> vec2_cast(const vec3_t<N>& v) noexcept;

/**
 * @brief Perform a truncating cast from a 4D vector to a 2D vector.
 *
 * @param v
 * A 4D Vector of type N.
 *
 * @return A 2D Vector containing the X and Y elements of v.
 */
template <typename N>
constexpr vec2_t<N> vec2_cast(const vec4_t<N>& v) noexcept;



/*-------------------------------------
    Casts to 3D Vectors
-------------------------------------*/
/**
 * @brief Perform a concatenating cast of a 2D vector and scalar into a 3D
 * vector.
 *
 * @param v
 * A 2D vector of type N to be used for the X/Y components of the output
 * vector.
 *
 * @param s
 * A scalar which will construct the Z-component of the output vector.
 *
 * @return A 3D vector containing the X/Y elements of v and Z component from
 * an input scalar.
 */
template <typename N>
constexpr vec3_t<N> vec3_cast(const vec2_t<N>& v, const N& s) noexcept;

/**
 * @brief Perform a concatenating cast of a 2D vector and scalar into a 3D
 * vector.
 *
 * @param s
 * A scalar which will construct the X-component of the output vector.
 *
 * @param v
 * A 2D vector of type N to be used for the Y/Z components of the output
 * vector.
 *
 * @return A 3D vector containing the X component from an input scalar and Y/Z
 * from the elements of v.
 */
template <typename N>
constexpr vec3_t<N> vec3_cast(const N& s, const vec2_t<N>& v) noexcept;

/**
 * @brief Perform a truncating cast from a 4D vector to a 3D vector.
 *
 * @param v
 * A 4D Vector of type N.
 *
 * @return A 3D Vector containing the X, Y, and Z elements of v.
 */
template <typename N>
constexpr vec3_t<N> vec3_cast(const vec4_t<N>& v) noexcept;



/*-------------------------------------
    Casts to 4D Vectors
-------------------------------------*/
/**
 * @brief Perform a concatenating cast of a 2D vector and two scalars into a
 * 4D vector.
 *
 * @param v
 * A 2D vector of type N to be used for the X/Y components of the output
 * vector.
 *
 * @param s0
 * A scalar which will construct the Z-component of the output vector.
 *
 * @param s1
 * A scalar which will construct the W-component of the output vector.
 *
 * @return A 4D vector containing the X/Y elements of v and Z, W components
 * from two input scalars.
 */
template <typename N>
constexpr vec4_t<N> vec4_cast(const vec2_t<N>& v, const N& s0, const N& s1) noexcept;

/**
 * @brief Perform a concatenating cast of a 2D vector and two scalars into a
 * 4D vector.
 *
 * @param s0
 * A scalar which will construct the X-component of the output vector.
 *
 * @param v
 * A 2D vector of type N to be used for the Y/Z components of the output
 * vector.
 *
 * @param s1
 * A scalar which will construct the W-component of the output vector.
 *
 * @return A 4D vector containing the X component from an input scalar, Y/Z
 * from the elements of v, and W component from another scalar.
 */
template <typename N>
constexpr vec4_t<N> vec4_cast(const N& s0, const vec2_t<N>& v, const N& s1) noexcept;

/**
 * @brief Perform a concatenating cast of a 2D vector and two scalars into a
 * 4D vector.
 *
 * @param s0
 * A scalar which will construct the X-component of the output vector.
 *
 * @param s1
 * A scalar which will construct the Y-component of the output vector.
 *
 * @param v
 * A 2D vector of type N to be used for the Z/W components of the output
 * vector.
 *
 * @return A 4D vector containing the X/Y component from two input scalars,
 * and Z/W from the elements of v.
 */
template <typename N>
constexpr vec4_t<N> vec4_cast(const N& s0, const N& s1, const vec2_t<N>& v) noexcept;

/**
 * @brief Perform a concatenating cast of two 2D vectors into a 4D vector.
 *
 * @param v0
 * A 2D vector which will construct the X/Y components of the output vector.
 *
 * @param v1
 * A 2D  which will construct the Z/W component of the output vector.
 *
 * @return A 4D vector containing the X/Y component from one 2D vector and Z/W
 * components from the other 2D vector.
 */
template <typename N>
constexpr vec4_t<N> vec4_cast(const vec2_t<N>& v0, const vec2_t<N>& v1) noexcept;

/**
 * @brief Perform a concatenating cast of a 3D vector and scalar into a 4D
 * vector.
 *
 * @param v
 * A 3D vector of type N to be used for the X/Y/Z components of the output
 * vector.
 *
 * @param s
 * A scalar which will construct the W-component of the output vector.
 *
 * @return A 4D vector containing the X/Y/Z elements of v and W component from
 * an input scalar.
 */
template <typename N>
constexpr vec4_t<N> vec4_cast(const vec3_t<N>& v, const N& s) noexcept;

/**
 * @brief Perform a concatenating cast of a scalar and 3D vector into a 4D
 * vector.
 *
 * @param s
 * A scalar which will construct the X-component of the output vector.
 *
 * @param v
 * A 3D vector of type N to be used for the Y/Z/W components of the output
 * vector.
 *
 * @return A 4D vector containing the X component from an input scalar and
 * Y/Z/W components from the elements of v.
 */
template <typename N>
constexpr vec4_t<N> vec4_cast(const N& s, const vec3_t<N>& v) noexcept;



} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/vec_utils_impl.h"

#ifdef LS_ARCH_X86
    #include "lightsky/math/x86/vecf_utils_impl.h"
#elif defined(LS_ARCH_ARM)
    #include "lightsky/math/arm/vecf_utils_impl.h"
#endif

#endif /* LS_MATH_VEC_UTILS_H */
