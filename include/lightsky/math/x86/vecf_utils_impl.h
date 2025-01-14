
#ifndef LS_MATH_VECF_UTILS_IMPL_H
#define LS_MATH_VECF_UTILS_IMPL_H

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
inline LS_INLINE float dot(const vec3_t<float>& v1, const vec3_t<float>& v2) noexcept
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
inline LS_INLINE vec3_t<float> cross(const vec3_t<float>& v1, const vec3_t<float>& v2) noexcept
{
    const __m128 a = _mm_set_ps(0.f, v1.v[2], v1.v[1], v1.v[0]);
    const __m128 b = _mm_set_ps(0.f, v2.v[2], v2.v[1], v2.v[0]);

    const __m128 yzxA = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 yzxB = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));

    #ifdef LS_X86_FMA
        const __m128 c = _mm_fmsub_ps(a, yzxB, _mm_mul_ps(yzxA, b));
    #else
        const __m128 c = _mm_sub_ps(_mm_mul_ps(a, yzxB), _mm_mul_ps(yzxA, b));
    #endif

    union
    {
        __m128 simd;
        vec3_t<float> vec;
    } ret{_mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1))};

    return ret.vec;
}

/*-------------------------------------
    3D Magnitude
-------------------------------------*/
inline LS_INLINE float length(const vec3_t<float>& v) noexcept
{
    // cache
    const __m128 s = _mm_set_ps(v.v[0], v.v[1], v.v[2], 0.f);

    // horizontal add
    const __m128 a = _mm_mul_ps(s, s);

    // swap the words of each vector
    const __m128 b = _mm_movehdup_ps(a);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_movehl_ps(c, c);
    const __m128 e = _mm_add_ss(c, d);

    return _mm_cvtss_f32(_mm_sqrt_ss(e));
}



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Sum
-------------------------------------*/
inline LS_INLINE float sum(const vec4_t<float>& v) noexcept
{
    // horizontal add
    const __m128 a = v.simd;

    // swap the words of each vector
    const __m128 b = _mm_movehdup_ps(a);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_movehl_ps(c, c);
    const __m128 e = _mm_add_ss(c, d);

    return _mm_cvtss_f32(e);
}

/*-------------------------------------
    4D Reciprocal Sum
-------------------------------------*/
inline LS_INLINE float sum_inv(const vec4_t<float>& v) noexcept
{
    // horizontal add
    const __m128 a = v.simd;

    // swap the words of each vector
    const __m128 b = _mm_movehdup_ps(a);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_movehl_ps(c, c);
    const __m128 e = _mm_add_ss(c, d);

    return _mm_cvtss_f32(_mm_rcp_ss(e));
}

/*-------------------------------------
    4D Cross
-------------------------------------*/
inline LS_INLINE vec4_t<float> cross(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    const __m128 yzxA = _mm_shuffle_ps(v1.simd, v1.simd, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 yzxB = _mm_shuffle_ps(v2.simd, v2.simd, _MM_SHUFFLE(3, 0, 2, 1));
    #ifdef LS_X86_FMA
        const __m128 ret = _mm_fmsub_ps(v1.simd, yzxB, _mm_mul_ps(yzxA, v2.simd));
    #else
        const __m128 ret = _mm_sub_ps(_mm_mul_ps(v1.simd, yzxB), _mm_mul_ps(yzxA, v2.simd));
    #endif
    return vec4_t<float>{_mm_shuffle_ps(ret, ret, _MM_SHUFFLE(3, 0, 2, 1))};
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
inline LS_INLINE float dot(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    // horizontal add
    const __m128 a = _mm_mul_ps(v1.simd, v2.simd);

    // swap the words of each vector
    const __m128 b = _mm_movehdup_ps(a);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_movehl_ps(c, c);
    const __m128 e = _mm_add_ss(c, d);

    return _mm_cvtss_f32(e);
}

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
inline LS_INLINE float length(const vec4_t<float>& v) noexcept
{
    // horizontal add
    const __m128 a = _mm_mul_ps(v.simd, v.simd);

    // swap the words of each vector
    const __m128 b = _mm_movehdup_ps(a);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_unpackhi_ps(c, c);
    const __m128 e = _mm_add_ss(c, d);

    return _mm_cvtss_f32(_mm_sqrt_ss(e));
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
inline LS_INLINE vec4_t<float> normalize(const vec4_t<float>& v) noexcept
{
    // horizontal add
    const __m128 a = _mm_mul_ps(v.simd, v.simd);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 e = _mm_add_ps(c, d);

    // normalization
    return vec4_t<float>{_mm_mul_ps(v.simd, _mm_rcp_ps(_mm_sqrt_ps(e)))};
}

/*-------------------------------------
    4D Mix
-------------------------------------*/
inline LS_INLINE vec4_t<float> mix(const vec4_t<float>& v1, const vec4_t<float>& v2, float percent) noexcept
{
    const __m128 p = _mm_set1_ps(percent);
    const __m128 v = _mm_sub_ps(v2.simd, v1.simd);

    #ifdef LS_X86_FMA
        return vec4_t<float>{_mm_fmadd_ps(v, p, v1.simd)};
    #else
        return vec4_t<float>{_mm_add_ps(_mm_mul_ps(v, p), v1.simd)};
    #endif
}

/*-------------------------------------
    4D Reflect
-------------------------------------*/
inline LS_INLINE vec4_t<float> reflect(const vec4_t<float>& v, const vec4_t<float>& norm) noexcept
{
    //return v - vec4_t<num_t>{2} * dot(v, norm) * norm;
    // horizontal add
    const __m128 vs = v.simd;
    const __m128 ns = norm.simd;

    const __m128 a = _mm_mul_ps(vs, ns);

    // swap the words of each vector
    const __m128 b = _mm_shuffle_ps(a, a, 0xB1);
    const __m128 c = _mm_add_ps(a, b);

    // swap each half of the vector
    const __m128 d = _mm_shuffle_ps(c, c, 0x0F);
    const __m128 dp = _mm_add_ps(c, d);

    const __m128 reflection = _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(2.f), dp), ns);
    return vec4_t<float>{_mm_sub_ps(vs, reflection)};
}

/*-------------------------------------
    4D Min
-------------------------------------*/
inline LS_INLINE vec4_t<float> min(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    return vec4_t<float>{_mm_min_ps(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
inline LS_INLINE vec4_t<float> max(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    return vec4_t<float>{_mm_max_ps(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Clamp
-------------------------------------*/
inline LS_INLINE vec4_t<float> clamp(const vec4_t<float>& v, const vec4_t<float>& minVals, const vec4_t<float>& maxVals) noexcept
{
    return vec4_t<float>{_mm_min_ps(maxVals.simd, _mm_max_ps(v.simd, minVals.simd))};
}

/*-------------------------------------
    4D Saturate
-------------------------------------*/
inline LS_INLINE vec4_t<float> saturate(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{_mm_min_ps(_mm_and_ps(v.simd, _mm_castsi128_ps(_mm_set1_epi32(0x3FFFFFFF))), _mm_set1_ps(1.f))};
}

/*-------------------------------------
    4D Step
-------------------------------------*/
inline LS_INLINE vec4_t<float> step(const vec4_t<float>& edge, const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{_mm_and_ps(_mm_cmpge_ps(v.simd, edge.simd), _mm_set1_ps(1.f))};
}

/*-------------------------------------
    4D Smoothstep
-------------------------------------*/
inline LS_INLINE vec4_t<float> smoothstep(const vec4_t<float>& a, const vec4_t<float>& b, const vec4_t<float>& x) noexcept
{
    const __m128 xa = _mm_sub_ps(x.simd, a.simd);
    const __m128 xb = _mm_sub_ps(b.simd, a.simd);
    const __m128 d = _mm_div_ps(xa, xb);
    const __m128 clamped = _mm_min_ps(_mm_set1_ps(1.f), _mm_max_ps(_mm_setzero_ps(), d));

    #ifdef LS_X86_FMA
        const __m128 n = _mm_fnmadd_ps(_mm_set1_ps(2.f), clamped, _mm_set1_ps(3.f));
    #else
        const __m128 n = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(-2.f), clamped), _mm_set1_ps(3.f));
    #endif

    return vec4_t<float>{_mm_mul_ps(n, _mm_mul_ps(clamped, clamped))};
}

/*-------------------------------------
    4D RCP
-------------------------------------*/
inline LS_INLINE vec4_t<float> rcp(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{_mm_rcp_ps(v.simd)};
}

/*-------------------------------------
    4D Sign Bits (int)
-------------------------------------*/
inline LS_INLINE int sign_mask(const vec4_t<int32_t>& x) noexcept
{
    const __m128i v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(x.v));
    return _mm_movemask_ps(_mm_castsi128_ps(v));
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
    Create a value with the magnitude of n and sign of s
-------------------------------------*/
inline LS_INLINE vec4_t<float> copysign(const vec4_t<float>& n, const vec4_t<float>& s) noexcept
{
    const __m128 a = _mm_and_ps(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)), s.simd);
    const __m128 b = _mm_and_ps(_mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)), n.simd);
    return vec4_t<float>{_mm_or_ps(a, b)};
}

/*-------------------------------------
    4D floor
-------------------------------------*/
inline LS_INLINE vec4_t<float> floor(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{_mm_floor_ps(v.simd)};
}

/*-------------------------------------
    4D ceil
-------------------------------------*/
inline LS_INLINE vec4_t<float> ceil(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{_mm_ceil_ps(v.simd)};
}

/*-------------------------------------
    4D round
-------------------------------------*/
inline LS_INLINE vec4_t<float> round(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{_mm_round_ps(v.simd, _MM_FROUND_TO_NEAREST_INT)};
}

/*-------------------------------------
    4D abs
-------------------------------------*/
inline LS_INLINE vec4_t<float> abs(const vec4_t<float>& v) noexcept
{
    const __m128 sign = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
    return vec4_t<float>{_mm_xor_ps(_mm_or_ps(v.simd, sign), sign)};
}



/*-------------------------------------
    log2

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE vec4_t<float> log2(const vec4_t<float>& n) noexcept
{
    const __m128i vxi = _mm_castps_si128(n.simd);
    const __m128i mx  = _mm_or_si128(_mm_and_si128(vxi, _mm_set1_epi32(0x007FFFFFu)), _mm_set1_epi32(0x3f000000u));
    const __m128  mxf = _mm_castsi128_ps(mx);
    const __m128  a   = _mm_rcp_ps(_mm_add_ps(_mm_set1_ps(0.3520887068f), mxf));

    #if defined(LS_X86_FMA)
        const __m128 b = _mm_fmadd_ps(_mm_set1_ps(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi), _mm_set1_ps(-124.22551499f));
        const __m128 c = _mm_fmadd_ps(_mm_set1_ps(-1.498030302f), mxf, b);
        const __m128 d = _mm_fmadd_ps(_mm_set1_ps(-1.72587999f), a, c);
        return vec4_t<float>{d};

    #else
        const __m128 b = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi)), _mm_set1_ps(-124.22551499f));
        const __m128 c = _mm_mul_ps(_mm_set1_ps(-1.498030302f), mxf);
        const __m128 d = _mm_mul_ps(_mm_set1_ps(-1.72587999f), a);
        return vec4_t<float>{_mm_add_ps(_mm_add_ps(b, c), d)};
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
    const __m128i vxi = _mm_castps_si128(n.simd);
    const __m128i mx  = _mm_or_si128(_mm_and_si128(vxi, _mm_set1_epi32(0x007FFFFFu)), _mm_set1_epi32(0x3f000000u));
    const __m128  mxf = _mm_castsi128_ps(mx);
    const __m128  a   = _mm_rcp_ps(_mm_add_ps(_mm_set1_ps(0.3520887068f), mxf));

    #if defined(LS_X86_FMA)
        const __m128 b   = _mm_fmadd_ps(_mm_set1_ps(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi), _mm_set1_ps(-124.22551499f));
        const __m128 c   = _mm_fmadd_ps(_mm_set1_ps(-1.498030302f), mxf, b);
        const __m128 d   = _mm_fmadd_ps(_mm_set1_ps(-1.72587999f), a, c);
        const __m128 ln2 = _mm_set1_ps(0.69314718056f);
        return vec4_t<float>{_mm_mul_ps(ln2, d)};

    #else
        const __m128 b   = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi)), _mm_set1_ps(-124.22551499f));
        const __m128 c   = _mm_mul_ps(_mm_set1_ps(-1.498030302f), mxf);
        const __m128 d   = _mm_mul_ps(_mm_set1_ps(-1.72587999f), a);
        const __m128 ln2 = _mm_set1_ps(0.6931471805599453f);
        return vec4_t<float>{_mm_mul_ps(ln2, _mm_add_ps(_mm_add_ps(b, c), d))};
    #endif
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
    #if defined(LS_MATH_HIGH_PREC)
        const __m128 p = _mm_mul_ps(_mm_set1_ps(x), _mm_set1_ps(1.442695040f)); // x * 1/ln(2)
        const __m128 s126   = _mm_set1_ps(-126.f);
        const __m128 ltzero = _mm_cmplt_ps(p, _mm_setzero_ps());
        const __m128 offset = _mm_and_ps(ltzero, _mm_set1_ps(1.f));
        const __m128 clipp  = _mm_max_ps(p, s126);
        const __m128 w = _mm_round_ps(clipp, _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC);
        const __m128 z = _mm_add_ps(_mm_sub_ps(clipp, w), offset);

        const __m128 d = _mm_add_ps(_mm_set1_ps(121.2740575f), clipp);
        const __m128 c = _mm_mul_ps(_mm_set1_ps(1.49012907f), z);
        const __m128 a = _mm_sub_ps(_mm_set1_ps(4.84252568f), z);
        const __m128 b = _mm_div_ps(_mm_set1_ps(27.7280233f), a);

        const __m128 e = _mm_add_ps(b, d);
        const __m128 f = _mm_sub_ps(e, c);

        const __m128i v = _mm_cvtps_epi32(_mm_mul_ps(_mm_set1_ps((float)(1 << 23)), f));

        return vec4_t<float>{_mm_castsi128_ps(v)};
    #else
        const __m128 s126   = _mm_set1_ps(-126.f);
        const __m128 p      = _mm_mul_ps(x.simd, _mm_set1_ps(1.4426950408889634f)); // x * 1/ln(2)
        const __m128 clipp  = _mm_max_ps(p, s126);
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
    #if defined(LS_MATH_HIGH_PREC)
        const __m128 p = _mm_set1_ps(x);
        const __m128 s126   = _mm_set1_ps(-126.f);
        const __m128 ltzero = _mm_castsi128_ps(_mm_srai_epi32(_mm_castps_si128(p), 31));
        const __m128 offset = _mm_and_ps(ltzero, _mm_set1_ps(1.f));
        const __m128 clipp  = _mm_max_ps(p, s126);
        const __m128 w = _mm_round_ps(clipp, _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC);
        const __m128 z = _mm_add_ps(_mm_sub_ps(clipp, w), offset);

        const __m128 d = _mm_add_ps(_mm_set1_ps(121.2740575f), clipp);
        const __m128 c = _mm_mul_ps(_mm_set1_ps(1.49012907f), z);
        const __m128 a = _mm_sub_ps(_mm_set1_ps(4.84252568f), z);
        const __m128 b = _mm_div_ps(_mm_set1_ps(27.7280233f), a);

        const __m128 e = _mm_add_ps(b, d);
        const __m128 f = _mm_sub_ps(e, c);

        const __m128i v = _mm_cvtps_epi32(_mm_mul_ps(_mm_set1_ps((float)(1 << 23)), f));

        return vec4_t<float>{_mm_castsi128_ps(v)};

    #else
        const __m128 s126   = _mm_set1_ps(-126.f);
        const __m128 p      = x.simd;
        const __m128 clipp  = _mm_max_ps(p, s126);
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
    return exp(log(x) * y);
}



/*-------------------------------------
    FMA
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmadd(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    #ifdef LS_X86_FMA
        return vec4_t<float>{_mm_fmadd_ps(x.simd, m.simd, a.simd)};
    #else
        return vec4_t<float>{_mm_add_ps(_mm_mul_ps(x.simd, m.simd), a.simd)};
    #endif
}



/*-------------------------------------
    FMS
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmsub(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    #ifdef LS_X86_FMA
        return vec4_t<float>{_mm_fmsub_ps(x.simd, m.simd, a.simd)};
    #else
        return vec4_t<float>{_mm_sub_ps(_mm_mul_ps(x.simd, m.simd), a.simd)};
    #endif
}



} // end math namespace
} // end ls namespace

#endif /* LS_MATH_VECF_UTILS_IMPL_H */
