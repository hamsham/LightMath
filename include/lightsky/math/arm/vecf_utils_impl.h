
#include <arm_neon.h>

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
template <>
inline
float length(const vec3_t<float>& v)
{
    const float lanes[4] = {v.v[0], v.v[1], v.v[2], 0.f};
    const float32x4_t s = vld1q_f32(lanes);
    const float32x4_t a = vmulq_f32(s, s);
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);
    const float32x4_t e = vrecpeq_f32(vrsqrteq_f32(d));

    float ret;
    vst1q_lane_f32(&ret, e, 0);
    return ret;
}



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Magnitude
-------------------------------------*/
template <>
inline
float length(const vec4_t<float>& v)
{
    const float32x4_t s = v.simd;
    const float32x4_t a = vmulq_f32(s, s);
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);
    const float32x4_t e = vrecpeq_f32(vrsqrteq_f32(d));

    float ret;
    vst1q_lane_f32(&ret, e, 0);
    return ret;
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
template <>
inline
math::vec4_t<float> normalize(const vec4_t<float>& v)
{
    const float32x4_t s = v.simd;
    const float32x4_t a = vmulq_f32(s, s);
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);

    // normalization
    return vec4_t<float>{vmulq_f32(s, vrsqrteq_f32(d))};
}



} // end math namespace
} // end ls namespace
