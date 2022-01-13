
#ifndef LS_MATH_INTERPOLATE_IMPL_H
#define LS_MATH_INTERPOLATE_IMPL_H

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/vec_utils.h"

namespace ls
{



/*-----------------------------------------------------------------------------
 * Bezier curve (quadratic)
-----------------------------------------------------------------------------*/
template <typename U, typename T>
inline T math::bezier_quadratic(U t, T p0, T p1, T p2) noexcept
{
    return (p0 * math::pow<U>(U{1} - t, U{2}))
           + ((p1 * t) * (U{1}-t) * U{2})
           + (p2 * math::pow<U>(t, U{2}));
}



/*-----------------------------------------------------------------------------
 * Bezier curve (cubic)
-----------------------------------------------------------------------------*/
template <typename U, typename T>
inline T math::bezier_cubic(U t, T p0, T p1, T p2, T p3) noexcept
{
    return (p0 * math::pow<U>(U{1} - t, U{3}))
           + ((p1 * t) * math::pow<U>(U{1}-t, U{2}) * U{3})
           + (p2 * math::pow<U>(t, U{2}) * (U{1}-t) * U{3})
           + (p3 * math::pow<U>(t, U{3}));
}



/*-----------------------------------------------------------------------------
 * Bezier curve (general solution)
-----------------------------------------------------------------------------*/
namespace math
{
namespace impl
{



/*-------------------------------------
 * Compile-time factorials
-------------------------------------*/
template <typename T>
constexpr T _binomial_factorial(const T& n) noexcept
{
    return !n ? T{1} : n * _binomial_factorial<T>(n-T{1});
}



// In the case of factorial division, we can simplify an expression by
// removing all matching terms
template <typename T>
constexpr T _binomial_factorial_simplify(const T& n, const T& k) noexcept
{
    return (!n || n == k) ? T{1} : n * _binomial_factorial_simplify<T>(n-T{1}, k);
}



/*-------------------------------------
 * Compile-time binomial coefficient
-------------------------------------*/
template <unsigned N, unsigned K>
constexpr unsigned _binomial_coeff() noexcept
{
    static_assert(N >= K, "Cannot compute binomial coefficient (n < k).");
    static_assert(K >= 0, "Cannot compute binomial coefficient (k < 0).");
    return _binomial_factorial_simplify<unsigned>(N, K) / _binomial_factorial<unsigned>(N - K);
    //return factorial<unsigned>(N) / (factorial<unsigned>(K) * factorial<unsigned>(N - K));
}



/*-------------------------------------
 * bezier implementation (single-term)
-------------------------------------*/
template <typename U, unsigned i, unsigned n, typename T>
inline T _bezier_general_impl(const U& t, const T& p) noexcept
{
    return p * T{math::pow<U>(t, U{i}) * math::pow<U>(U{1}-t, U{n-i}) * U{impl::_binomial_coeff<n, i>()}};
}



/*-------------------------------------
 * bezier implementation (summation)
-------------------------------------*/
template <typename U, unsigned i, unsigned n, typename T, typename... TT>
inline T _bezier_general_impl(const U& t, const T& p, const TT&... pp) noexcept
{
    return _bezier_general_impl<U, i, n, T>(t, p) + _bezier_general_impl<U, i+1, n, TT...>(t, pp...);
}



} // impl namespace
} // math namespace



template <typename U, typename T, typename... TT>
inline T math::bezier_general(const U& t, const T& p0, const TT&... p1) noexcept
{
    return impl::_bezier_general_impl<U, 0, sizeof...(TT), T, TT...>(t, p0, p1...);
}



} // ls namespace

#endif /* LS_MATH_INTERPOLATE_IMPL_H */
