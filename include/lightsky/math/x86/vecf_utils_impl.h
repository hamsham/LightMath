
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
inline LS_INLINE float dot(const vec3_t<float>& v1, const vec3_t<float>& v2)
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
    const vec4_t<float> ret{_mm_mul_ps(va, vb)};
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

    const __m128 yzxA = _mm_permute_ps(a.simd, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 yzxB = _mm_permute_ps(b.simd, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 c = _mm_fmsub_ps(a.simd, yzxB, _mm_mul_ps(yzxA, b.simd));

    ret.simd = _mm_permute_ps(c, _MM_SHUFFLE(3, 0, 2, 1));
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
    const __m128 b = _mm_permute_ps(a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_permute_ps(c, 0x0F);
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
    const __m128 b = _mm_permute_ps(a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_permute_ps(c, 0x0F);
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
    const __m128 b = _mm_permute_ps(a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_permute_ps(c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(_mm_rcp_ps(e));
}

/*-------------------------------------
    4D Cross
-------------------------------------*/
inline LS_INLINE vec4_t<float> cross(const vec4_t<float>& v1, const vec4_t<float>& v2) {
    const __m128 a = v1.simd;
    const __m128 b = v2.simd;
    const __m128 yzxA = _mm_permute_ps(a, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 yzxB = _mm_permute_ps(b, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 c = _mm_fmsub_ps(a, yzxB, _mm_mul_ps(yzxA, b));

    return vec4_t<float>{_mm_permute_ps(c, _MM_SHUFFLE(3, 0, 2, 1))};
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
inline LS_INLINE float dot(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    // horizontal add
    const __m128 a = _mm_mul_ps(v1.simd, v2.simd);

    // swap the words of each vector
    const __m128 b = _mm_permute_ps(a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_permute_ps(c, 0x0F);
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
    const __m128 b = _mm_permute_ps(a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_permute_ps(c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    return _mm_cvtss_f32(_mm_rcp_ps(_mm_rsqrt_ps(e)));
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
inline LS_INLINE vec4_t<float> normalize(const vec4_t<float>& v)
{
    // cache
    const __m128 s = v.simd;

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_permute_ps(a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_permute_ps(c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    // normalization
    return vec4_t<float>{_mm_mul_ps(s, _mm_rsqrt_ps(e))};
}

/*-------------------------------------
    4D Mix
-------------------------------------*/
inline LS_INLINE math::vec4_t<float> mix(const vec4_t<float>& v1, const vec4_t<float>& v2, float percent)
{
    const __m128 p = _mm_set1_ps(percent);
    const __m128 v = _mm_sub_ps(v2.simd, v1.simd);
    return vec4_t<float>{_mm_fmadd_ps(v, p, v1.simd)};
}

/*-------------------------------------
    4D Reflect
-------------------------------------*/
inline LS_INLINE vec4_t<float> reflect(const vec4_t<float>& v, const vec4_t<float>& norm) {
    //return v - vec4_t<num_t>{2} * dot(v, norm) * norm;
    // horizontal add
    const __m128 vs = v.simd;
    const __m128 ns = norm.simd;

    const __m128 a = _mm_mul_ps(vs, ns);

    // swap the words of each vector
    const __m128 b = _mm_permute_ps(a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_permute_ps(c, 0x0F);
    const __m128 dp = _mm_add_ps(c, d);

    const __m128 reflection = _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(2.f), dp), ns);
    return vec4_t<float>{_mm_sub_ps(vs, reflection)};
}

/*-------------------------------------
    4D Min
-------------------------------------*/
inline LS_INLINE vec4_t<float> min(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return vec4_t<float>{_mm_min_ps(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
inline LS_INLINE vec4_t<float> max(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return vec4_t<float>{_mm_max_ps(v1.simd, v2.simd)};
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
inline LS_INLINE int sign_mask(const vec4_t<float>& x) noexcept
{
    return _mm_movemask_ps(x.simd);
}

/*-------------------------------------
    sign
-------------------------------------*/
inline LS_INLINE vec4_t<float> sign(const vec4_t<float>& x) noexcept
{
    return vec4_t<float>{_mm_and_ps(_mm_cmplt_ps(x.simd, _mm_setzero_ps()), _mm_set1_ps(1.f))};
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
    log2

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE vec4_t<float> log2(const vec4_t<float>& n) noexcept
{
    #if 0
    __m128 exp = n.simd;
    __m128i x = _mm_castps_si128(exp);

    const __m128i log2 = _mm_sub_epi32(_mm_and_si128(_mm_srai_epi32(x, 23), _mm_set1_epi32(255)), _mm_set1_epi32(128));

    x = _mm_and_si128(x, _mm_set1_epi32(~(255 << 23)));
    x = _mm_add_epi32(x, _mm_set1_epi32(127 << 23));

    exp = _mm_castsi128_ps(x);
    __m128 ret;
    ret = _mm_fmadd_ps(_mm_set1_ps(-0.333333333333f), exp, _mm_set1_ps(2.f));
    ret = _mm_fmsub_ps(ret, exp, _mm_set1_ps(0.666666666666f));
    return vec4_t<float>{_mm_add_ps(ret, _mm_cvtepi32_ps(log2))};
    #else
    const __m128  vx  = n.simd;
    const __m128i vxi = _mm_castps_si128(vx);
    const __m128i mx  = _mm_or_si128(_mm_and_si128(vxi, _mm_set1_epi32(0x007FFFFFu)), _mm_set1_epi32(0x3f000000u));
    const __m128  mxf = _mm_castsi128_ps(mx);
    const __m128  d   = _mm_fmsub_ps(_mm_set1_ps(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi), _mm_set1_ps(124.22551499f));
    const __m128  a   = _mm_rcp_ps(_mm_add_ps(_mm_set1_ps(0.3520887068f), mxf));
    const __m128  c   = _mm_mul_ps(_mm_set1_ps(1.498030302f), mxf);
    const __m128  b   = _mm_mul_ps(_mm_set1_ps(1.72587999f), a);

    return vec4_t<float>{_mm_sub_ps(_mm_sub_ps(d, c), b)};
    #endif
}



/*-------------------------------------
    log

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE vec4_t<float> log(const vec4_t<float>& n) noexcept
{
    const __m128  vx  = n.simd;
    const __m128i vxi = _mm_castps_si128(vx);
    const __m128i mx  = _mm_or_si128(_mm_and_si128(vxi, _mm_set1_epi32(0x007FFFFFu)), _mm_set1_epi32(0x3f000000u));
    const __m128  mxf = _mm_castsi128_ps(mx);
    const __m128  d   = _mm_fmsub_ps(_mm_set1_ps(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi), _mm_set1_ps(124.22551499f));
    const __m128  a   = _mm_rcp_ps(_mm_add_ps(_mm_set1_ps(0.3520887068f), mxf));
    const __m128  c   = _mm_mul_ps(_mm_set1_ps(1.498030302f), mxf);
    const __m128  b   = _mm_mul_ps(_mm_set1_ps(1.72587999f), a);
    const __m128  ln2 = _mm_set1_ps(0.69314718056f);

    return vec4_t<float>{_mm_mul_ps(ln2, _mm_sub_ps(_mm_sub_ps(d, c), b))};
}



/*-------------------------------------
    log10
-------------------------------------*/
inline LS_INLINE vec4_t<float> log10(const vec4_t<float>& n) noexcept
{
    const vec4_t<float> x = log2(n);
    return vec4_t<float>{_mm_mul_ps(x.simd, _mm_set1_ps(0.3010299956639812f))}; // log2( 10 )
}



/*-------------------------------------
    logN
-------------------------------------*/
inline LS_INLINE vec4_t<float> logN(const vec4_t<float>& baseN, const vec4_t<float>& n) noexcept
{
    const vec4_t<float> x = log(n);
    const vec4_t<float> b = log2(baseN);
    return vec4_t<float>{_mm_mul_ps(x.simd, _mm_rcp_ps(b.simd))};
}



/*-------------------------------------
    exp
    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE vec4_t<float> exp(const vec4_t<float>& x) noexcept
{
    #ifdef LS_MATH_HIGH_PREC
        __m128 p = _mm_mul_ps(_mm_set1_ps(x), _mm_set1_ps(1.442695040f)); // x * 1/ln(2)
        __m128 ltzero = _mm_cmplt_ps(p, _mm_setzero_ps());
        __m128 offset = _mm_and_ps(ltzero, _mm_set1_ps(1.f));
        __m128 lt126 = _mm_cmplt_ps(p, _mm_set1_ps(-126.f));
        __m128 clipp = _mm_or_ps(_mm_and_ps(lt126, _mm_set1_ps(-126.f)), _mm_andnot_ps(lt126, p));
        __m128 w = _mm_round_ps(clipp, _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC);
        __m128 z = _mm_add_ps(_mm_sub_ps(clipp, w), offset);

        const __m128 d = _mm_add_ps(_mm_set1_ps(121.2740575f), clipp);
        const __m128 c = _mm_mul_ps(_mm_set1_ps(1.49012907f), z);
        const __m128 a = _mm_sub_ps(_mm_set1_ps(4.84252568f), z);
        const __m128 b = _mm_div_ps(_mm_set1_ps(27.7280233f), a);

        const __m128 e = _mm_add_ps(b, d);
        const __m128 f = _mm_sub_ps(e, c);

        const __m128i v = _mm_cvtps_epi32(_mm_mul_ps(_mm_set1_ps((float)(1 << 23)), f));

        return vec4_t<float>{_mm_castsi128_ps(v)};
    #else
        const __m128 p      = _mm_mul_ps(x.simd, _mm_set1_ps(1.442695040f)); // x * 1/ln(2)
        const __m128 lt126  = _mm_cmplt_ps(p, _mm_set1_ps(-126.f));
        const __m128 clipp  = _mm_or_ps(_mm_andnot_ps (lt126, p), _mm_and_ps(lt126, _mm_set1_ps(-126.f)));
        const __m128 clipp2 = _mm_add_ps(clipp, _mm_set1_ps(126.94269504f));
        const __m128i v     = _mm_cvtps_epi32(_mm_mul_ps(_mm_set1_ps((float)(1 << 23)), clipp2));

        return vec4_t<float>{_mm_castsi128_ps(v)};
    #endif
}



/*-------------------------------------
    exp2
    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE vec4_t<float> exp2(const vec4_t<float>& x) noexcept
{
    #ifdef LS_MATH_HIGH_PREC
        __m128 p = _mm_set1_ps(x);
        __m128 ltzero = _mm_castsi128_ps(_mm_srai_epi32(_mm_castps_si128(p), 31);
        __m128 offset = _mm_and_ps(ltzero, _mm_set1_ps(1.f));
        __m128 lt126 = _mm_cmplt_ps(p, _mm_set1_ps(-126.f));
        __m128 clipp = _mm_or_ps(_mm_and_ps(lt126, _mm_set1_ps(-126.f)), _mm_andnot_ps(lt126, p));
        __m128 w = _mm_round_ps(clipp, _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC);
        __m128 z = _mm_add_ps(_mm_sub_ps(clipp, w), offset);

        const __m128 d = _mm_add_ps(_mm_set1_ps(121.2740575f), clipp);
        const __m128 c = _mm_mul_ps(_mm_set1_ps(1.49012907f), z);
        const __m128 a = _mm_sub_ps(_mm_set1_ps(4.84252568f), z);
        const __m128 b = _mm_div_ps(_mm_set1_ps(27.7280233f), a);

        const __m128 e = _mm_add_ps(b, d);
        const __m128 f = _mm_sub_ps(e, c);

        const __m128i v = _mm_cvtps_epi32(_mm_mul_ps(_mm_set1_ps((float)(1 << 23)), f));

        return vec4_t<float>{_mm_castsi128_ps(v)};
    #else
        const __m128 p      = x.simd;
        const __m128 lt126  = _mm_cmplt_ps(p, _mm_set1_ps(-126.f));
        const __m128 clipp  = _mm_or_ps(_mm_andnot_ps (lt126, p), _mm_and_ps(lt126, _mm_set1_ps(-126.f)));
        const __m128 clipp2 = _mm_add_ps(clipp, _mm_set1_ps(126.94269504f));
        const __m128i v     = _mm_cvtps_epi32(_mm_mul_ps(_mm_set1_ps((float)(1 << 23)), clipp2));

        return vec4_t<float>{_mm_castsi128_ps(v)};
    #endif
}



/*-------------------------------------
    pow
-------------------------------------*/
inline LS_INLINE vec4_t<float> pow(const vec4_t<float>& x, const vec4_t<float>& y) noexcept
{
    return exp2(log2(x) * y);
}



/*-------------------------------------
    FMA
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmadd(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    return vec4_t<float>{_mm_fmadd_ps(x.simd, m.simd, a.simd)};
}



/*-------------------------------------
    FMS
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmsub(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    return vec4_t<float>{_mm_fmsub_ps(x.simd, m.simd, a.simd)};
}


} // end math namespace
} // end ls namespace
