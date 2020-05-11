
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
/*-------------------------------------
    3x3 Determinant
-------------------------------------*/
inline LS_INLINE float determinant(const mat3_t<float>& m3x3) noexcept
{
    const float* const m = reinterpret_cast<const float*>(&m3x3);

    const float32x4_t col0{0.f, m[4], m[5], m[3]};
    const float32x4_t col1{0.f, m[8], m[6], m[7]};
    const float32x4_t col2{0.f, m[5], m[3], m[4]};
    const float32x4_t col3{0.f, m[7], m[8], m[6]};
    const float32x4_t col4{0.f, m[0], m[1], m[2]};

    const float32x4_t sub0 = vmlaq_f32(vnegq_f32(vmulq_f32(col3, col2)), col1, col0);
    const float32x4_t mul2 = vmulq_f32(sub0, col4);

    // horizontal add: swap the words of each vector, add, then swap each
    // half of the vectors and perform a final add.
    const float32x2_t swap = vadd_f32(vget_high_f32(mul2), vget_low_f32(mul2));
    const float32x2_t sum = vpadd_f32(swap, swap);

    return vget_lane_f32(sum, 0);
}

/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4x4 Outer Product
-------------------------------------*/
inline LS_INLINE mat4_t<float> outer(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    return mat4_t<float>{
        vmulq_n_f32(v2.simd, v1[0]),
        vmulq_n_f32(v2.simd, v1[1]),
        vmulq_n_f32(v2.simd, v1[2]),
        vmulq_n_f32(v2.simd, v1[3])
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
