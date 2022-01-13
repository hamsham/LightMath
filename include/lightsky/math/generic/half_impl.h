
#ifndef LS_MATH_HALF_IMPL_H
#define LS_MATH_HALF_IMPL_H

namespace ls
{
namespace math
{
namespace impl
{

/**
 * @brief Helpful converter between float and halves.
 *
 * Source code provided by:
 * https://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion
 */
class Float16Converter
{
    union Bits
    {
        float f;
        int32_t si;
        uint32_t ui;
    };

    static constexpr int shift = 13;
    static constexpr int shiftSign = 16;

    static constexpr int32_t infN = 0x7F800000; // flt32 infinity
    static constexpr int32_t maxN = 0x477FE000; // max flt16 normal as a flt32
    static constexpr int32_t minN = 0x38800000; // min flt16 normal as a flt32
    static constexpr int32_t signN = 0x80000000; // flt32 sign bit

    static constexpr int32_t infC = infN >> shift;
    static constexpr int32_t nanN = (infC + 1) << shift; // minimum flt16 nan as a flt32
    static constexpr int32_t maxC = maxN >> shift;
    static constexpr int32_t minC = minN >> shift;
    static constexpr int32_t signC = signN >> shiftSign; // flt16 sign bit

    static constexpr int32_t mulN = 0x52000000; // (1 << 23) / minN
    static constexpr int32_t mulC = 0x33800000; // minN / (1 << (23 - shift))

    static constexpr int32_t subC = 0x003FF; // max flt32 subnormal down shifted
    static constexpr int32_t norC = 0x00400; // min flt32 normal down shifted

    static constexpr int32_t maxD = infC - maxC - 1;
    static constexpr int32_t minD = minC - subC - 1;

  public:
    static inline uint16_t LS_IMPERATIVE single_to_half(float value) noexcept
    {
        Bits v, s;
        v.f = value;
        uint32_t sign = v.si & signN;
        v.si ^= sign;
        sign >>= shiftSign; // logical shift
        s.si = mulN;
        s.si = s.f * v.f; // correct subnormals
        v.si ^= (s.si ^ v.si) & -(minN > v.si);
        v.si ^= (infN ^ v.si) & -((infN > v.si) & (v.si > maxN));
        v.si ^= (nanN ^ v.si) & -((nanN > v.si) & (v.si > infN));
        v.ui >>= shift; // logical shift
        v.si ^= ((v.si - maxD) ^ v.si) & -(v.si > maxC);
        v.si ^= ((v.si - minD) ^ v.si) & -(v.si > subC);
        return (uint16_t)(v.ui | sign);
    }

    static inline float LS_IMPERATIVE half_to_single(uint16_t value) noexcept
    {
        Bits v;
        v.ui = value;
        int32_t sign = v.si & signC;
        v.si ^= sign;
        sign <<= shiftSign;
        v.si ^= ((v.si + minD) ^ v.si) & -(v.si > subC);
        v.si ^= ((v.si + maxD) ^ v.si) & -(v.si > maxC);
        Bits s;
        s.si = mulC;
        s.f *= (float)v.si;
        int32_t mask = -(norC > v.si);
        v.si <<= shift;
        v.si ^= (s.si ^ v.si) & mask;
        v.si |= sign;
        return v.f;
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
