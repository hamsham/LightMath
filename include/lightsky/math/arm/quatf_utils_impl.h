
#include <arm_neon.h>

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    Quaternion Utilities
-----------------------------------------------------------------------------*/
/*-------------------------------------
    normalize
-------------------------------------*/
template <>
inline
math::quat_t<float> normalize(const quat_t<float>& q)
{
    const float32x4_t s = vld1q_f32(q.q);
    const float32x4_t a = vmulq_f32(s, s);
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);

    // normalization
    quat_t<float> ret;
    vst1q_f32(ret.q, vmulq_f32(s, vrsqrteq_f32(d)));
    return ret;
}



} // end math namespace
} // end ls namespace
