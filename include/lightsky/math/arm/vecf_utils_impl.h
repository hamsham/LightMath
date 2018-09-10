
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
    const float32x4_t e = vrsqrteq_f32(d);

    const float32x4_t recip = vrecpeq_f32(e);
    const float32x4_t ret = vmulq_f32(vrecpsq_f32(e, recip), recip);

    return vget_lane_f32(vget_low_f32(ret), 0);
}



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Sum
-------------------------------------*/
inline float sum(const vec4_t<float>& v)
{
    const float32x4_t a = v.simd;
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);

    return vget_lane_f32(vget_low_f32(d), 0);
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
inline float dot(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    const float32x4_t a = vmulq_f32(v1.simd, v2.simd);
    const float32x4_t b = vaddq_f32(a, vrev64q_f32(a));
    const float32x4_t c = vcombine_f32(vget_high_f32(b), vget_low_f32(b));
    const float32x4_t d = vaddq_f32(b, c);

    return vget_lane_f32(vget_low_f32(d), 0);
}

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
    const float32x4_t e = vrsqrteq_f32(d);

    const float32x4_t recip = vrecpeq_f32(e);
    const float32x4_t ret = vmulq_f32(vrecpsq_f32(e, recip), recip);

    return vget_lane_f32(vget_low_f32(ret), 0);
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

/*-------------------------------------
    4D Min
-------------------------------------*/
inline vec4_t<float> min(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return math::vec4_t<float>{vminq_f32(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
inline vec4_t<float> max(const vec4_t<float>& v1, const vec4_t<float>& v2)
{
    return math::vec4_t<float>{vmaxq_f32(v1.simd, v2.simd)};
}

/*-------------------------------------
    4D RCP
-------------------------------------*/
inline vec4_t<float> rcp(const vec4_t<float>& v)
{
    const float32x4_t simd  = v.simd;
    const float32x4_t recip = vrecpeq_f32(simd);
    const float32x4_t ret   = vmulq_f32(vrecpsq_f32(simd, recip), recip);
    return vec4_t<float>{ret};
}



} // end math namespace
} // end ls namespace
