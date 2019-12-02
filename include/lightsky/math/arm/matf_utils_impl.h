
#include <arm_neon.h>

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    2x2 Matrices
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
    3x3 Matrices
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4x4 Outer Product
-------------------------------------*/
inline LS_INLINE mat4_t<float> outer(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    return mat4_t<float>{
        vmulq_f32(vdupq_n_f32(v1[0]), v2.simd),
        vmulq_f32(vdupq_n_f32(v1[1]), v2.simd),
        vmulq_f32(vdupq_n_f32(v1[2]), v2.simd),
        vmulq_f32(vdupq_n_f32(v1[3]), v2.simd)
    };
}

/*-------------------------------------
    4x4 Transpose
-------------------------------------*/
inline LS_INLINE mat4_t<float> transpose(const mat4_t<float>& m)
{
    // a|b|c|d
    // e|f|g|h
    // i|j|k|l
    // m|n|o|p

    // a|e|c|g
    // b|f|d|h
    // i|m|k|o
    // j|n|l|p
    /*
    const float32x4x2_t aecg_bfdh = vtrnq_f32(m.m[0].simd, m.m[1].simd);
    const float32x4x2_t imko_jnlp = vtrnq_f32(m.m[2].simd, m.m[3].simd);

    // a|e|i|m
    // b|f|j|n
    // c|g|k|o
    // d|h|l|p
    return mat4_t<float>{
        {vcombine_f32(vget_low_f32(aecg_bfdh.val[0]), vget_low_f32(imko_jnlp.val[0]))},
        {vcombine_f32(vget_low_f32(aecg_bfdh.val[1]), vget_low_f32(imko_jnlp.val[1]))},
        {vcombine_f32(vget_high_f32(aecg_bfdh.val[0]), vget_high_f32(imko_jnlp.val[0]))},
        {vcombine_f32(vget_high_f32(aecg_bfdh.val[1]), vget_high_f32(imko_jnlp.val[1]))}
    };
    */
    union
    {
        float32x4x4_t t;
        mat4_t<float> m;
    } ret{vld4q_f32(&m[0])};
    return ret.m;
}



} // end math namespace
} // end ls namespace
