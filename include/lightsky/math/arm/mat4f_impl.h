
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{
    alignas(alignof(float32x4x4_t)) mat4_t<float> ret;

    #if defined(LS_ARCH_AARCH64)
        ret[0].simd = vmulq_laneq_f32(             this->m[0].simd, n[0].simd, 0);
        ret[0].simd = vmlaq_laneq_f32(ret[0].simd, this->m[1].simd, n[0].simd, 1);
        ret[0].simd = vmlaq_laneq_f32(ret[0].simd, this->m[2].simd, n[0].simd, 2);
        ret[0].simd = vmlaq_laneq_f32(ret[0].simd, this->m[3].simd, n[0].simd, 3);

        ret[1].simd = vmulq_laneq_f32(             this->m[0].simd, n[1].simd, 0);
        ret[1].simd = vmlaq_laneq_f32(ret[1].simd, this->m[1].simd, n[1].simd, 1);
        ret[1].simd = vmlaq_laneq_f32(ret[1].simd, this->m[2].simd, n[1].simd, 2);
        ret[1].simd = vmlaq_laneq_f32(ret[1].simd, this->m[3].simd, n[1].simd, 3);

        ret[2].simd = vmulq_laneq_f32(             this->m[0].simd, n[2].simd, 0);
        ret[2].simd = vmlaq_laneq_f32(ret[2].simd, this->m[1].simd, n[2].simd, 1);
        ret[2].simd = vmlaq_laneq_f32(ret[2].simd, this->m[2].simd, n[2].simd, 2);
        ret[2].simd = vmlaq_laneq_f32(ret[2].simd, this->m[3].simd, n[2].simd, 3);

        ret[3].simd = vmulq_laneq_f32(             this->m[0].simd, n[3].simd, 0);
        ret[3].simd = vmlaq_laneq_f32(ret[3].simd, this->m[1].simd, n[3].simd, 1);
        ret[3].simd = vmlaq_laneq_f32(ret[3].simd, this->m[2].simd, n[3].simd, 2);
        ret[3].simd = vmlaq_laneq_f32(ret[3].simd, this->m[3].simd, n[3].simd, 3);

    #else
        ret[0].simd = vmulq_lane_f32(             this->m[0].simd, vget_low_f32( n[0].simd), 0);
        ret[0].simd = vmlaq_lane_f32(ret[0].simd, this->m[1].simd, vget_low_f32( n[0].simd), 1);
        ret[0].simd = vmlaq_lane_f32(ret[0].simd, this->m[2].simd, vget_high_f32(n[0].simd), 0);
        ret[0].simd = vmlaq_lane_f32(ret[0].simd, this->m[3].simd, vget_high_f32(n[0].simd), 1);

        ret[1].simd = vmulq_lane_f32(             this->m[0].simd, vget_low_f32( n[1].simd), 0);
        ret[1].simd = vmlaq_lane_f32(ret[1].simd, this->m[1].simd, vget_low_f32( n[1].simd), 1);
        ret[1].simd = vmlaq_lane_f32(ret[1].simd, this->m[2].simd, vget_high_f32(n[1].simd), 0);
        ret[1].simd = vmlaq_lane_f32(ret[1].simd, this->m[3].simd, vget_high_f32(n[1].simd), 1);

        ret[2].simd = vmulq_lane_f32(             this->m[0].simd, vget_low_f32( n[2].simd), 0);
        ret[2].simd = vmlaq_lane_f32(ret[2].simd, this->m[1].simd, vget_low_f32( n[2].simd), 1);
        ret[2].simd = vmlaq_lane_f32(ret[2].simd, this->m[2].simd, vget_high_f32(n[2].simd), 0);
        ret[2].simd = vmlaq_lane_f32(ret[2].simd, this->m[3].simd, vget_high_f32(n[2].simd), 1);

        ret[3].simd = vmulq_lane_f32(             this->m[0].simd, vget_low_f32( n[3].simd), 0);
        ret[3].simd = vmlaq_lane_f32(ret[3].simd, this->m[1].simd, vget_low_f32( n[3].simd), 1);
        ret[3].simd = vmlaq_lane_f32(ret[3].simd, this->m[2].simd, vget_high_f32(n[3].simd), 0);
        ret[3].simd = vmlaq_lane_f32(ret[3].simd, this->m[3].simd, vget_high_f32(n[3].simd), 1);

    #endif

    return ret;
}



/*
template <>
inline LS_INLINE mat4_t<float>& mat4_t<float>::operator*=(const mat4_t<float>& n)
{
    // Transpose the internal matrix, then multiply it by n.
    // a|b|c|d
    // e|f|g|h
    // i|j|k|l
    // m|n|o|p

    // a|e|c|g
    // b|f|d|h
    // i|m|k|o
    // j|n|l|p
    const float32x4x2_t aecg_bfdh = vtrnq_f32(this->m[0].simd, this->m[1].simd);
    const float32x4x2_t imko_jnlp = vtrnq_f32(this->m[2].simd, this->m[3].simd);

    // a|e|i|m
    // b|f|j|n
    // c|g|k|o
    // d|h|l|p
    const float32x4_t t[4] = {
        {vcombine_f32(vget_low_f32(aecg_bfdh.val[0]),  vget_low_f32(imko_jnlp.val[0]))},
        {vcombine_f32(vget_low_f32(aecg_bfdh.val[1]),  vget_low_f32(imko_jnlp.val[1]))},
        {vcombine_f32(vget_high_f32(aecg_bfdh.val[0]), vget_high_f32(imko_jnlp.val[0]))},
        {vcombine_f32(vget_high_f32(aecg_bfdh.val[1]), vget_high_f32(imko_jnlp.val[1]))}
    };
        
    for (unsigned i = 0; i < 4; ++i)
    {
        const float32x4_t simd = n.m[i].simd;
        
        const float32x4_t aq = vmulq_f32(t[0], simd);
        const float32x4_t bq = vmulq_f32(t[1], simd);
        const float32x4_t cq = vmulq_f32(t[2], simd);
        const float32x4_t dq = vmulq_f32(t[3], simd);
        
        const float32x2_t ad = vadd_f32(vget_high_f32(aq), vget_low_f32(aq));
        const float32x2_t bd = vadd_f32(vget_high_f32(bq), vget_low_f32(bq));
        const float32x2_t cd = vadd_f32(vget_high_f32(cq), vget_low_f32(cq));
        const float32x2_t dd = vadd_f32(vget_high_f32(dq), vget_low_f32(dq));
        
        this->m[i] = vec4_t<float>{
            vget_lane_f32(vpadd_f32(ad, ad), 0),
            vget_lane_f32(vpadd_f32(bd, bd), 0),
            vget_lane_f32(vpadd_f32(cd, cd), 0),
            vget_lane_f32(vpadd_f32(dd, dd), 0)
        };
    }

    return *this;
}
*/



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
template <> inline LS_INLINE
vec4_t<float> mat4_t<float>::operator*(const vec4_t<float>& v) const
{
    #if defined(LS_ARCH_AARCH64)
        const float32x4_t v0 =     vmulq_laneq_f32(    this->m[0].simd, v.simd, 0);
        const float32x4_t v1 =     vmlaq_laneq_f32(v0, this->m[1].simd, v.simd, 1);
        const float32x4_t v2 =     vmlaq_laneq_f32(v1, this->m[2].simd, v.simd, 2);
        return math::vec4_t<float>{vmlaq_laneq_f32(v2, this->m[3].simd, v.simd, 3)};
    #else
        const float32x4_t v0 =     vmulq_lane_f32(    this->m[0].simd, vget_low_f32(v.simd),  0);
        const float32x4_t v1 =     vmlaq_lane_f32(v0, this->m[1].simd, vget_low_f32(v.simd),  1);
        const float32x4_t v2 =     vmlaq_lane_f32(v1, this->m[2].simd, vget_high_f32(v.simd), 0);
        return math::vec4_t<float>{vmlaq_lane_f32(v2, this->m[3].simd, vget_high_f32(v.simd), 1)};
    #endif
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
inline LS_INLINE vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
    #if defined(LS_ARCH_AARCH64)
        float32x4_t aq = vmulq_f32(m[0].simd, simd);
        float32x4_t bq = vmulq_f32(m[1].simd, simd);
        float32x4_t cq = vmulq_f32(m[2].simd, simd);
        float32x4_t dq = vmulq_f32(m[3].simd, simd);

        return vec4_t<float>{
            vaddvq_f32(aq),
            vaddvq_f32(bq),
            vaddvq_f32(cq),
            vaddvq_f32(dq)
        };
    
    #else
        const float32x4_t aq = vmulq_f32(m[0].simd, simd);
        const float32x4_t bq = vmulq_f32(m[1].simd, simd);
        const float32x4_t cq = vmulq_f32(m[2].simd, simd);
        const float32x4_t dq = vmulq_f32(m[3].simd, simd);

        const float32x2_t ad = vadd_f32(vget_high_f32(aq), vget_low_f32(aq));
        const float32x2_t bd = vadd_f32(vget_high_f32(bq), vget_low_f32(bq));
        const float32x2_t cd = vadd_f32(vget_high_f32(cq), vget_low_f32(cq));
        const float32x2_t dd = vadd_f32(vget_high_f32(dq), vget_low_f32(dq));

        return vec4_t<float>{
            vget_lane_f32(vpadd_f32(ad, ad), 0),
            vget_lane_f32(vpadd_f32(bd, bd), 0),
            vget_lane_f32(vpadd_f32(cd, cd), 0),
            vget_lane_f32(vpadd_f32(dd, dd), 0)
        };

    #endif
}




} //end math namespace
} //end ls namespace
