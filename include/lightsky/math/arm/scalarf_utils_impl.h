
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
inline LS_INLINE float floor(float n) noexcept
{
    const float32x4_t f = vdupq_n_f32(n);
    const float32x4_t t = vcvtq_f32_s32(vcvtq_s32_f32(f)); // truncate fraction bits
    const uint32x4_t  i = vcltq_f32(f, t);
    const float32x4_t r = vsubq_f32(t, vcvtq_f32_u32(vandq_u32(i, vdupq_n_u32(1u))));

    return vget_lane_f32(vget_low_f32(r), 0);
}



/*-------------------------------------
 fmod
-------------------------------------*/
inline LS_INLINE float fmod(const float n1, const float n2) noexcept
{
    const float32x4_t  num   = vdupq_n_f32(n1);
    const float32x4_t  denom = vdupq_n_f32(n2);
    const float32x4_t  c     = vmulq_f32(num, vrecpeq_f32(denom));
    const int32x4_t    i     = vcvtq_s32_f32(c);
    const float32x4_t  t     = vcvtq_f32_s32(i); // truncate fraction
    const float32x4_t  base  = vmulq_f32(t, denom);

    const float32x4_t ret = vsubq_f32(num, base);
    return vget_lane_f32(vget_low_f32(ret), 0);
}



/*-------------------------------------
 fmod_1
-------------------------------------*/
inline LS_INLINE float fmod_1(const float n) noexcept
{
    const float32x4_t  num   = vdupq_n_f32(n);
    const int32x4_t    i     = vcvtq_s32_f32(num);
    const float32x4_t  t     = vcvtq_f32_s32(i); // truncate fraction

    const float32x4_t ret = vsubq_f32(num, t);
    return vget_lane_f32(vget_low_f32(ret), 0);
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
inline LS_INLINE float fast_inv_sqrt(float x) noexcept
{
    const float32x4_t ret = vrsqrteq_f32(vdupq_n_f32(x));
    return vget_lane_f32(vget_low_f32(ret), 0);
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
inline LS_INLINE float fast_sqrt(float x) noexcept
{
    const float32x4_t ret{vrecpeq_f32(vrsqrteq_f32(vdupq_n_f32(x)))};
    return vget_lane_f32(vget_low_f32(ret), 0);
}



/*-------------------------------------
    rcp
-------------------------------------*/
inline LS_INLINE float rcp(float x) noexcept
{
    const float32x4_t scalar = vdupq_n_f32(x);
    const float32x4_t recip = vrecpeq_f32(scalar);

    const float32x4_t ret = vmulq_f32(vrecpsq_f32(scalar, recip), recip);
    return vget_lane_f32(vget_low_f32(ret), 0);
}



/*-------------------------------------
    sum
-------------------------------------*/
inline LS_INLINE float sum(float num0, float num1, float num2, float num3) noexcept
{
    const float lanes[4] = {num0, num1, num2, num3};

    const float32x4_t a = vld1q_f32(lanes);
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);

    return vget_lane_f32(vget_low_f32(d), 0);
}



} // end math namespace
} // end ls namespace
