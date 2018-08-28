
#include <emmintrin.h> // SSE2
#include <xmmintrin.h> // SSE

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
/*
template<> inline
float min(float a, float b) noexcept
{
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
*/



/*-------------------------------------
    max
-------------------------------------*/
/*
template<> inline
float max(float a, float b) noexcept
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
*/



/*-------------------------------------
    clamp
-------------------------------------*/
/*
template<> inline
float clamp(float n, float minVal, float maxVal) noexcept
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_min_ss(_mm_set_ss(n), _mm_set_ss(maxVal)), _mm_set_ss(minVal)));
}
*/



/*-------------------------------------
    floor
-------------------------------------*/
/*
template<>
*/inline
float floor(float n) noexcept
{
    const __m128 f = _mm_set_ss(n);
    const __m128 t = _mm_cvtepi32_ps(_mm_cvttps_epi32(f)); // truncate fraction bits
    const __m128 r = _mm_sub_ps(t, _mm_and_ps(_mm_cmplt_ps(f, t), _mm_set_ss(1.f)));
    return _mm_cvtss_f32(r);
}



/*-------------------------------------
 fmod
-------------------------------------*/
/*
template<> inline
*/
/*
inline
float fmod(const float n1, const float n2) noexcept
{
    const __m128  num   = _mm_set_ss(n1);
    const __m128  denom = _mm_set_ss(n2);
    const __m128  c     = _mm_div_ss(num, denom);
    const __m128i i     = _mm_cvttps_epi32(c);
    const __m128  t     = _mm_cvtepi32_ps(i); // truncate fraction
    const __m128  base  = _mm_mul_ss(t, denom);
    return _mm_cvtss_f32(_mm_sub_ss(num, base));
}
*/



/*-------------------------------------
 fmod_1
-------------------------------------*/
/*
template<> inline
*/
/*
inline float fmod_1(const float n) noexcept
{
    const __m128  num   = _mm_set_ss(n);
    const __m128i i     = _mm_cvttps_epi32(num);
    const __m128  t     = _mm_cvtepi32_ps(i); // truncate fraction
    return _mm_cvtss_f32(_mm_sub_ss(num, t));
}
*/



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
template<> inline
float fast_inv_sqrt<float>(float x) noexcept
{
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
template<> inline
float fast_sqrt<float>(float input) noexcept
{
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(input)));
}



} // end math namespace
} // end ls namespace
