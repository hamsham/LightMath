
#include "lightsky/setup/Compiler.h"

#ifdef LS_COMPILER_MSC
    #include <intrin.h>
#endif /* LS_COMPILER_MSC */

extern "C" {
    #include <immintrin.h>
}



namespace ls
{
namespace math
{



template<>
union alignas(alignof(__m128)) vec4_t<float>
{
    typedef float value_type;
    static constexpr unsigned num_components() noexcept { return 4; }

    // data
    __m128 simd;

    float v[4];

    // Main Constructor
    constexpr vec4_t(float inX, float inY, float inZ, float inW);

    // Delegated Constructors
    vec4_t() = default;

    explicit constexpr vec4_t(__m128 n);

    vec4_t(float n);

    vec4_t(const vec4_t<float>& input) = default;

    vec4_t(vec4_t<float>&& input) = default;

    ~vec4_t() = default;

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

    vec4_t& operator=(const vec4_t<float>&) noexcept = default;

    vec4_t& operator=(vec4_t<float>&&) noexcept = default;

    vec4_t& operator+=(const vec4_t<float>&);

    vec4_t& operator-=(const vec4_t<float>&);

    vec4_t& operator*=(const vec4_t<float>&);

    vec4_t& operator/=(const vec4_t<float>&);

    vec4_t& operator++(); //prefix operators
    vec4_t& operator--();

    vec4_t operator++(int); //postfix operators
    vec4_t operator--(int);

    inline bool operator==(const vec4_t<float>& compare) const; //comparisons

    inline bool operator!=(const vec4_t<float>& compare) const;

    inline bool operator<(const vec4_t<float>& compare) const;

    inline bool operator>(const vec4_t<float>& compare) const;

    inline bool operator<=(const vec4_t<float>& compare) const;

    inline bool operator>=(const vec4_t<float>& compare) const;

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

static_assert(std::is_trivial<vec4_t<float>>::value, "Vec4f must be trivial.");

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
constexpr LS_INLINE vec4_t<float>::vec4_t(float inX, float inY, float inZ, float inW) :
    v{inX, inY, inZ, inW}
    //simd(_mm_set_ps(inW, inZ, inY, inX))
    //simd{inX, inY, inZ, inW}
{
    //this->simd = _mm_set_ps(inW, inZ, inY, inX);
}

/*
constexpr LS_INLINE vec4_t<float>::vec4_t() :
    v{0.f}
{
}
*/

inline LS_INLINE vec4_t<float>::vec4_t(float n) :
    simd(_mm_set1_ps(n))
    //v{n, n, n, n}
{
    //this->simd = _mm_set1_ps(n);
}

constexpr LS_INLINE vec4_t<float>::vec4_t(const __m128 n) :
    simd(n)
{
    //this->simd = n;
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
template<typename other_t>
inline LS_INLINE vec4_t<float>::operator vec4_t<other_t>() const
{
    return vec4_t<other_t>{(other_t)v[0], (other_t)v[1], (other_t)v[2], (other_t)v[3]};
}

template <>
template <>
inline LS_INLINE vec4_t<int8_t>::operator vec4_t<float>() const
{
    const __m128i vals = _mm_castps_si128(_mm_load1_ps(reinterpret_cast<const float*>(v)));
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepu8_epi32(vals))};
}

template <>
template <>
inline LS_INLINE vec4_t<int16_t>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(v))))};
}

template <>
template <>
inline LS_INLINE vec4_t<int32_t>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtepi32_ps(reinterpret_cast<const __m128i&>(*this))};
}

#ifdef LS_X86_SSE4_1

template <>
template <>
inline LS_INLINE vec4_t<uint8_t>::operator vec4_t<float>() const
{
    const __m128i vals = _mm_castps_si128(_mm_load1_ps(reinterpret_cast<const float*>(v)));
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepu8_epi32(vals))};
}

template <>
template <>
inline LS_INLINE vec4_t<uint16_t>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(v))))};
}

template <>
template <>
inline LS_INLINE vec4_t<uint32_t>::operator vec4_t<float>() const
{
    //return vec4_t<float>{_mm_cvtepi32_ps(_mm_lddqu_si128(reinterpret_cast<const __m128i*>(v)))};
    const __m128i& v0 = reinterpret_cast<const __m128i&>(*this);
    __m128i v2  = _mm_srli_epi32(v0, 1);
    __m128i v1  = _mm_and_si128(v0, _mm_set1_epi32(1));
    __m128  v2f = _mm_cvtepi32_ps(v2);
    __m128  v1f = _mm_cvtepi32_ps(v1);
    return vec4_t<float>{_mm_add_ps(_mm_add_ps(v2f, v2f), v1f)};
}

#endif

#if defined(LS_X86_FP16)
template <>
template <>
inline LS_INLINE vec4_t<half>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtph_ps(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(v)))};
}
#endif

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int8_t>() const
{
    const __m128i data = _mm_cvtps_epi32(simd);
    const __m128i perms = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, 8, 4, 0);

    union
    {
        const __m128i i;
        const vec4_t<int8_t> v;
    } ret{_mm_shuffle_epi8(data, perms)};
    return ret.v;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int16_t>() const
{
    const __m128i data = _mm_cvtps_epi32(simd);

    union
    {
        const __m128i i;
        const vec4_t<int16_t> v;
    } ret{_mm_packs_epi32(data, _mm_setzero_si128())};
    return ret.v;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int32_t>() const
{
    union
    {
        const __m128i simd;
        const vec4_t<int32_t> vec;
    } data{_mm_cvtps_epi32(simd)};

    return data.vec;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint8_t>() const
{
    const __m128i data = _mm_cvtps_epi32(simd);
    const __m128i perms = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, 8, 4, 0);

    union
    {
        const __m128i i;
        const vec4_t<uint8_t> v;
    } ret{_mm_shuffle_epi8(data, perms)};
    return ret.v;
}

#ifdef LS_X86_SSE4_1

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint16_t>() const
{
    const __m128i data = _mm_cvtps_epi32(simd);

    union
    {
        const __m128i i;
        const vec4_t<uint16_t> v;
    } ret{_mm_packus_epi32(data, _mm_setzero_si128())};
    return ret.v;
}

#endif

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint32_t>() const
{
    union
    {
        const __m128i simd;
        const vec4_t<uint32_t> vec;
    } data{_mm_cvtps_epi32(simd)};

    return data.vec;
}

#if defined(LS_X86_FP16)
template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<half>() const
{
    #if defined(LS_COMPILER_MSC)
        const __m128i data = _mm_cvtps_ph(simd, _MM_FROUND_TO_ZERO);
    #else
        const __m128i data = _mm_cvtps_ph(simd, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
    #endif

    vec4_t<half> ret;
    _mm_storel_pi(reinterpret_cast<__m64*>(ret.v), _mm_castsi128_ps(data));

    return ret;
}
#endif

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
constexpr float vec4_t<float>::operator[](index_t i) const
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
    return vec4_t{_mm_add_ps(simd, input.simd)};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator-(const vec4_t<float>& input) const
{
    return vec4_t{_mm_sub_ps(simd, input.simd)};
}

//for operations like "vectA = -vectB"

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator-() const
{
    //return vec4_t<float>{_mm_sub_ps(_mm_setzero_ps(), simd)};
    return vec4_t{_mm_xor_ps(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)), simd)};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator*(const vec4_t<float>& input) const
{
    return vec4_t{_mm_mul_ps(simd, input.simd)};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator/(const vec4_t<float>& input) const
{
    return vec4_t{_mm_div_ps(simd, input.simd)};
}

/*
inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator=(const vec4_t<float>& input) noexcept
{
       this->simd = input.simd;
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator=(vec4_t<float>&& input) noexcept
{
    this->simd = input.simd;
    return *this;
}
*/

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator+=(const vec4_t<float>& input)
{
    this->simd = _mm_add_ps(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator-=(const vec4_t<float>& input)
{
    this->simd = _mm_sub_ps(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator*=(const vec4_t<float>& input)
{
    this->simd = _mm_mul_ps(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator/=(const vec4_t<float>& input)
{
    this->simd = _mm_div_ps(simd, input.simd);
    return *this;
}

// prefix operations

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator++()
{
    this->simd = _mm_add_ps(simd, _mm_set1_ps(1.f));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator--()
{
    this->simd = _mm_sub_ps(simd, _mm_set1_ps(1.f));
    return *this;
}

//postfix operations

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator++(int)
{
    __m128 ret = simd;
    this->simd = _mm_add_ps(simd, _mm_set1_ps(1.f));
    return vec4_t<float>{ret};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator--(int)
{
    __m128 ret = simd;
    this->simd = _mm_sub_ps(simd, _mm_set1_ps(1.f));
    return vec4_t<float>{ret};
}

//comparisons

inline LS_INLINE bool vec4_t<float>::operator==(const vec4_t<float>& compare) const
{
    return _mm_movemask_ps(_mm_cmpeq_ps(simd, compare.simd)) == 0x0F;
}

inline LS_INLINE bool vec4_t<float>::operator!=(const vec4_t<float>& compare) const
{
    return _mm_movemask_ps(_mm_cmpneq_ps(simd, compare.simd)) == 0x0F;
}

inline LS_INLINE bool vec4_t<float>::operator<(const vec4_t<float>& compare) const
{
    return _mm_movemask_ps(_mm_cmplt_ps(simd, compare.simd)) == 0x0F;
}

inline LS_INLINE bool vec4_t<float>::operator>(const vec4_t<float>& compare) const
{
    return _mm_movemask_ps(_mm_cmpgt_ps(simd, compare.simd)) == 0x0F;
}

inline LS_INLINE bool vec4_t<float>::operator<=(const vec4_t<float>& compare) const
{
    return _mm_movemask_ps(_mm_cmple_ps(simd, compare.simd)) == 0x0F;
}

inline LS_INLINE bool vec4_t<float>::operator>=(const vec4_t<float>& compare) const
{
    return _mm_movemask_ps(_mm_cmpge_ps(simd, compare.simd)) == 0x0F;
}

/*-------------------------------------
    Vector-Scalar Math Operations
-------------------------------------*/
inline LS_INLINE vec4_t<float> vec4_t<float>::operator=(float input)
{
    this->simd = _mm_set1_ps(input);
    return *this;
}

inline LS_INLINE vec4_t<float> vec4_t<float>::operator+(float input) const
{
    return vec4_t<float>{_mm_add_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE vec4_t<float> vec4_t<float>::operator-(float input) const
{
    return vec4_t<float>{_mm_sub_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE vec4_t<float> vec4_t<float>::operator*(float input) const
{
    return vec4_t<float>{_mm_mul_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE vec4_t<float> vec4_t<float>::operator/(float input) const
{
    return vec4_t<float>{_mm_div_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE vec4_t<float>& vec4_t<float>::operator+=(float input)
{
    this->simd = _mm_add_ps(simd, _mm_set1_ps(input));
    return *this;
}

inline LS_INLINE vec4_t<float>& vec4_t<float>::operator-=(float input)
{
    this->simd = _mm_sub_ps(simd, _mm_set1_ps(input));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator*=(float input)
{
    this->simd = _mm_mul_ps(simd, _mm_set1_ps(input));
    return *this;
}

inline LS_INLINE vec4_t<float>& vec4_t<float>::operator/=(float input)
{
    this->simd = _mm_div_ps(simd, _mm_set1_ps(input));
    return *this;
}

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
inline LS_INLINE vec4_t<float> operator+(float n, const vec4_t<float>& v)
{
    return v + n;
}

inline LS_INLINE vec4_t<float> operator-(float n, const vec4_t<float>& v)
{
    return v - n;
}

inline LS_INLINE vec4_t<float> operator*(float n, const vec4_t<float>& v)
{
    return v * n;
}
} // end math namespace
} // end ls namespace
