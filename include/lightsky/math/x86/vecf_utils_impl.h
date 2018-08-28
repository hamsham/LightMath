
#include <pmmintrin.h>

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    2D Vectors
-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
    3D Vectors
-----------------------------------------------------------------------------*/
/*
template<> inline
float dot<float>(const vec3_t<float>& v1, const vec3_t<float>& v2)
{
    //const __m128i axy = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(v1.v));
    //const __m128  va  = _mm_movelh_ps(_mm_castsi128_ps(axy), _mm_load_ss(&v1.v[2]));
    //const __m128i bxy = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(v2.v));
    //const __m128  vb  = _mm_movelh_ps(_mm_castsi128_ps(bxy), _mm_load_ss(&v2.v[2]));

    const __m128 va(_mm_shuffle_ps(_mm_movelh_ps(_mm_load_ss(&v1.v[0]), _mm_load_ss(&v1.v[1])), _mm_load_ss(&v1.v[2]), _MM_SHUFFLE(2, 0, 2, 0)));
    const __m128 vb(_mm_shuffle_ps(_mm_movelh_ps(_mm_load_ss(&v2.v[0]), _mm_load_ss(&v2.v[1])), _mm_load_ss(&v2.v[2]), _MM_SHUFFLE(2, 0, 2, 0)));

    //const __m128 c = _mm_mul_ps(va, vb);
    //const __m128 d = _mm_hadd_ps(c, c);
    //const __m128 e = _mm_hadd_ps(d, d);
    //return _mm_cvtss_f32(e);
    const math::vec4_t<float> ret{_mm_mul_ps(va, vb)};
    return ret[0] + ret[1] + ret[2];
}
*/

/*-------------------------------------
    3D Magnitude
-------------------------------------*/
template <>
inline
float length(const vec3_t<float>& v)
{
    // cache
    const __m128 s = _mm_set_ps(v.v[0], v.v[1], v.v[2], 0.f);

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xA1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(_mm_sqrt_ps(e));
}



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Dot
-------------------------------------*/
/*
template <> inline
float dot<float>(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    //__m128 a = _mm_mul_ps(v1.simd, v2.simd);
    //__m128 b = _mm_hadd_ps(a, a);
    //__m128 c = _mm_hadd_ps(b, b);
    //return _mm_cvtss_f32(c);
}
*/

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
template <>
inline
float length(const vec4_t<float>& v)
{
    // cache
    const __m128 s = v.simd;

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xA1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(_mm_sqrt_ps(e));
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
/*
template <>
inline
math::vec4_t<float> normalize(const vec4_t<float>& v)
{
    // cache
    const __m128 s = v.simd;

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xA1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    // normalization
    return vec4_t<float>{_mm_mul_ps(s, _mm_rsqrt_ps(e))};
}
*/



} // end math namespace
} // end ls namespace
