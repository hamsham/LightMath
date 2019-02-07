
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
template<> inline LS_INLINE
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
    3D Cross
-------------------------------------*/
inline LS_INLINE vec3_t<float> cross(const vec3_t<float>& v1, const vec3_t<float>& v2) {
    union
    {
        vec3_t<float> vec;
        __m128 simd;
    } a{v1}, b{v2}, ret;

    const __m128 yzxA = _mm_shuffle_ps(a.simd, a.simd, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 yzxB = _mm_shuffle_ps(b.simd, b.simd, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 c = _mm_sub_ps(_mm_mul_ps(a.simd, yzxB), _mm_mul_ps(yzxA, b.simd));

    ret.simd = _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1));
    return ret.vec;
}

/*-------------------------------------
    3D Magnitude
-------------------------------------*/
inline LS_INLINE float length(const vec3_t<float>& v)
{
    // cache
    const __m128 s = _mm_set_ps(v.v[0], v.v[1], v.v[2], 0.f);

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



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Sum
-------------------------------------*/
inline LS_INLINE float sum(const vec4_t<float>& v)
{
    // horizontal add
    const __m128 a = v.simd;

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(e);
}

/*-------------------------------------
    4D Reciprocal Sum
-------------------------------------*/
inline LS_INLINE float sum_inv(const vec4_t<float>& v)
{
    // horizontal add
    const __m128 a = v.simd;

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(_mm_rcp_ps(e));
}

/*-------------------------------------
    4D Cross
-------------------------------------*/
inline LS_INLINE vec4_t<float> cross(const vec4_t<float>& v1, const vec4_t<float>& v2) {
    const __m128 a = v1.simd;
    const __m128 b = v2.simd;
    const __m128 yzxA = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 yzxB = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 c = _mm_sub_ps(_mm_mul_ps(a, yzxB), _mm_mul_ps(yzxA, b));

    return vec4_t<float>{_mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1))};
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
inline LS_INLINE float dot(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    // horizontal add
    const __m128 a = _mm_mul_ps(v1.simd, v2.simd);

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
inline LS_INLINE float length(const vec4_t<float>& v)
{
    // cache
    const __m128 s = v.simd;

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(_mm_rcp_ps(_mm_rsqrt_ps(e)));
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
inline LS_INLINE math::vec4_t<float> normalize(const vec4_t<float>& v)
{
    // cache
    const __m128 s = v.simd;

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    // normalization
    return vec4_t<float>{_mm_mul_ps(s, _mm_rsqrt_ps(e))};
}

/*-------------------------------------
    4D Min
-------------------------------------*/
inline LS_INLINE vec4_t<float> min(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return math::vec4_t<float>{_mm_min_ps(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
inline LS_INLINE vec4_t<float> max(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return math::vec4_t<float>{_mm_max_ps(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D RCP
-------------------------------------*/
inline LS_INLINE vec4_t<float> rcp(const vec4_t<float>& v)
{
    return vec4_t<float>{_mm_rcp_ps(v.simd)};
}

/*-------------------------------------
    4D Sign Bits
-------------------------------------*/
inline LS_INLINE int sign_bits(const vec4_t<float>& x) noexcept
{
    return _mm_movemask_ps(x.simd);
}

/*-------------------------------------
    4D floor
-------------------------------------*/
inline LS_INLINE vec4_t<float> floor(const vec4_t<float>& v)
{
    return vec4_t<float> {_mm_floor_ps(v.simd)};
}

/*-------------------------------------
    4D ceil
-------------------------------------*/
inline LS_INLINE vec4_t<float> ceil(const vec4_t<float>& v)
{
    return vec4_t<float> {_mm_ceil_ps(v.simd)};
}

/*-------------------------------------
    4D round
-------------------------------------*/
inline LS_INLINE vec4_t<float> round(const vec4_t<float>& v)
{
    return vec4_t<float> {_mm_round_ps(v.simd, _MM_FROUND_TO_NEAREST_INT)};
}



/*-------------------------------------
    fast_log2

    Fast Approximate logarithms
    This method was found on flipcode:
        http://www.flipcode.com/archives/Fast_log_Function.shtml
    Accurate to within 5 decimal places.
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE vec4_t<float> fast_log2(const vec4_t<float>& n) noexcept
{
    __m128 exp = n.simd;
    __m128i x = _mm_castps_si128(exp);

    const __m128i log2 = _mm_sub_epi32(_mm_and_si128(_mm_srai_epi32(x, 23), _mm_set1_epi32(255)), _mm_set1_epi32(128));

    x = _mm_and_si128(x, _mm_set1_epi32(~(255 << 23)));
    x = _mm_add_epi32(x, _mm_set1_epi32(127 << 23));

    exp = _mm_castsi128_ps(x);
    __m128 ret;
    ret = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(-0.3333333333f), exp), _mm_set1_ps(2.f));
    ret = _mm_sub_ps(_mm_mul_ps(ret, exp), _mm_set1_ps(0.6666666666f));
    return vec4_t<float>{_mm_add_ps(ret, _mm_cvtepi32_ps(log2))};
}



/*-------------------------------------
    fast_log
-------------------------------------*/
inline LS_INLINE vec4_t<float> fast_log(const vec4_t<float>& n) noexcept
{
    const math::vec4_t<float> x = fast_log2(n);
    return math::vec4_t<float>{_mm_mul_ps(x.simd, _mm_set1_ps(0.693147181f))}; // ln( 2 )
}



/*-------------------------------------
    fast_logN
-------------------------------------*/
inline LS_INLINE vec4_t<float> fast_logN(const vec4_t<float>& baseN, const vec4_t<float>& n) noexcept
{
    const math::vec4_t<float> x = fast_log(n);
    const math::vec4_t<float> b = fast_log2(baseN);
    return math::vec4_t<float>{_mm_mul_ps(x.simd, _mm_rcp_ps(b.simd))};
}



/*-------------------------------------
    exp
-------------------------------------*/
inline LS_INLINE vec4_t<float> exp(const vec4_t<float>& x) noexcept
{
    __m128 s = _mm_add_ps(_mm_set1_ps(1.f), _mm_mul_ps(x.simd, _mm_set1_ps(1.f/256.f)));
    s = _mm_mul_ps(s, s);
    s = _mm_mul_ps(s, s);
    s = _mm_mul_ps(s, s);
    s = _mm_mul_ps(s, s);
    s = _mm_mul_ps(s, s);
    s = _mm_mul_ps(s, s);
    s = _mm_mul_ps(s, s);
    s = _mm_mul_ps(s, s);

    return math::vec4_t<float>{s};
}



/*-------------------------------------
    pow
-------------------------------------*/
inline LS_INLINE vec4_t<float> pow(const vec4_t<float>& x, const vec4_t<float>& y) noexcept
{
    return math::exp(math::fast_log(x) * y);
}


} // end math namespace
} // end ls namespace
