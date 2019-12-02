
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{
    alignas(sizeof(float32x4_t)) mat4_t<float> ret;

    ret[0].simd = vmulq_f32(             this->m[0].simd, vdupq_n_f32(n[0][0]));
    ret[0].simd = vmlaq_f32(ret[0].simd, this->m[1].simd, vdupq_n_f32(n[0][1]));
    ret[0].simd = vmlaq_f32(ret[0].simd, this->m[2].simd, vdupq_n_f32(n[0][2]));
    ret[0].simd = vmlaq_f32(ret[0].simd, this->m[3].simd, vdupq_n_f32(n[0][3]));

    ret[1].simd = vmulq_f32(             this->m[0].simd, vdupq_n_f32(n[1][0]));
    ret[1].simd = vmlaq_f32(ret[1].simd, this->m[1].simd, vdupq_n_f32(n[1][1]));
    ret[1].simd = vmlaq_f32(ret[1].simd, this->m[2].simd, vdupq_n_f32(n[1][2]));
    ret[1].simd = vmlaq_f32(ret[1].simd, this->m[3].simd, vdupq_n_f32(n[1][3]));

    ret[2].simd = vmulq_f32(             this->m[0].simd, vdupq_n_f32(n[2][0]));
    ret[2].simd = vmlaq_f32(ret[2].simd, this->m[1].simd, vdupq_n_f32(n[2][1]));
    ret[2].simd = vmlaq_f32(ret[2].simd, this->m[2].simd, vdupq_n_f32(n[2][2]));
    ret[2].simd = vmlaq_f32(ret[2].simd, this->m[3].simd, vdupq_n_f32(n[2][3]));

    ret[3].simd = vmulq_f32(             this->m[0].simd, vdupq_n_f32(n[3][0]));
    ret[3].simd = vmlaq_f32(ret[3].simd, this->m[1].simd, vdupq_n_f32(n[3][1]));
    ret[3].simd = vmlaq_f32(ret[3].simd, this->m[2].simd, vdupq_n_f32(n[3][2]));
    ret[3].simd = vmlaq_f32(ret[3].simd, this->m[3].simd, vdupq_n_f32(n[3][3]));

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
inline LS_INLINE vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
    #if 0
    const mat4_t<float> temp0{
        {vmulq_f32(this->simd, m[0].simd)},
        {vmulq_f32(this->simd, m[1].simd)},
        {vmulq_f32(this->simd, m[2].simd)},
        {vmulq_f32(this->simd, m[3].simd)}
    };

    const float32x4x4_t temp1 = vld4q_f32(&temp0[0]);
    
    return vec4_t<float>{vaddq_f32(temp1.val[3], vaddq_f32(temp1.val[2], vaddq_f32(temp1.val[1], temp1.val[0])))};
    
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
