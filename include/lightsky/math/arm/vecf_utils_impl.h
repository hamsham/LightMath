
#include <arm_neon.h>

#include "lightsky/setup/Api.h" // LS_INLINE

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
/*-------------------------------------
    3D Magnitude
-------------------------------------*/
/*
inline LS_INLINE float length(const vec3_t<float>& v) noexcept
{
    const float lanes[4] = {v.v[0], v.v[1], v.v[2], 0.f};
    const float32x4_t s = vld1q_f32(lanes);

    // sum, squared
    const float32x4_t a = vmulq_f32(s, s);
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);

    float32x2_t d = vrsqrte_f32(c);
    d = vmul_f32(vrsqrts_f32(vmul_f32(c, d), d), d);
    //d = vmul_f32(vrsqrts_f32(vmul_f32(c, d), d), d);

    float32x2_t e = vrecpe_f32(d);
    e = vmul_f32(vrecps_f32(d, e), e);
    e = vmul_f32(vrecps_f32(d, e), e);
    return vget_lane_f32(e, 0);
}
*/


/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Sum
-------------------------------------*/
inline LS_INLINE float sum(const vec4_t<float>& v) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        return vaddvq_f32(v.simd);

    #else
        const float32x2_t a = vadd_f32(vget_high_f32(v.simd), vget_low_f32(v.simd));
        const float32x2_t b = vpadd_f32(a, a);
        return vget_lane_f32(b, 0);

    #endif
}

/*-------------------------------------
    4D Reciprocal Sum
-------------------------------------*/
inline LS_INLINE float sum_inv(const vec4_t<float>& v) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        const float32x2_t b = vdup_n_f32(vaddvq_f32(v.simd));

    #else
        const float32x2_t a = vadd_f32(vget_high_f32(v.simd), vget_low_f32(v.simd));
        const float32x2_t b = vpadd_f32(a, a);

    #endif

    return vget_lane_f32(vrecpe_f32(b), 0);
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
inline LS_INLINE float dot(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    const float32x4_t a = vmulq_f32(v1.simd, v2.simd);

    #if defined(LS_ARCH_AARCH64)
        return vaddvq_f32(a);

    #else
        const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
        const float32x2_t c = vpadd_f32(b, b);
        return vget_lane_f32(c, 0);

    #endif
}

/*-------------------------------------
    4D Cross
-------------------------------------*/
inline LS_INLINE vec4_t<float> cross(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    const float32x2x2_t v1Split = vzip_f32(vget_low_f32(v1.simd), vrev64_f32(vget_high_f32(v1.simd)));
    const float32x4_t yzxA = vcombine_f32(v1Split.val[1], v1Split.val[0]);

    const float32x2x2_t v2Split = vzip_f32(vget_low_f32(v2.simd), vrev64_f32(vget_high_f32(v2.simd)));
    const float32x4_t yzxB = vcombine_f32(v2Split.val[1], v2Split.val[0]);

    const float32x4_t mulSub = vmlsq_f32(vmulq_f32(v1.simd, yzxB), v2.simd, yzxA);

    const float32x2x2_t split = vzip_f32(vget_low_f32(mulSub), vrev64_f32(vget_high_f32(mulSub)));
    return vec4_t<float>{vcombine_f32(split.val[1], split.val[0])};
}

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
inline LS_INLINE float length(const vec4_t<float>& v) noexcept
{
    // sum, squared
    const float32x4_t a = vmulq_f32(v.simd, v.simd);

    #if defined(LS_ARCH_AARCH64)
        float32x2_t c = vdup_n_f32(vaddvq_f32(a));
    #else
        const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
        const float32x2_t c = vpadd_f32(b, b);
    #endif

    float32x2_t d = vrsqrte_f32(c);
    d = vmul_f32(vrsqrts_f32(vmul_f32(c, d), d), d);
    //d = vmul_f32(vrsqrts_f32(vmul_f32(c, d), d), d);

    float32x2_t e = vrecpe_f32(d);
    e = vmul_f32(vrecps_f32(d, e), e);
    e = vmul_f32(vrecps_f32(d, e), e);
    return vget_lane_f32(e, 0);
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
inline LS_INLINE vec4_t<float> normalize(const vec4_t<float>& v) noexcept
{
    const float32x4_t a = vmulq_f32(v.simd, v.simd);

    #if defined(LS_ARCH_AARCH64)
        float32x4_t d = vdupq_n_f32(vaddvq_f32(a));
    #else
        const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
        const float32x2_t c = vpadd_f32(b, b);
        float32x4_t d = vcombine_f32(c, c);

    #endif

    // normalization
    float32x4_t e = vrsqrteq_f32(d);
    e = vmulq_f32(vrsqrtsq_f32(vmulq_f32(d, e), e), e);
    //e = vmulq_f32(vrsqrtsq_f32(vmulq_f32(d, e), e), e);
    return vmulq_f32(v.simd, e);
}

/*-------------------------------------
    4D Mix
-------------------------------------*/
inline LS_INLINE vec4_t<float> mix(const vec4_t<float>& v1, const vec4_t<float>& v2, float percent) noexcept
{
    const float32x4_t v = vsubq_f32(v2.simd, v1.simd);
    return vec4_t<float>{vmlaq_n_f32(v1.simd, v, percent)};
}

/*-------------------------------------
    4D Min
-------------------------------------*/
inline LS_INLINE vec4_t<float> min(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    return vec4_t<float>{vminq_f32(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
inline LS_INLINE vec4_t<float> max(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    return vec4_t<float>{vmaxq_f32(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Clamp
-------------------------------------*/
inline LS_INLINE vec4_t<float> clamp(const vec4_t<float>& v, const vec4_t<float>& minVals, const vec4_t<float>& maxVals) noexcept
{
    return vec4_t<float>{vminq_f32(maxVals.simd, vmaxq_f32(v.simd, minVals.simd))};
}

/*-------------------------------------
    4D Step
-------------------------------------*/
inline LS_INLINE vec4_t<float> step(const vec4_t<float>& edge, const vec4_t<float>& v) noexcept
{
    const uint32x4_t cmpVal = vcltq_f32(v.simd, edge.simd);
    return vec4_t<float>{vbslq_f32(cmpVal, vdupq_n_f32(0.f), vdupq_n_f32(1.f))};
}

/*-------------------------------------
    4D RCP
-------------------------------------*/
inline LS_INLINE vec4_t<float> rcp(const vec4_t<float>& v) noexcept
{
    const float32x4_t recip = vrecpeq_f32(v.simd);
    const float32x4_t ret   = vmulq_f32(vrecpsq_f32(v.simd, recip), recip);
    return vec4_t<float>{ret};
}

/*-------------------------------------
    4D Sign Bits
-------------------------------------*/
inline LS_INLINE int sign_mask(const vec4_t<float>& x) noexcept
{
    /*
    uint32_t vals[4];
    const uint32x4_t a = vreinterpretq_u32_f32(x.simd);
    vst1q_u32(vals, a);

    return ((a[3] >> 28) & 8) | ((a[2] >> 29) & 4) | ((a[1] >> 30) & 2) | ((a[0] >> 31) & 1);
    */

    constexpr int32_t shiftLiterals[4] = {-28, -29, -30, -31};
    constexpr int32_t andLiterals[4] = {1, 2, 4, 8};

    int32x4_t cmp = vreinterpretq_s32_u32(vcltq_f32(x.simd, vdupq_n_f32(0.f)));
    int32x4_t shifts = vqshlq_s32(cmp, vld1q_s32(shiftLiterals));
    int32x4_t masks = vandq_s32(shifts, vld1q_s32(andLiterals));

    int32x2_t or2 = vorr_s32(vget_high_s32(masks), vget_low_s32(masks));
    return vget_lane_s32(or2, 0) | vget_lane_s32(or2, 1);
}

/*-------------------------------------
    4D floor
-------------------------------------*/
#if defined(LS_ARCH_AARCH64)
inline LS_INLINE vec4_t<float> floor(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{vrndmq_f32(v.simd)};
}
#endif

/*-------------------------------------
    4D ceil
-------------------------------------*/
#if defined(LS_ARCH_AARCH64)
inline LS_INLINE vec4_t<float> ceil(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{vrndpq_f32(v.simd)};
}
#endif

/*-------------------------------------
    4D round
-------------------------------------*/
#if defined(LS_ARCH_AARCH64)
inline LS_INLINE vec4_t<float> round(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{vrndiq_f32(v.simd)};
}
#endif

/*-------------------------------------
    4D abs
-------------------------------------*/
inline LS_INLINE vec4_t<float> abs(const vec4_t<float>& v) noexcept
{
    return vec4_t<float>{vabsq_f32(v.simd)};
}

/*-------------------------------------
    FMA
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmadd(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        return vec4_t<float>{vfmaq_f32(a.simd, m.simd, x.simd)};
    #else
        return vec4_t<float>{vmlaq_f32(a.simd, m.simd, x.simd)};
    #endif
}

/*-------------------------------------
    FMS
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmsub(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        return vec4_t<float>{vfmsq_f32(a.simd, m.simd, x.simd)};
    #else
        return vec4_t<float>{vmlaq_f32(vnegq_f32(a.simd), m.simd, x.simd)};
    #endif
}



} // end math namespace
} // end ls namespace
