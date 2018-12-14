
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
inline LS_INLINE vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
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
}



} //end math namespace
} //end ls namespace
