
namespace ls {
namespace math {



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
inline vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
    float32x4_t ret;
    ret = vmulq_f32(     m[0].simd, simd);
    ret = vmlaq_f32(ret, m[1].simd, simd);
    ret = vmlaq_f32(ret, m[2].simd, simd);
    ret = vmlaq_f32(ret, m[3].simd, simd);
    
    return vec4_t<float>{ret};
}



} //end math namespace
} //end ls namespace
