
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
inline LS_INLINE float length(const vec3_t<float>& v)
{
    const float lanes[4] = {v.v[0], v.v[1], v.v[2], 0.f};
    const float32x4_t s = vld1q_f32(lanes);
    const float32x4_t a = vmulq_f32(s, s);
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);
    const float32x2_t d = vrsqrte_f32(c);

    const float32x2_t recip0 = vrecpe_f32(d);
    const float32x2_t recip1 = vmul_f32(vrecps_f32(d, recip0), recip0);
    return vget_lane_f32(recip1, 0);
}



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Sum
-------------------------------------*/
inline LS_INLINE float sum(const vec4_t<float>& v)
{
    const float32x4_t a = v.simd;
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);
    return vget_lane_f32(c, 0);
}

/*-------------------------------------
    4D Reciprocal Sum
-------------------------------------*/
inline LS_INLINE float sum_inv(const vec4_t<float>& v)
{
    const float32x4_t a = v.simd;
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);

    const float32x2_t recip0 = vrecpe_f32(c);
    const float32x2_t recip1 = vmul_f32(vrecps_f32(c, recip0), recip0);

    return vget_lane_f32(recip1, 0);
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
inline LS_INLINE float dot(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    const float32x4_t a = vmulq_f32(v1.simd, v2.simd);
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);

    return vget_lane_f32(c, 0);
}

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
inline LS_INLINE float length(const vec4_t<float>& v)
{
    const float32x4_t s = vld1q_f32(&v);
    const float32x4_t a = vmulq_f32(s, s);
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);
    const float32x2_t d = vrsqrte_f32(c);

    const float32x2_t recip0 = vrecpe_f32(d);
    const float32x2_t recip1 = vmul_f32(vrecps_f32(d, recip0), recip0);
    return vget_lane_f32(recip1, 0);
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
inline LS_INLINE math::vec4_t<float> normalize(const vec4_t<float>& v)
{
    const float32x4_t s = v.simd;
    const float32x4_t a = vmulq_f32(s, s);
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);
    const float32x4_t d = vcombine_f32(c, c);

    // normalization
    return vec4_t<float>{vmulq_f32(s, vrsqrteq_f32(d))};
}

/*-------------------------------------
    4D Min
-------------------------------------*/
inline LS_INLINE vec4_t<float> min(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return math::vec4_t<float>{vminq_f32(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
inline LS_INLINE vec4_t<float> max(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return math::vec4_t<float>{vmaxq_f32(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D RCP
-------------------------------------*/
inline LS_INLINE vec4_t<float> rcp(const vec4_t<float>& v)
{
    const float32x4_t simd  = v.simd;
    const float32x4_t recip = vrecpeq_f32(simd);
    const float32x4_t ret   = vmulq_f32(vrecpsq_f32(simd, recip), recip);
    return vec4_t<float>{ret};
}

/*-------------------------------------
    4D Sign Bits
-------------------------------------*/
inline LS_INLINE int sign_mask(const vec4_t<float>& x) noexcept
{
    uint32_t vals[4];
    const uint32x4_t a = vreinterpretq_u32_f32(x.simd);
    vst1q_u32(vals, a);

    return ((a[3] >> 28) & 8) | ((a[2] >> 29) & 4) | ((a[1] >> 30) & 2) | ((a[0] >> 31) & 1);
}

/*-------------------------------------
    FMA
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmadd(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    #if defined(LS_ARCH_AARCH64)
    return return vec4_t<float>{vfmaq_f32(a, m, x)};
    #else
    return return vec4_t<float>{vaddq_f32(vmulq_f32(x, m), a)};
    #endif
}

/*-------------------------------------
    FMS
-------------------------------------*/
inline LS_INLINE vec4_t<float> fmadd(const vec4_t<float>& x, const vec4_t<float>& m, const vec4_t<float>& a) noexcept
{
    #if defined(LS_ARCH_AARCH64)
    return return vec4_t<float>{vfmsq_f32(a, m, x)};
    #else
    return return vec4_t<float>{vsubq_f32(vmulq_f32(x, m), a)};
    #endif
}



} // end math namespace
} // end ls namespace
