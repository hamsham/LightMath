
#ifndef LS_MATH_HALFF_IMPL_H
#define LS_MATH_HALFF_IMPL_H

namespace ls
{
namespace math
{



/*-------------------------------------
 * Construct from a float
-------------------------------------*/
inline LS_INLINE half::half(const float f) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        float16x4_t temp = vcvt_f16_f32(vdupq_n_f32(f));
        bits = vreinterpret_u16_f16(temp)[0];
    #elif defined(LS_ARCH_ARM)
        union
        {
            __fp16 f;
            uint16_t i;
        } temp;
        temp.f = (__fp16)f;
        bits = temp.i;
    #else
        #error "Unknown ARM platform."
    #endif
}



/*-------------------------------------
 * Convert from a float
-------------------------------------*/
inline LS_INLINE half& half::operator=(const float f) noexcept
{
    #if defined(LS_ARCH_AARCH64)
        float16x4_t temp = vcvt_f16_f32(vdupq_n_f32(f));
        bits = vreinterpret_u16_f16(temp)[0];
    #elif defined(LS_ARCH_ARM)
        union
        {
            __fp16 f;
            uint16_t i;
        } temp;
        temp.f = (__fp16)f;
        bits = temp.i;
    #else
        #error "Unknown ARM platform."
    #endif

    return *this;
}



/*-------------------------------------
 * Cast to a float
-------------------------------------*/
inline LS_INLINE half::operator float() const noexcept
{
    #if defined(LS_ARCH_AARCH64)
        float32x4_t temp = vcvt_f32_f16(vreinterpret_f16_u16(vdup_n_u16(bits)));
        return temp[0];
    #elif defined(LS_ARCH_ARM)
        union
        {
            uint16_t i;
            __fp16 f;
        } temp{bits};
        return (float)temp.f;
    #else
        #error "Unknown ARM platform."
    #endif
}



} // end math namespace
} // end ls namespace

#endif /* LS_MATH_HALFF_IMPL_H */
