
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
    #if defined(LS_ARCH_AARCH64)
        return vaddvq_f32(mul2);
    #else
        const float32x2_t swap = vadd_f32(vget_high_f32(mul2), vget_low_f32(mul2));
        const float32x2_t sum = vpadd_f32(swap, swap);

        return vget_lane_f32(sum, 0);
    #endif
}



/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4x4 Outer Product
-------------------------------------*/
inline LS_INLINE mat4_t<float> outer(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        return mat4_t<float>{
            vec4_t<float>{vmulq_laneq_f32(v2.simd, v1.simd, 0)},
            vec4_t<float>{vmulq_laneq_f32(v2.simd, v1.simd, 1)},
            vec4_t<float>{vmulq_laneq_f32(v2.simd, v1.simd, 2)},
            vec4_t<float>{vmulq_laneq_f32(v2.simd, v1.simd, 3)}
        };

    #else
        return mat4_t<float>{
            vec4_t<float>{vmulq_f32(v2.simd, vdupq_n_f32(vgetq_lane_f32(v1.simd, 0)))},
            vec4_t<float>{vmulq_f32(v2.simd, vdupq_n_f32(vgetq_lane_f32(v1.simd, 1)))},
            vec4_t<float>{vmulq_f32(v2.simd, vdupq_n_f32(vgetq_lane_f32(v1.simd, 2)))},
            vec4_t<float>{vmulq_f32(v2.simd, vdupq_n_f32(vgetq_lane_f32(v1.simd, 3)))}
        };

    #endif
}



/*-------------------------------------
    4x4 Component-wise multiplication
-------------------------------------*/
inline LS_INLINE mat4_t<float> mat_comp_mul(const mat4_t<float>& m1, const mat4_t<float>& m2) noexcept
{
    return mat4_t<float>{
        vec4_t<float>{vmulq_f32(m1.m[0].simd, m2.m[0].simd)},
        vec4_t<float>{vmulq_f32(m1.m[1].simd, m2.m[1].simd)},
        vec4_t<float>{vmulq_f32(m1.m[2].simd, m2.m[2].simd)},
        vec4_t<float>{vmulq_f32(m1.m[3].simd, m2.m[3].simd)}
    };
}



/*-------------------------------------
    Row-based multiplication
-------------------------------------*/
inline LS_INLINE mat4_t<float> mat_row_mul(const mat4_t<float>& m, const vec4_t<float>& v) noexcept {
    const float32x4_t row0 = vdupq_n_f32(vget_lane_f32(vget_low_f32(v.simd),  0));
    const float32x4_t row1 = vdupq_n_f32(vget_lane_f32(vget_low_f32(v.simd),  1));
    const float32x4_t row2 = vdupq_n_f32(vget_lane_f32(vget_high_f32(v.simd), 0));
    const float32x4_t row3 = vdupq_n_f32(vget_lane_f32(vget_high_f32(v.simd), 1));

    return mat4_t<float>{
        vec4_t<float>{vmulq_f32(m.m[0].simd, row0)},
        vec4_t<float>{vmulq_f32(m.m[1].simd, row1)},
        vec4_t<float>{vmulq_f32(m.m[2].simd, row2)},
        vec4_t<float>{vmulq_f32(m.m[3].simd, row3)},
    };
}



/*-------------------------------------
    4x4 Transpose
-------------------------------------*/
inline LS_INLINE mat4_t<float> transpose(const mat4_t<float>& m)
{
    const float32x4x4_t t {vld4q_f32(&m[0])};
    return mat4_t<float>{
        vec4_t<float>{t.val[0]},
        vec4_t<float>{t.val[1]},
        vec4_t<float>{t.val[2]},
        vec4_t<float>{t.val[3]}
    };
}



} // end math namespace
} // end ls namespace
