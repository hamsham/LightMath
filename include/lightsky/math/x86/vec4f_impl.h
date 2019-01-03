
#include <immintrin.h>



namespace ls
{
namespace math
{



template<>
union LS_API alignas(sizeof(__m128)) vec4_t<float>
{
    typedef float value_type;
    static constexpr unsigned num_components() noexcept { return 4; }

    // data
    float v[4];

    __m128 simd;

    // Main Constructor
    constexpr vec4_t(float inX, float inY, float inZ, float inW);

    // Delegated Constructors
    vec4_t() = default;

    constexpr vec4_t(const __m128 n);

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
    //simd(_mm_setr_ps(inX, inY, inZ, inW))
    //simd(_mm_set_ps(inW, inZ, inY, inX))
    simd{inX, inY, inZ, inW}
{
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
}

constexpr LS_INLINE vec4_t<float>::vec4_t(const __m128 n) :
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
template<typename other_t>
inline LS_INLINE vec4_t<float>::operator vec4_t<other_t>() const
{
    return vec4_t<other_t>{(other_t)v[0], (other_t)v[1], (other_t)v[2], (other_t)v[3]};
}

template <>
template <>
inline LS_INLINE vec4_t<uint8_t>::operator vec4_t<float>() const
{
    const __m128i mask = _mm_set_epi32(0, 0, 0, 0xFFFFFFFF);
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepu8_epi32(_mm_maskload_epi32(reinterpret_cast<const int32_t*>(v), mask)))};
}

template <>
template <>
inline LS_INLINE vec4_t<int8_t>::operator vec4_t<float>() const
{
    const __m128i mask = _mm_set_epi32(0, 0, 0, 0xFFFFFFFF);
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepi8_epi32(_mm_maskload_epi32(reinterpret_cast<const int32_t*>(v), mask)))};
}

template <>
template <>
inline LS_INLINE vec4_t<uint16_t>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(v))))};
}

template <>
template <>
inline LS_INLINE vec4_t<int16_t>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(v))))};
}

template <>
template <>
inline LS_INLINE vec4_t<uint32_t>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_lddqu_si128(reinterpret_cast<const __m128i*>(v)))};
}

template <>
template <>
inline LS_INLINE vec4_t<int32_t>::operator vec4_t<float>() const
{
    return vec4_t<float>{_mm_cvtepi32_ps(_mm_lddqu_si128(reinterpret_cast<const __m128i*>(v)))};
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint8_t>() const
{
    const __m128i data = _mm_cvtps_epi32(simd);
    const __m128i perms = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, 8, 4, 0);

    union
    {
        const int32_t i;
        const vec4_t<uint8_t> v;
    } ret{_mm_cvtsi128_si32(_mm_shuffle_epi8(data, perms))};
    return ret.v;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int8_t>() const
{
    const __m128i data = _mm_cvtps_epi32(simd);
    const __m128i perms = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, 8, 4, 0);

    union
    {
        const int32_t i;
        const vec4_t<int8_t> v;
    } ret{_mm_cvtsi128_si32(_mm_shuffle_epi8(data, perms))};
    return ret.v;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<uint16_t>() const
{
    const __m128i data = _mm_packs_epi32(_mm_cvtps_epi32(simd), _mm_setzero_si128());

    union
    {
        const int64_t i;
        const vec4_t<uint16_t> v;
    } ret{_mm_cvtsi128_si64(data)};
    return ret.v;
}

template <>
inline LS_INLINE vec4_t<float>::operator vec4_t<int16_t>() const
{
    const __m128i data = _mm_packs_epi32(_mm_cvtps_epi32(simd), _mm_setzero_si128());

    union
    {
        const int64_t i;
        const vec4_t<int16_t> v;
    } ret{_mm_cvtsi128_si64(data)};
    return ret.v;
}

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

inline LS_INLINE const float* vec4_t<float>::operator&() const
{
    return v;
}

inline LS_INLINE float* vec4_t<float>::operator&()
{
    return v;
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
    return vec4_t<float>{_mm_sub_ps(_mm_setzero_ps(), simd)};
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
    simd = _mm_add_ps(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator-=(const vec4_t<float>& input)
{
    simd = _mm_sub_ps(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator*=(const vec4_t<float>& input)
{
    simd = _mm_mul_ps(simd, input.simd);
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator/=(const vec4_t<float>& input)
{
    simd = _mm_div_ps(simd, input.simd);
    return *this;
}

// prefix operations

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator++()
{
    simd = _mm_add_ps(simd, _mm_set1_ps(1.f));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator--()
{
    simd = _mm_sub_ps(simd, _mm_set1_ps(1.f));
    return *this;
}

//postfix operations

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator++(int)
{
    __m128 ret = simd;
    simd = _mm_add_ps(simd, _mm_set1_ps(1.f));
    return vec4_t<float>{ret};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator--(int)
{
    __m128 ret = simd;
    simd = _mm_sub_ps(simd, _mm_set1_ps(1.f));
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
    simd = _mm_set1_ps(input);
    return *this;
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator+(float input) const
{
    return vec4_t<float>{_mm_add_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator-(float input) const
{
    return vec4_t<float>{_mm_sub_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator*(float input) const
{
    return vec4_t<float>{_mm_mul_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE
vec4_t<float> vec4_t<float>::operator/(float input) const
{
    return vec4_t<float>{_mm_div_ps(simd, _mm_set1_ps(input))};
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator+=(float input)
{
    simd = _mm_add_ps(simd, _mm_set1_ps(input));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator-=(float input)
{
    simd = _mm_sub_ps(simd, _mm_set1_ps(input));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator*=(float input)
{
    simd = _mm_mul_ps(simd, _mm_set1_ps(input));
    return *this;
}

inline LS_INLINE
vec4_t<float>& vec4_t<float>::operator/=(float input)
{
    simd = _mm_div_ps(simd, _mm_set1_ps(input));
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
