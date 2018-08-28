
#include <arm_neon.h>

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
template<> inline
float floor(float n) noexcept
{
    union SimdVec
    {
        float32x4_t simd;
        float f[4];
    };
    const float32x4_t f = vdupq_n_f32(n);
    const float32x4_t t = vcvtq_f32_s32(vcvtq_s32_f32(f)); // truncate fraction bits
    const uint32x4_t  i = vcltq_f32(f, t);
    const float32x4_t r = vsubq_f32(t, vcvtq_f32_u32(vandq_u32(i, vdupq_n_u32(1u))));
    return SimdVec{r}.f[0];
}



/*-------------------------------------
 fmod
-------------------------------------*/
template<> inline
float fmod(const float n1, const float n2) noexcept
{
    union SimdVec
    {
        float32x4_t simd;
        float f[4];
    };
    const float32x4_t  num   = vdupq_n_f32(n1);
    const float32x4_t  denom = vdupq_n_f32(n2);
    const float32x4_t  c     = vmulq_f32(num, vrecpeq_f32(denom));
    const int32x4_t    i     = vcvtq_s32_f32(c);
    const float32x4_t  t     = vcvtq_f32_s32(i); // truncate fraction
    const float32x4_t  base  = vmulq_f32(t, denom);
    return SimdVec{vsubq_f32(num, base)}.f[0];
}



/*-------------------------------------
 fmod_1
-------------------------------------*/
template<> inline
float fmod_1(const float n) noexcept
{
    union SimdVec
    {
        float32x4_t simd;
        float f[4];
    };
    const float32x4_t  num   = vdupq_n_f32(n);
    const int32x4_t    i     = vcvtq_s32_f32(num);
    const float32x4_t  t     = vcvtq_f32_s32(i); // truncate fraction
    return SimdVec{vsubq_f32(num, t)}.f[0];
}



/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
template<> inline
float fast_inv_sqrt<float>(float x) noexcept
{
    union SimdVec
    {
        float32x4_t simd;
        float f[4];
    } ret{vrsqrteq_f32(vdupq_n_f32(x))};
    return ret.f[0];
}



} // end math namespace
} // end ls namespace
