
#ifndef LS_MATH_SCALARF_UTILS_IMPL_H
#define LS_MATH_SCALARF_UTILS_IMPL_H

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
    const __m128 v0 = _mm_min_ss(_mm_set_ss(a), _mm_set_ss(b));
    const __m128 v1 = _mm_set_ss(c);

    return _mm_cvtss_f32(_mm_min_ss(v1, v0));
}

/*-------------------------------------
    min
-------------------------------------*/
inline LS_INLINE float min(float a, float b, float c, float d) noexcept
{
    const __m128 v0 = _mm_min_ss(_mm_set_ss(a), _mm_set_ss(b));
    const __m128 v1 = _mm_min_ss(_mm_set_ss(c), _mm_set_ss(d));

    return _mm_cvtss_f32(_mm_min_ss(v1, v0));
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
    const __m128 v0 = _mm_max_ss(_mm_set_ss(a), _mm_set_ss(b));
    const __m128 v1 = _mm_set_ss(c);

    return _mm_cvtss_f32(_mm_max_ss(v1, v0));
}

/*-------------------------------------
    max
-------------------------------------*/
inline LS_INLINE float max(float a, float b, float c, float d) noexcept
{
    const __m128 v0 = _mm_max_ss(_mm_set_ss(a), _mm_set_ss(b));
    const __m128 v1 = _mm_max_ss(_mm_set_ss(c), _mm_set_ss(d));

    return _mm_cvtss_f32(_mm_max_ss(v1, v0));
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
    #ifdef LS_X86_SSE4_1
        return _mm_cvtss_f32(_mm_floor_ps(_mm_set1_ps(n)));
    #else
        return _mm_cvtss_f32(_mm_cvtepi32_ps(_mm_cvtps_epi32(_mm_set_ss(n))));
    #endif
}



/*-------------------------------------
    ceil
-------------------------------------*/
inline LS_INLINE float ceil(float n) noexcept
{
    #ifdef LS_X86_SSE4_1
        return _mm_cvtss_f32(_mm_ceil_ps(_mm_set1_ps(n)));
    #else
        const __m128i one = _mm_set1_epi32(1);
        const __m128i c = _mm_cvtps_epi32(_mm_set_ss(n));
        return _mm_cvtss_f32(_mm_cvtepi32_ps(_mm_add_epi32(one, c)));
    #endif
}



/*-------------------------------------
    round
-------------------------------------*/
inline LS_INLINE float round(float n) noexcept
{
    #ifdef LS_X86_SSE4_1
        return _mm_cvtss_f32(_mm_round_ps(_mm_set1_ps(n), _MM_FROUND_TO_NEAREST_INT));
    #else
        const __m128i i = _mm_cvtps_epi32(_mm_add_ss(_mm_set_ss(0.5f), _mm_set_ss(n)));
        return _mm_cvtss_f32(_mm_cvtepi32_ps(i));
    #endif
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
inline LS_INLINE float inversesqrt(float x) noexcept
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
    sign_mask
-------------------------------------*/
inline LS_INLINE int sign_mask(float x) noexcept
{
    return _mm_movemask_ps(_mm_set_ss(x));
}



/*-------------------------------------
    sign
-------------------------------------*/
inline LS_INLINE float sign(float x) noexcept
{
    return _mm_cvtss_f32(_mm_and_ps(_mm_cmplt_ps(_mm_set1_ps(x), _mm_setzero_ps()), _mm_set1_ps(1.f)));
}



/*-------------------------------------
    abs
-------------------------------------*/
inline LS_INLINE float abs(float x) noexcept
{
    return _mm_cvtss_f32(_mm_and_ps(_mm_set_ss(x), _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF))));
}



/*-------------------------------------
    smoothstep
-------------------------------------*/
inline LS_INLINE float smoothstep(float a, float b, float x) noexcept
{
    const __m128 xv = _mm_set_ss(x);
    const __m128 bv = _mm_set_ss(b);
    const __m128 av = _mm_set_ss(a);

    const __m128 s0 = _mm_sub_ss(xv, av);
    const __m128 s1 = _mm_sub_ss(bv, av);
    const __m128 s2 = _mm_div_ss(s0, s1);

    const __m128 s3 = _mm_min_ss(_mm_max_ss(s2, _mm_setzero_ps()), _mm_set_ss(1.f));
    const __m128 s4 = _mm_sub_ss(_mm_set_ss(3.f), _mm_mul_ss(_mm_set_ss(2.f), s3));
    const __m128 s5 = _mm_mul_ss(s3, _mm_mul_ss(s3, s4));
    return _mm_cvtss_f32(s5);
}



/*-------------------------------------
    log2

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE float log2(float n) noexcept
{
    const __m128i vxi = _mm_castps_si128(_mm_set_ss(n));
    const __m128i mx  = _mm_or_si128(_mm_and_si128(vxi, _mm_set1_epi32(0x007FFFFFu)), _mm_set1_epi32(0x3f000000u));
    const __m128  mxf = _mm_castsi128_ps(mx);

    #ifdef LS_X86_FMA
        const __m128  d   = _mm_fmsub_ss(_mm_set_ss(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi), _mm_set_ss(124.22551499f));
    #else
        const __m128  d = _mm_sub_ss(_mm_mul_ps(_mm_set_ss(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi)), _mm_set_ss(124.22551499f));
    #endif

    const __m128  a   = _mm_rcp_ss(_mm_add_ss(_mm_set_ss(0.3520887068f), mxf));
    const __m128  c   = _mm_mul_ss(_mm_set_ss(1.498030302f), mxf);
    const __m128  b   = _mm_mul_ss(_mm_set_ss(1.72587999f), a);

    return _mm_cvtss_f32(_mm_sub_ss(_mm_sub_ss(d, c), b));
}



/*-------------------------------------
    log
    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE float log(float n) noexcept
{
    const __m128i vxi = _mm_castps_si128(_mm_set_ss(n));
    const __m128i mx  = _mm_or_si128(_mm_and_si128(vxi, _mm_set1_epi32(0x007FFFFFu)), _mm_set1_epi32(0x3f000000u));
    const __m128  mxf = _mm_castsi128_ps(mx);

    #ifdef LS_X86_FMA
        const __m128  d = _mm_fmsub_ss(_mm_set_ss(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi), _mm_set_ss(124.22551499f));
    #else
        const __m128  d = _mm_sub_ss(_mm_mul_ps(_mm_set_ss(1.1920928955078125e-7f), _mm_cvtepi32_ps(vxi)), _mm_set_ss(124.22551499f));
    #endif

    const __m128  a   = _mm_rcp_ss(_mm_add_ss(_mm_set_ss(0.3520887068f), mxf));
    const __m128  c   = _mm_mul_ss(_mm_set_ss(1.498030302f), mxf);
    const __m128  b   = _mm_mul_ss(_mm_set_ss(1.72587999f), a);
    const __m128  ln2 = _mm_set_ss(0.69314718056f);

    return _mm_cvtss_f32(_mm_mul_ss(ln2, _mm_sub_ss(_mm_sub_ss(d, c), b)));
}



/*-------------------------------------
    log10
-------------------------------------*/
inline LS_INLINE float log10(float n) noexcept
{
    const float x = log2(n);
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(x), _mm_set_ss(0.3010299956639812f))); // ln( 2 )
}



/*-------------------------------------
    logN
-------------------------------------*/
inline LS_INLINE float logN(float baseN, float n) noexcept
{
    const float x = log(n);
    const float b = log2(baseN);
    return _mm_cvtss_f32(_mm_mul_ps(_mm_set_ss(x), _mm_rcp_ps(_mm_set_ss(b))));
}



/*-------------------------------------
    exp

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE float exp(float x) noexcept
{
    /*
    __m128 s = _mm_add_ss(_mm_set_ss(1.f), _mm_mul_ss(_mm_set_ss(x), _mm_set_ss(1.f/65536.f)));

    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);

    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);

    return _mm_cvtss_f32(s);
    */

    #ifdef LS_MATH_HIGH_PREC
    __m128 p = _mm_mul_ss(_mm_set_ss(x), _mm_set_ss(1.442695040f)); // x * 1/ln(2)
    __m128 ltzero = _mm_cmplt_ss(p, _mm_setzero_ps());
    __m128 offset = _mm_and_ps(ltzero, _mm_set_ss(1.f));
    __m128 lt126 = _mm_cmplt_ss(p, _mm_set_ss(-126.f));
    __m128 clipp = _mm_or_ps(_mm_and_ps(lt126, _mm_set_ss(-126.f)), _mm_andnot_ps(lt126, p));
    __m128 w = _mm_round_ps(clipp, _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC);
    __m128 z = _mm_add_ss(_mm_sub_ss(clipp, w), offset);

    const __m128 d = _mm_add_ss(_mm_set_ss(121.2740575f), clipp);
    const __m128 c = _mm_mul_ss(_mm_set_ss(1.49012907f), z);
    const __m128 a = _mm_sub_ss(_mm_set_ss(4.84252568f), z);
    const __m128 b = _mm_div_ss(_mm_set_ss(27.7280233f), a);

    const __m128 e = _mm_add_ss(b, d);
    const __m128 f = _mm_sub_ss(e, c);

    const __m128i v = _mm_cvtps_epi32(_mm_mul_ss(_mm_set_ss((float)(1 << 23)), f));

    return _mm_cvtss_f32(_mm_castsi128_ps(v));
    #else
    const __m128 p      = _mm_mul_ss(_mm_set_ss(x), _mm_set_ss(1.442695040f)); // x * 1/ln(2)
    const __m128 lt126  = _mm_cmplt_ps(p, _mm_set_ss(-126.f));
    const __m128 clipp  = _mm_or_ps(_mm_andnot_ps (lt126, p), _mm_and_ps(lt126, _mm_set_ss(-126.f)));
    const __m128 clipp2 = _mm_add_ps(clipp, _mm_set_ss(126.94269504f));
    const __m128i v     = _mm_cvtps_epi32(_mm_mul_ps(_mm_set_ss((float)(1 << 23)), clipp2));

    return _mm_cvtss_f32(_mm_castsi128_ps(v));
    #endif
}



/*-------------------------------------
    exp2

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
inline LS_INLINE float exp2(float x) noexcept
{
    #ifdef LS_MATH_HIGH_PREC
    __m128 p = _mm_set_ss(x);
    __m128 ltzero = _mm_castsi128_ps(_mm_srai_epi32(_mm_castps_si128(p), 31);
    __m128 offset = _mm_and_ps(ltzero, _mm_set_ss(1.f));
    __m128 lt126 = _mm_cmplt_ss(p, _mm_set_ss(-126.f));
    __m128 clipp = _mm_or_ps(_mm_and_ps(lt126, _mm_set_ss(-126.f)), _mm_andnot_ps(lt126, p));
    __m128 w = _mm_round_ps(clipp, _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC);
    __m128 z = _mm_add_ss(_mm_sub_ss(clipp, w), offset);

    const __m128 d = _mm_add_ss(_mm_set_ss(121.2740575f), clipp);
    const __m128 c = _mm_mul_ss(_mm_set_ss(1.49012907f), z);
    const __m128 a = _mm_sub_ss(_mm_set_ss(4.84252568f), z);
    const __m128 b = _mm_div_ss(_mm_set_ss(27.7280233f), a);

    const __m128 e = _mm_add_ss(b, d);
    const __m128 f = _mm_sub_ss(e, c);

    const __m128i v = _mm_cvtps_epi32(_mm_mul_ss(_mm_set_ss((float)(1 << 23)), f));

    return _mm_cvtss_f32(_mm_castsi128_ps(v));

    #else
    const __m128 p      = _mm_set_ss(x);
    const __m128 lt126  = _mm_cmplt_ps (p, _mm_set_ss(-126.f));
    const __m128 clipp  = _mm_or_ps(_mm_andnot_ps(lt126, p), _mm_and_ps(lt126, _mm_set_ss(-126.f)));
    const __m128 clipp2 = _mm_add_ps(clipp, _mm_set_ss(126.94269504f));
    const __m128i v     = _mm_cvtps_epi32(_mm_mul_ps(_mm_set_ss((float)(1 << 23)), clipp2));

    return _mm_cvtss_f32(_mm_castsi128_ps(v));
    #endif
}



/*-------------------------------------
    atan2, accurate to within 0.01 radians.
-------------------------------------*/
#if 1
inline LS_INLINE float atan2(float y, float x) noexcept
{
    __m128 r, angle, theta;
    __m128 yf = _mm_set_ss(y);
    __m128 xf = _mm_set_ss(x);

    const __m128 absMask  = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
    const __m128 signMask = _mm_and_ps(_mm_cmplt_ss(yf, _mm_setzero_ps()), _mm_castsi128_ps(_mm_set1_epi32(0x80000000)));

    {
        const __m128 theta1      = _mm_set_ss(LS_PI_OVER_4);
        const __m128 theta2      = _mm_set_ss(3.f * LS_PI_OVER_4);
        const __m128 absY        = _mm_and_ps(yf, absMask);// + scalar_t{1e-10};
        const __m128 xy          = _mm_add_ss(xf, absY);
        const __m128 xGtY        = _mm_cmpge_ss(xf, _mm_setzero_ps());
        const __m128 numerator   = _mm_or_ps(_mm_and_ps(xGtY, _mm_sub_ss(xf, absY)), _mm_andnot_ps(xGtY, xy));
        const __m128 denominator = _mm_or_ps(_mm_and_ps(xGtY, xy), _mm_andnot_ps(xGtY, _mm_sub_ss(absY, xf)));

        r = _mm_div_ss(numerator, denominator);
        theta = _mm_or_ps(_mm_and_ps(xGtY, theta1), _mm_andnot_ps(xGtY, theta2));
    }

    {
        const __m128 pi5Over16 = _mm_set_ss(5.f * LS_PI / 16.f);
        const __m128 piOver16  = _mm_set_ss(LS_PI / 16.f);
        const __m128 r2        = _mm_mul_ss(r, r);
        const __m128 rPi16     = _mm_mul_ss(piOver16, r);
        const __m128 r5Pi16    = _mm_mul_ss(pi5Over16, r);

        // is it necessary to clamp values between [-1,1] ???
        angle = _mm_add_ss(_mm_sub_ss(_mm_mul_ss(r2, rPi16), r5Pi16), theta);
    }

    // negate if in quad III or IV
    return _mm_cvtss_f32(_mm_or_ps(signMask, angle));
}
#endif



/*-------------------------------------
    pow
-------------------------------------*/
inline LS_INLINE float pow(float x, float y) noexcept
{
    /*
    __m128 expx = _mm_set_ss(x);
    __m128i b = _mm_castps_si128(expx);

    const __m128i log2 = _mm_sub_epi32(_mm_and_si128(_mm_srai_epi32(b, 23), _mm_set1_epi32(255)), _mm_set1_epi32(128));

    b = _mm_and_si128(b, _mm_set1_epi32(~(255 << 23)));
    b = _mm_add_epi32(b, _mm_set1_epi32(127 << 23));

    expx = _mm_castsi128_ps(b);

    __m128 l2 = _mm_add_ss(_mm_mul_ss(_mm_set_ss(-0.3333333333f), expx), _mm_set_ss(2.f));
    l2 = _mm_sub_ss(_mm_mul_ss(l2, expx), _mm_set_ss(0.6666666666f));
    l2 = _mm_add_ss(l2, _mm_cvtepi32_ps(log2));

    __m128 ln = _mm_mul_ss(l2, _mm_set_ss(0.693147181f)); // ln( 2 )

    __m128 expy = _mm_mul_ps(ln, _mm_set_ss(y));
    __m128 s = _mm_add_ss(_mm_set_ss(1.f), _mm_mul_ss(expy, _mm_set_ss(1.f/16384.f)));

    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);

    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);
    s = _mm_mul_ss(s, s);

    return _mm_cvtss_f32(s);
    */
    return exp2(log2(x) * y);
}



/*-------------------------------------
    FMA
-------------------------------------*/
inline LS_INLINE float fmadd(float x, float m, float a) noexcept
{
    #ifdef LS_X86_FMA
        return _mm_cvtss_f32(_mm_fmadd_ps(_mm_set_ss(x), _mm_set_ss(m), _mm_set_ss(a)));
    #else
        return _mm_cvtss_f32(_mm_add_ps(_mm_mul_ps(_mm_set_ss(x), _mm_set_ss(m)), _mm_set_ss(a)));
    #endif
}



/*-------------------------------------
    FMA
-------------------------------------*/
inline LS_INLINE float fmsub(float x, float m, float a) noexcept
{
    #ifdef LS_X86_FMA
        return _mm_cvtss_f32(_mm_fmsub_ps(_mm_set_ss(x), _mm_set_ss(m), _mm_set_ss(a)));
    #else
        return _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(_mm_set_ss(x), _mm_set_ss(m)), _mm_set_ss(a)));
    #endif
}



} // end math namespace
} // end ls namespace

#endif /* LS_MATH_SCALARF_UTILS_IMPL_H */
