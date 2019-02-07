
#include <arm_neon.h>

#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    Quaternion Utilities
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Dot
-------------------------------------*/
inline LS_INLINE float dot(const quat_t<float>& q1, const quat_t<float>& q2)
{
    const float32x4_t a = vmulq_f32(vld1q_f32(q1.q), vld1q_f32(q2.q));
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);

    return vget_lane_f32(c, 0);
}

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
inline LS_INLINE float length(const quat_t<float>& q)
{
    const float32x4_t s = vld1q_f32(q.q);
    const float32x4_t a = vmulq_f32(s, s);
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);
    const float32x2_t d = vrsqrte_f32(c);

    const float32x2_t recip0 = vrecpe_f32(d);
    const float32x2_t recip1 = vmul_f32(vrecps_f32(d, recip0), recip0);
    return vget_lane_f32(recip1, 0);
}

/*-------------------------------------
    normalize
-------------------------------------*/
inline LS_INLINE quat_t<float> normalize(const quat_t<float>& q)
{
    const float32x4_t s = vld1q_f32(q.q);
    const float32x4_t a = vmulq_f32(s, s);
    const float32x2_t b = vadd_f32(vget_high_f32(a), vget_low_f32(a));
    const float32x2_t c = vpadd_f32(b, b);
    const float32x4_t d = vcombine_f32(c, c);

    // normalization
    quat_t<float> ret;
    vst1q_f32(ret.q, vmulq_f32(s, vrsqrteq_f32(d)));
    return ret;
}



} // end math namespace
} // end ls namespace
