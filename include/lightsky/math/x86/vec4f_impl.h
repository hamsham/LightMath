
#include <xmmintrin.h>



namespace ls
{
namespace math
{



template<>
union LS_API alignas(sizeof(__m128)) vec4_t<float>
{
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
    constexpr explicit operator vec4_t<other_t>() const;

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
constexpr vec4_t<float>::vec4_t(float inX, float inY, float inZ, float inW) :
    //simd(_mm_setr_ps(inX, inY, inZ, inW))
    //simd(_mm_set_ps(inW, inZ, inY, inX))
    v{inX, inY, inZ, inW}
{
}

/*
constexpr vec4_t<float>::vec4_t() :
    v{0.f}
{
}
*/

inline vec4_t<float>::vec4_t(float n) :
    simd(_mm_set1_ps(n))
    //v{n, n, n, n}
{
}

constexpr vec4_t<float>::vec4_t(const __m128 n) :
    simd(n)
{
}

/*
constexpr vec4_t<float>::vec4_t(const vec4_t<float>& v) :
    simd(v.simd)
{
}

constexpr vec4_t<float>::vec4_t(vec4_t<float>&& v) :
    simd(v.simd)
{
}
*/

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
template<typename other_t>
constexpr vec4_t<float>::operator vec4_t<other_t>() const
{
    return vec4_t<other_t>{(other_t)v[0], (other_t)v[1], (other_t)v[2], (other_t)v[3]};
}

template <>
template <>
inline vec4_t<unsigned char>::operator vec4_t<float>() const
{
    const __m128i temp = _mm_set_epi32(v[3], v[2], v[1], v[0]);
    return vec4_t<float>{_mm_cvtepi32_ps(temp)};
}

inline const float* vec4_t<float>::operator&() const
{
    return v;
}

inline float* vec4_t<float>::operator&()
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
inline float& vec4_t<float>::operator[](index_t i)
{
    return v[i];
}

/*-------------------------------------
    Vector-Vector Math Operations
-------------------------------------*/
inline
vec4_t<float> vec4_t<float>::operator+(const vec4_t<float>& input) const
{
    return vec4_t{_mm_add_ps(simd, input.simd)};
}

inline
vec4_t<float> vec4_t<float>::operator-(const vec4_t<float>& input) const
{
    return vec4_t{_mm_sub_ps(simd, input.simd)};
}

//for operations like "vectA = -vectB"

inline
vec4_t<float> vec4_t<float>::operator-() const
{
    return vec4_t<float>{_mm_sub_ps(_mm_setzero_ps(), simd)};
}

inline
vec4_t<float> vec4_t<float>::operator*(const vec4_t<float>& input) const
{
    return vec4_t{_mm_mul_ps(simd, input.simd)};
}

inline
vec4_t<float> vec4_t<float>::operator/(const vec4_t<float>& input) const
{
    return vec4_t{_mm_div_ps(simd, input.simd)};
}

/*
inline
vec4_t<float>& vec4_t<float>::operator=(const vec4_t<float>& input)
{
    simd = input.simd;
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator=(vec4_t<float>&& input)
{
    simd = input.simd;
    return *this;
}
*/

inline
vec4_t<float>& vec4_t<float>::operator+=(const vec4_t<float>& input)
{
    simd = _mm_add_ps(simd, input.simd);
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator-=(const vec4_t<float>& input)
{
    simd = _mm_sub_ps(simd, input.simd);
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator*=(const vec4_t<float>& input)
{
    simd = _mm_mul_ps(simd, input.simd);
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator/=(const vec4_t<float>& input)
{
    simd = _mm_div_ps(simd, input.simd);
    return *this;
}

// prefix operations

inline
vec4_t<float>& vec4_t<float>::operator++()
{
    simd = _mm_add_ps(simd, _mm_set_ps1(1.f));
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator--()
{
    simd = _mm_sub_ps(simd, _mm_set_ps1(1.f));
    return *this;
}

//postfix operations

inline
vec4_t<float> vec4_t<float>::operator++(int)
{
    __m128 ret = simd;
    simd = _mm_add_ps(simd, _mm_set_ps1(1.f));
    return vec4_t<float>{ret};
}

inline
vec4_t<float> vec4_t<float>::operator--(int)
{
    __m128 ret = simd;
    simd = _mm_sub_ps(simd, _mm_set_ps1(1.f));
    return vec4_t<float>{ret};
}

//comparisons

constexpr
bool vec4_t<float>::operator==(const vec4_t<float>& compare) const
{
    return
        v[0] == compare.v[0] &&
        v[1] == compare.v[1] &&
        v[2] == compare.v[2] &&
        v[3] == compare.v[3];
}

constexpr
bool vec4_t<float>::operator!=(const vec4_t<float>& compare) const
{
    return
        v[0] != compare.v[0] ||
        v[1] != compare.v[1] ||
        v[2] != compare.v[2] ||
        v[3] != compare.v[3];
}

constexpr
bool vec4_t<float>::operator<(const vec4_t<float>& compare) const
{
    return
        v[0] < compare.v[0] &&
        v[1] < compare.v[1] &&
        v[2] < compare.v[2] &&
        v[3] < compare.v[3];
}

constexpr
bool vec4_t<float>::operator>(const vec4_t<float>& compare) const
{
    return
        v[0] > compare.v[0] &&
        v[1] > compare.v[1] &&
        v[2] > compare.v[2] &&
        v[3] > compare.v[3];
}

constexpr
bool vec4_t<float>::operator<=(const vec4_t<float>& compare) const
{
    return
        v[0] <= compare.v[0] &&
        v[1] <= compare.v[1] &&
        v[2] <= compare.v[2] &&
        v[3] <= compare.v[3];
}

constexpr
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
inline
vec4_t<float> vec4_t<float>::operator=(float input)
{
    simd = _mm_set_ps1(input);
    return *this;
}

inline
vec4_t<float> vec4_t<float>::operator+(float input) const
{
    return vec4_t<float>{_mm_add_ps(simd, _mm_set_ps1(input))};
}

inline
vec4_t<float> vec4_t<float>::operator-(float input) const
{
    return vec4_t<float>{_mm_sub_ps(simd, _mm_set_ps1(input))};
}

inline
vec4_t<float> vec4_t<float>::operator*(float input) const
{
    return vec4_t<float>{_mm_mul_ps(simd, _mm_set_ps1(input))};
}

inline
vec4_t<float> vec4_t<float>::operator/(float input) const
{
    return vec4_t<float>{_mm_div_ps(simd, _mm_set_ps1(input))};
}

inline
vec4_t<float>& vec4_t<float>::operator+=(float input)
{
    simd = _mm_add_ps(simd, _mm_set_ps1(input));
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator-=(float input)
{
    simd = _mm_sub_ps(simd, _mm_set_ps1(input));
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator*=(float input)
{
    simd = _mm_mul_ps(simd, _mm_set_ps1(input));
    return *this;
}

inline
vec4_t<float>& vec4_t<float>::operator/=(float input)
{
    simd = _mm_div_ps(simd, _mm_set_ps1(input));
    return *this;
}

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
inline
vec4_t<float> operator+(float n, const vec4_t<float>& v)
{
    return v + n;
}

inline
vec4_t<float> operator-(float n, const vec4_t<float>& v)
{
    return v - n;
}

inline
vec4_t<float> operator*(float n, const vec4_t<float>& v)
{
    return v * n;
}
} // end math namespace
} // end ls namespace
