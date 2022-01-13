
#ifndef LS_MATH_VEC4F_IMPL_H
#define LS_MATH_VEC4F_IMPL_H

#include <arm_neon.h>

#include "lightsky/setup/Api.h" // LS_INLINE



namespace ls
{
namespace math
{



template<>
union alignas(alignof(float32x4_t)) vec4_t<float>
{
    typedef float value_type;
    static constexpr unsigned num_components() noexcept { return 4; }

    // data
    float v[4];

    float32x4_t simd;

    ~vec4_t() = default;

    // Main Constructor
    constexpr vec4_t(float inX, float inY, float inZ, float inW);

    // Delegated Constructors
    vec4_t() = default;

    explicit constexpr vec4_t(const float32x4_t n);

    vec4_t(float n);

    vec4_t(const vec4_t<float>& input) = default;

    vec4_t(vec4_t<float>&& input) = default;

    // Conversions & Casting
    template<typename other_t>
    inline explicit operator vec4_t<other_t>() const;

    const float* operator&() const;

    inline float* operator&();

    // Subscripting Operators
    template <typename index_t>
    constexpr float operator[](index_t i) const;

    template <typename index_t>
    inline float& operator[](index_t i);

    // vector-vector operators
    vec4_t operator+(const vec4_t<float>&) const;

    vec4_t operator-(const vec4_t<float>&) const;

    vec4_t operator-() const;

    vec4_t operator*(const vec4_t<float>&) const;

    vec4_t operator/(const vec4_t<float>&) const;

    vec4_t& operator=(const vec4_t<float>&) = default;

    vec4_t& operator=(vec4_t<float>&&) = default;

    vec4_t& operator+=(const vec4_t<float>&);

    vec4_t& operator-=(const vec4_t<float>&);

    vec4_t& operator*=(const vec4_t<float>&);

    vec4_t& operator/=(const vec4_t<float>&);

    vec4_t& operator++(); //prefix operators
    vec4_t& operator--();

    vec4_t operator++(int); //postfix operators
    vec4_t operator--(int);

    constexpr bool operator==(const vec4_t<float>& compare) const; //comparisons

    constexpr bool operator!=(const vec4_t<float>& compare) const;

    constexpr bool operator<(const vec4_t<float>& compare) const;

    constexpr bool operator>(const vec4_t<float>& compare) const;

    constexpr bool operator<=(const vec4_t<float>& compare) const;

    constexpr bool operator>=(const vec4_t<float>& compare) const;

    // vector-matrix operators (implementation in the matrix4 header)
    constexpr mat4_t<float> operator+(const mat4_t<float>&) const;

    constexpr mat4_t<float> operator-(const mat4_t<float>&) const;

    vec4_t<float> operator*(const mat4_t<float>&) const;

    vec4_t& operator*=(const mat4_t<float>&);

    // vector-scalar operators
    vec4_t operator=(float);

    inline vec4_t operator+(float) const;

    inline vec4_t operator-(float) const;

    inline vec4_t operator*(float) const;

    inline vec4_t operator/(float) const;

    vec4_t& operator+=(float);

    vec4_t& operator-=(float);

    vec4_t& operator*=(float);

    vec4_t& operator/=(float);
};

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
constexpr LS_INLINE vec4_t<float>::vec4_t(float inX, float inY, float inZ, float inW) :
    v{inX, inY, inZ, inW}
{
}

/*
inline LS_INLINE vec4_t<float>::vec4_t(float inX, float inY, float inZ, float inW)
{
    const float temp[4] = {inX, inY, inZ, inW};
    simd = vld1q_f32(temp);
}
*/

/*
constexpr LS_INLINE vec4_t<float>::vec4_t() :
    v{0.f}
{
}
*/

inline LS_INLINE vec4_t<float>::vec4_t(float n) :
    simd{vdupq_n_f32(n)}
{
}

constexpr LS_INLINE vec4_t<float>::vec4_t(const float32x4_t n) :
    simd(n)
{
}

/*
constexpr LS_INLINE vec4_t<float>::vec4_t(const vec4_t<float>& v) :
    simd(v.simd)
{
}

constexpr LS_INLINE vec4_t<float>::vec4_t(vec4_t<float>&& v) :
    simd(v.simd)
{
}
*/

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
/*-------------------------------------
    Convert to 4D float
-------------------------------------*/
template<typename other_t>
inline LS_INLINE vec4_t<float>::operator vec4_t<other_t>() const
{
    return vec4_t<other_t>{(other_t)v[0], (other_t)v[1], (other_t)v[2], (other_t)v[3]};
}

template <>
template <>
inline LS_INLINE vec4_t<int8_t>::operator vec4_t<float>() const
{
    const int8x8_t val8 = vreinterpret_s8_u32(vld1_dup_u32(reinterpret_cast<const uint32_t*>(v)));
    const int16x8_t val16 = vmovl_s8(val8);
    const int32x4_t val32 = vmovl_s16(vget_low_s16(val16));
    return vec4_t<float>{vcvtq_f32_s32(val32)};
}

template <>
template <>
inline LS_INLINE vec4_t<int16_t>::operator vec4_t<float>() const
{
    const int16x4_t val16 = vreinterpret_s16_u64(vld1_dup_u64(reinterpret_cast<const uint64_t*>(v)));
    const int32x4_t val32 = vmovl_s16(val16);
    return vec4_t<float>{vcvtq_f32_s32(val32)};
}

template <>
template <>
inline LS_INLINE vec4_t<int32_t>::operator vec4_t<float>() const
{
    vec4_t<float> ret;
    vst1q_f32(ret.v, vcvtq_f32_s32(vld1q_s32(v)));
    return ret;
}

template <>
template <>
inline LS_INLINE vec4_t<uint8_t>::operator vec4_t<float>() const
{
    const uint8x8_t val8 = vreinterpret_u8_u32(vld1_dup_u32(reinterpret_cast<const uint32_t*>(v)));
    const uint16x8_t val16 = vmovl_u8(val8);
    const uint32x4_t val32 = vmovl_u16(vget_low_u16(val16));
    return vec4_t<float>{vcvtq_f32_u32(val32)};
}

template <>
template <>
inline LS_INLINE vec4_t<uint16_t>::operator vec4_t<float>() const
{
    const uint16x4_t val16 = vreinterpret_u16_u64(vld1_dup_u64(reinterpret_cast<const uint64_t*>(v)));
    const uint32x4_t val32 = vmovl_u16(val16);
    return vec4_t<float>{vcvtq_f32_u32(val32)};
}

template <>
template <>
inline LS_INLINE vec4_t<uint32_t>::operator vec4_t<float>() const
{
    vec4_t<float> ret;
    vst1q_f32(ret.v, vcvtq_f32_u32(vld1q_u32(v)));
    return ret;
}

template <>
template <>
inline LS_INLINE vec4_t<half>::operator vec4_t<float>() const
{
    return vec4_t<float>{vcvt_f32_f16(vld1_f16(reinterpret_cast<const float16_t*>(v)))};
}
 
/*-------------------------------------
    Convert to Other 4D Types
-------------------------------------*/
template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int8_t>() const
{
    union
    {
        int32_t i;
        vec4_t<int8_t> v;
    } ret;

    const int32x4_t val32 = vcvtq_s32_f32(this->simd);
    const int16x4_t val16 = vmovn_s32(val32);
    const int8x8_t val8 = vmovn_s16(vcombine_s16(val16, val16));

    vst1_lane_s32(&ret.i, vreinterpret_s32_s8(val8), 0);
    return ret.v;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int16_t>() const
{
    vec4_t<int16_t> ret;
    vst1_s16(ret.v, vmovn_s32(vcvtq_s32_f32(this->simd)));
    return ret;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int32_t>() const
{
    vec4_t<int32_t> ret;
    vst1q_s32(ret.v, vcvtq_s32_f32(this->simd));
    return ret;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint8_t>() const
{
    union
    {
        uint32_t i;
        vec4_t<uint8_t> v;
    } ret;

    const uint32x4_t val32 = vcvtq_u32_f32(this->simd);
    const uint16x4_t val16 = vmovn_u32(val32);
    const uint8x8_t val8 = vmovn_u16(vcombine_u16(val16, val16));

    vst1_lane_u32(&ret.i, vreinterpret_u32_u8(val8), 0);
    return ret.v;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint16_t>() const
{
    vec4_t<uint16_t> ret;
    vst1_u16(ret.v, vmovn_u32(vcvtq_u32_f32(this->simd)));
    return ret;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint32_t>() const
{
    vec4_t<uint32_t> ret;
    vst1q_u32(ret.v, vcvtq_u32_f32(this->simd));
    return ret;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<half>() const
{
    vec4_t<half> ret;
    vst1_f16(reinterpret_cast<float16_t*>(ret.v), vcvt_f16_f32(this->simd));
    return ret;
}
 
/*-------------------------------------
    Cast to a float pointer
-------------------------------------*/
inline LS_INLINE const float* vec4_t<float>::operator&() const
{
    return reinterpret_cast<const float*>(this);
}

inline LS_INLINE float* vec4_t<float>::operator&()
{
    return reinterpret_cast<float*>(this);
}

/*-------------------------------------
    Subscripting Operators
-------------------------------------*/
template <typename index_t>
constexpr LS_INLINE float vec4_t<float>::operator[](index_t i) const
{
    return v[i];
}

template <typename index_t>
inline LS_INLINE float& vec4_t<float>::operator[](index_t i)
{
    return v[i];
}

/*-------------------------------------
    Vector-Vector Math Operations
-------------------------------------*/
inline LS_INLINE
vec4_t<float> vec4_t<float>::operator+(const vec4_t<float>& input) const
{
    return vec4_t{vaddq_f32(simd, input.simd)};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator-(const vec4_t<float>& input) const
{
    return vec4_t{vsubq_f32(simd, input.simd)};
}

//for operations like "vectA = -vectB"

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator-() const
{
    return vec4_t<float>{vnegq_f32(simd)};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator*(const vec4_t<float>& input) const
{
    return vec4_t{vmulq_f32(simd, input.simd)};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator/(const vec4_t<float>& input) const
{
    #ifdef LS_ARCH_AARCH64
        return vec4_t<float>{vdivq_f32(simd, input.simd)};
    #else
        const float32x4_t recip = vrecpeq_f32(input.simd);
        return vec4_t<float>{vmulq_f32(simd, vmulq_f32(vrecpsq_f32(input.simd, recip), recip))};
    #endif
}

/*
inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator=(const vec4_t<float>& input)
{
    simd = input.simd;
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator=(vec4_t<float>&& input)
{
    simd = input.simd;
    return *this;
}
*/

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator+=(const vec4_t<float>& input)
{
    simd = vaddq_f32(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator-=(const vec4_t<float>& input)
{
    simd = vsubq_f32(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator*=(const vec4_t<float>& input)
{
    simd = vmulq_f32(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator/=(const vec4_t<float>& input)
{
    #ifdef LS_ARCH_AARCH64
        simd = vdivq_f32(simd, input.simd);
    #else
        const float32x4_t recip = vrecpeq_f32(input.simd);
        simd = vmulq_f32(simd, vmulq_f32(vrecpsq_f32(input.simd, recip), recip));
    #endif

    return *this;
}

// prefix operations

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator++()
{
    simd = vaddq_f32(simd, vdupq_n_f32(1.f));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator--()
{
    simd = vsubq_f32(simd, vdupq_n_f32(1.f));
    return *this;
}

//postfix operations

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator++(int)
{
    float32x4_t ret = simd;
    simd = vaddq_f32(simd, vdupq_n_f32(1.f));
    return vec4_t<float>{ret};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator--(int)
{
    float32x4_t ret = simd;
    simd = vsubq_f32(simd, vdupq_n_f32(1.f));
    return vec4_t<float>{ret};
}

//comparisons

constexpr LS_INLINE
bool vec4_t<float>::operator==(const vec4_t<float>& compare) const
{
    return
        v[0] == compare.v[0] &&
        v[1] == compare.v[1] &&
        v[2] == compare.v[2] &&
        v[3] == compare.v[3];
}

constexpr LS_INLINE
bool vec4_t<float>::operator!=(const vec4_t<float>& compare) const
{
    return
        v[0] != compare.v[0] ||
        v[1] != compare.v[1] ||
        v[2] != compare.v[2] ||
        v[3] != compare.v[3];
}

constexpr LS_INLINE
bool vec4_t<float>::operator<(const vec4_t<float>& compare) const
{
    return
        v[0] < compare.v[0] &&
        v[1] < compare.v[1] &&
        v[2] < compare.v[2] &&
        v[3] < compare.v[3];
}

constexpr LS_INLINE
bool vec4_t<float>::operator>(const vec4_t<float>& compare) const
{
    return
        v[0] > compare.v[0] &&
        v[1] > compare.v[1] &&
        v[2] > compare.v[2] &&
        v[3] > compare.v[3];
}

constexpr LS_INLINE
bool vec4_t<float>::operator<=(const vec4_t<float>& compare) const
{
    return
        v[0] <= compare.v[0] &&
        v[1] <= compare.v[1] &&
        v[2] <= compare.v[2] &&
        v[3] <= compare.v[3];
}

constexpr LS_INLINE
bool vec4_t<float>::operator>=(const vec4_t<float>& compare) const
{
    return
        v[0] >= compare.v[0] &&
        v[1] >= compare.v[1] &&
        v[2] >= compare.v[2] &&
        v[3] >= compare.v[3];
}

/*-------------------------------------
    Vector-Scalar Math Operations
-------------------------------------*/
inline LS_INLINE
vec4_t<float> vec4_t<float>::operator=(float input)
{
    simd = vdupq_n_f32(input);
    return *this;
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator+(float input) const
{
    return vec4_t<float>{vaddq_f32(simd, vdupq_n_f32(input))};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator-(float input) const
{
    return vec4_t<float>{vsubq_f32(simd, vdupq_n_f32(input))};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator*(float input) const
{
    return vec4_t<float>{vmulq_n_f32(simd, input)};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator/(float input) const
{
    const float32x4_t scalar = vdupq_n_f32(input);

    #ifdef LS_ARCH_AARCH64
        return vec4_t<float>{vdivq_f32(simd, scalar)};
    #else
        const float32x4_t recip = vrecpeq_f32(scalar);
        return vec4_t<float>{vmulq_f32(simd, vmulq_f32(vrecpsq_f32(scalar, recip), recip))};
    #endif
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator+=(float input)
{
    simd = vaddq_f32(simd, vdupq_n_f32(input));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator-=(float input)
{
    simd = vsubq_f32(simd, vdupq_n_f32(input));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator*=(float input)
{
    simd = vmulq_n_f32(simd, input);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator/=(float input)
{
    const float32x4_t scalar = vdupq_n_f32(input);

    #ifdef LS_ARCH_AARCH64
        simd = vdivq_f32(simd, scalar);
    #else
        const float32x4_t recip = vrecpeq_f32(scalar);
        simd = vmulq_f32(simd, vmulq_f32(vrecpsq_f32(scalar, recip), recip));
    #endif

    return *this;
}

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
inline LS_INLINE
vec4_t<float> operator+(float n, const vec4_t<float>& v)
{
    return v + n;
}

inline LS_INLINE
vec4_t<float> operator-(float n, const vec4_t<float>& v)
{
    return v - n;
}

inline LS_INLINE
vec4_t<float> operator*(float n, const vec4_t<float>& v)
{
    return v * n;
}
} // end math namespace
} // end ls namespace

#endif /* LS_MATH_VEC4F_IMPL_H */
