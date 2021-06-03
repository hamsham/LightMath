
#ifndef LS_MATH_INTERPOLATE_H
#define LS_MATH_INTERPOLATE_H

namespace ls
{
namespace math
{



/**
 * @brief Bezier curve (quadratic)
 *
 * @param t
 * The percent, between [0, 1] to interpolate all points passed into the
 * function.
 *
 * @param p0
 * The first point to interpolate.
 *
 * @param p1
 * The second point to interpolate.
 *
 * @param p2
 * The third point to interpolate.
 *
 * @return A value, interpolated among all points by a percentage, using the
 * general bezier formula.
 */
template <typename U, typename T>
inline T bezier_quadratic(U t, T p0, T p1, T p2) noexcept;



/**
 * @brief Bezier curve (cubic)
 *
 * @param t
 * The percent, between [0, 1] to interpolate all points passed into the
 * function.
 *
 * @param p0
 * The first point to interpolate.
 *
 * @param p1
 * The second point to interpolate.
 *
 * @param p2
 * The third point to interpolate.
 *
 * @param p3
 * The fourth point to interpolate.
 *
 * @return A value, interpolated among all points by a percentage, using the
 * general bezier formula.
 */
template <typename U, typename T>
inline T bezier_cubic(U t, T p0, T p1, T p2, T p3) noexcept;



/**
 * @brief Bezier curve (general solution)
 *
 * @param t
 * The percent, between [0, 1] to interpolate all points passed into the
 * function.
 *
 * @param p0
 * The first point to interpolate.
 *
 * @param p1
 * A variadic number of subsequent, sequential points to interpolate.
 *
 * @return A value, interpolated among all points by a percentage, using the
 * general bezier formula.
 */
template <typename U, typename T, typename... TT>
inline T bezier_general(const U& t, const T& p0, const TT&... p1) noexcept;



} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/Interpolate_impl.h"

#endif /* LS_MATH_INTERPOLATE_H */
