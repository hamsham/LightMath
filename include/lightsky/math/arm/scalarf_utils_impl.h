
#include <arm_neon.h>

#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    Function definitions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    floor
-------------------------------------*/
/*
inline LS_INLINE float floor(float n) noexcept
{
    const float32x2_t f = vdup_n_f32(n);
    const float32x2_t t = vcvt_f32_s32(vcvt_s32_f32(f)); // truncate fraction bits
    const uint32x2_t  i = vclt_f32(f, t);
    const float32x2_t r = vsub_f32(t, vcvt_f32_u32(vand_u32(i, vdup_n_u32(1u))));

    return vget_lane_f32(r, 0);
}
*/



/*-------------------------------------
 fmod
-------------------------------------*/
/*
inline LS_INLINE float fmod(const float n1, const float n2) noexcept
{
    const float32x2_t  num   = vdup_n_f32(n1);
    const float32x2_t  denom = vdup_n_f32(n2);
    const float32x2_t  c     = vmul_f32(num, vrecpe_f32(denom));
    const int32x2_t    i     = vcvt_s32_f32(c);
    const float32x2_t  t     = vcvt_f32_s32(i); // truncate fraction
    const float32x2_t  base  = vmul_f32(t, denom);

    const float32x2_t ret = vsub_f32(num, base);
    return vget_lane_f32(ret, 0);
}
*/



/*-------------------------------------
 fmod_1
-------------------------------------*/
inline LS_INLINE float fmod_1(const float n) noexcept
{
    const float32x2_t  num = vdup_n_f32(n);
    const int32x2_t    i   = vcvt_s32_f32(num);
    const float32x2_t  t   = vcvt_f32_s32(i); // truncate fraction
    const float32x2_t ret  = vsub_f32(num, t);

    return vget_lane_f32(ret, 0);
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
inline LS_INLINE float inversesqrt(float x) noexcept
{
    const float32x2_t scalar = vdup_n_f32(x);

    float32x2_t rsqr = vrsqrte_f32(scalar);
    rsqr = vmul_f32(vrsqrts_f32(vmul_f32(scalar, rsqr), rsqr), rsqr);
    rsqr = vmul_f32(vrsqrts_f32(vmul_f32(scalar, rsqr), rsqr), rsqr);

    return vget_lane_f32(rsqr, 0);
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
inline LS_INLINE float fast_sqrt(float x) noexcept
{
    const float32x2_t scalar = vdup_n_f32(x);

    float32x2_t rsqr = vrsqrte_f32(scalar);
    rsqr = vmul_f32(vrsqrts_f32(vmul_f32(scalar, rsqr), rsqr), rsqr);
    rsqr = vmul_f32(vrsqrts_f32(vmul_f32(scalar, rsqr), rsqr), rsqr);

    float32x2_t inv = vrecpe_f32(rsqr);
    inv = vmul_f32(vrecps_f32(rsqr, inv), inv);
    inv = vmul_f32(vrecps_f32(rsqr, inv), inv);

    return vget_lane_f32(inv, 0);
}



/*-------------------------------------
    rcp
-------------------------------------*/
inline LS_INLINE float rcp(float x) noexcept
{
    const float32x2_t scalar = vdup_n_f32(x);

    float32x2_t recip = vrecpe_f32(scalar);
    recip = vmul_f32(vrecps_f32(scalar, recip), recip);
    recip = vmul_f32(vrecps_f32(scalar, recip), recip);

    return vget_lane_f32(recip, 0);
}



/*-------------------------------------
    sum
-------------------------------------*/
/*
inline LS_INLINE float sum(float num0, float num1, float num2, float num3) noexcept
{
    const float lanes[4] = {num0, num1, num2, num3};

    const float32x4_t a = vld1q_f32(lanes);
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);

    return vget_lane_f32(vget_low_f32(d), 0);
}
*/



/*-------------------------------------
    FMA
-------------------------------------*/
inline LS_INLINE float fmadd(float x, float m, float a) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        const float32x2_t result = vfma_f32(vdup_n_f32(a), vdup_n_f32(m), vdup_n_f32(x));
    #else
        const float32x2_t result = vmla_f32(vdup_n_f32(a), vdup_n_f32(m), vdup_n_f32(x));
    #endif

    return vget_lane_f32(result, 0);
}



/*-------------------------------------
    FMS
-------------------------------------*/
inline LS_INLINE float fmsub(float x, float m, float a) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        const float32x2_t result = vfms_f32(vdup_n_f32(a), vdup_n_f32(m), vdup_n_f32(x));
    #else
        const float32x2_t result = vmla_f32(vneg_f32(vdup_n_f32(a)), vdup_n_f32(m), vdup_n_f32(x));
    #endif

    return vget_lane_f32(result, 0);
}



} // end math namespace
} // end ls namespace
