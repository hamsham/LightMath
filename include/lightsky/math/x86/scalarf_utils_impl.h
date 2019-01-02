
#include <immintrin.h> // SSE3

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    Function definitions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    min
-------------------------------------*/
inline LS_INLINE float min(float a, float b) noexcept
{
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

/*-------------------------------------
    min
-------------------------------------*/
inline LS_INLINE float min(float a, float b, float c) noexcept
{
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_min_ss(_mm_set_ss(b), _mm_set_ss(c))));
}

/*-------------------------------------
    min
-------------------------------------*/
inline LS_INLINE float min(float a, float b, float c, float d) noexcept
{
    const __m128 v = _mm_set_ps(a, b, c, d);
    const __m128 v1 = _mm_shuffle_ps(v, v, 0xB1);
    const __m128 v2 = _mm_min_ps(v, v1);
    const __m128 v3 = _mm_shuffle_ps(v2, v2, 0x0F);
    const __m128 v4 = _mm_min_ps(v2, v3);
    return _mm_cvtss_f32(v4);
}



/*-------------------------------------
    max
-------------------------------------*/
inline LS_INLINE float max(float a, float b) noexcept
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

/*-------------------------------------
    max
-------------------------------------*/
inline LS_INLINE float max(float a, float b, float c) noexcept
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_max_ss(_mm_set_ss(b), _mm_set_ss(c))));
}

/*-------------------------------------
    max
-------------------------------------*/
inline LS_INLINE float max(float a, float b, float c, float d) noexcept
{
    const __m128 v = _mm_set_ps(a, b, c, d);
    const __m128 v1 = _mm_shuffle_ps(v, v, 0xB1);
    const __m128 v2 = _mm_max_ps(v, v1);
    const __m128 v3 = _mm_shuffle_ps(v2, v2, 0x0F);
    const __m128 v4 = _mm_max_ps(v2, v3);
    return _mm_cvtss_f32(v4);
}



/*-------------------------------------
    clamp
-------------------------------------*/
inline LS_INLINE float clamp(float n, float minVal, float maxVal) noexcept
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_min_ss(_mm_set_ss(n), _mm_set_ss(maxVal)), _mm_set_ss(minVal)));
}



/*-------------------------------------
    floor
-------------------------------------*/
inline LS_INLINE float floor(float n) noexcept
{
    return _mm_cvtss_f32(_mm_floor_ps(_mm_set1_ps(n)));
}



/*-------------------------------------
    ceil
-------------------------------------*/
inline LS_INLINE float ceil(float n) noexcept
{
    return _mm_cvtss_f32(_mm_ceil_ps(_mm_set1_ps(n)));
}



/*-------------------------------------
    round
-------------------------------------*/
inline LS_INLINE float round(float n) noexcept
{
    return _mm_cvtss_f32(_mm_round_ps(_mm_set1_ps(n), _MM_FROUND_TO_NEAREST_INT));
}



/*-------------------------------------
 fmod
-------------------------------------*/
inline LS_INLINE float fmod(const float n1, const float n2) noexcept
{
    const __m128  num   = _mm_set_ss(n1);
    const __m128  denom = _mm_set_ss(n2);
    const __m128  c     = _mm_div_ss(num, denom);
    const __m128i i     = _mm_cvttps_epi32(c);
    const __m128  t     = _mm_cvtepi32_ps(i); // truncate fraction
    const __m128  base  = _mm_mul_ss(t, denom);
    return _mm_cvtss_f32(_mm_sub_ss(num, base));
}



/*-------------------------------------
 fmod_1
-------------------------------------*/
inline LS_INLINE float fmod_1(const float n) noexcept
{
    const __m128  num   = _mm_set_ss(n);
    const __m128i i     = _mm_cvttps_epi32(num);
    const __m128  t     = _mm_cvtepi32_ps(i); // truncate fraction
    return _mm_cvtss_f32(_mm_sub_ss(num, t));
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
inline LS_INLINE float fast_inv_sqrt(float x) noexcept
{
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
inline LS_INLINE float fast_sqrt(float input) noexcept
{
    return _mm_cvtss_f32(_mm_rcp_ss(_mm_rsqrt_ss(_mm_set_ss(input))));
}



/*-------------------------------------
    rcp
-------------------------------------*/
inline LS_INLINE float rcp(float input) noexcept
{
    return _mm_cvtss_f32(_mm_rcp_ss(_mm_set_ss(input)));
}



/*-------------------------------------
    sum
-------------------------------------*/
inline LS_INLINE float sum(float num0, float num1, float num2, float num3) noexcept
{
    const __m128 a = _mm_set_ps(num0, num1, num2, num3);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(e);
}



/*-------------------------------------
    sign_bit
-------------------------------------*/
inline LS_INLINE int sign_bit(float x) noexcept
{
    return _mm_cvtsi128_si32(_mm_castps_si128(_mm_set_ss(x))) >> 31;
}



} // end math namespace
} // end ls namespace
