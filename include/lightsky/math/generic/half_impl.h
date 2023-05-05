
#ifndef LS_MATH_HALF_IMPL_H
#define LS_MATH_HALF_IMPL_H

#include "lightsky/math/bits.h" // ls::math::clz_u32
#include "lightsky/math/scalar_utils.h" // ls::math::abs

namespace ls
{
namespace math
{
namespace impl
{

/**
 * @brief Helpful converter between float and halves using IEEE behavior.
 *
 * Conversion methods extrapolated from:
 * https://github.com/Maratyszcza/FP16/blob/master/include/fp16/fp16.h
 */
class Float16Converter
{
    static inline float fp32_from_bits(uint32_t bits) noexcept
    {
        const union
        {
            uint32_t u;
            float f;
        } result{bits};

        return result.f;
    }

    static inline uint32_t fp32_to_bits(float f) noexcept
    {
        const union
        {
            float f;
            uint32_t u;
        } result{f};

        return result.u;
    }

  public:
    static inline uint16_t LS_IMPERATIVE single_to_half(float value) noexcept
    {
        const float scale_to_inf = fp32_from_bits(0x77800000u);
        const float scale_to_zero = fp32_from_bits(0x08800000u);
        float base = (ls::math::abs(value) * scale_to_inf) * scale_to_zero;

        const uint32_t w = fp32_to_bits(value);
        const uint32_t shl1_w = w + w;
        const uint32_t sign = w & 0x80000000u;
        uint32_t bias = shl1_w & 0xFF000000u;

        if (bias < 0x71000000u)
        {
            bias = 0x71000000u;
        }

        base = fp32_from_bits((bias >> 1u) + 0x07800000u) + base;
        const uint32_t bits = fp32_to_bits(base);
        const uint32_t exp_bits = (bits >> 13u) & 0x00007C00u;
        const uint32_t mantissa_bits = bits & 0x00000FFFu;
        const uint32_t nonsign = exp_bits + mantissa_bits;
        const uint32_t result = (sign >> 16u) | (shl1_w > 0xFF000000u ? 0x00007E00u : nonsign);
        return (uint16_t)(result);
    }

    static inline float LS_IMPERATIVE half_to_single(uint16_t value) noexcept
    {
        const uint32_t w = (uint32_t)value << 16u;
        const uint32_t sign = w & 0x80000000u;
        const uint32_t nonsign = w & 0x7FFFFFFFu;
        uint32_t renorm_shift = ls::math::clz_u32(nonsign);
        renorm_shift = renorm_shift > 5u ? (renorm_shift - 5u) : 0u;
        const int32_t zero_mask = (int32_t) (nonsign - 1u) >> 31u;
        const uint32_t result = ((nonsign << renorm_shift >> 3u) + ((0x00000070u - renorm_shift) << 23u)) & ~zero_mask;
        return fp32_from_bits(sign | result);
    }
};

} // end impl namespace



/*-------------------------------------
 * Construct from a float
-------------------------------------*/
inline LS_INLINE half::half(const float f) noexcept :
    bits{impl::Float16Converter::single_to_half(f)}
{}



/*-------------------------------------
 * Convert from a float
-------------------------------------*/
inline LS_INLINE half& half::operator=(const float f) noexcept
{
    bits = impl::Float16Converter::single_to_half(f);
    return *this;
}



/*-------------------------------------
 * Cast to a float
-------------------------------------*/
inline LS_INLINE half::operator float() const noexcept
{
    return impl::Float16Converter::half_to_single(bits);
}



} // end math namespace
} // end ls namespace

#endif /* LS_MATH_HALF_IMPL_H */
