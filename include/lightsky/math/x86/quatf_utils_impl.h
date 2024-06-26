
#ifndef LS_MATH_QUATF_UTILS_IMPL_H
#define LS_MATH_QUATF_UTILS_IMPL_H

#include <pmmintrin.h>

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    Quaternion Utilities
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Dot
-------------------------------------*/
inline LS_INLINE float dot(const quat_t<float>& q1, const quat_t<float>& q2)
{
    // horizontal add
    const __m128 a = _mm_mul_ps(_mm_loadu_ps(q1.q), _mm_loadu_ps(q2.q));

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(e);
}

/*-------------------------------------
    4D Magnitude-Squared
-------------------------------------*/
inline LS_INLINE float length_squared(const quat_t<float>& q)
{
    // cache
    const __m128 s = _mm_loadu_ps(q.q);

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(e);
}

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
inline LS_INLINE float length(const quat_t<float>& q)
{
    // cache
    const __m128 s = _mm_loadu_ps(q.q);

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(_mm_sqrt_ps(e));
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
inline LS_INLINE math::quat_t<float> normalize(const quat_t<float>& q)
{
    // cache
    const __m128 s = _mm_loadu_ps(q.q);

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    // normalization
    alignas(sizeof(__m128)) quat_t<float> ret;
    _mm_store_ps(ret.q, _mm_mul_ps(s, _mm_rcp_ps(_mm_sqrt_ps(e))));
    return ret;
}



} // end math namespace
} // end ls namespace

#endif /* LS_MATH_QUATF_UTILS_IMPL_H */
