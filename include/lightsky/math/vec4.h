
#ifndef LS_MATH_VEC4_H
#define LS_MATH_VEC4_H

#include "lightsky/setup/Api.h"
#include "lightsky/setup/Arch.h"

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/* 4x4 Matrix forward declaration */
template <typename num_t>
struct mat4_t;



/**----------------------------------------------------------------------------
 *  @brief 4D Vector Structure
 *
 *  Recommended for use with non-integral types
 *
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
 *      2 = Z
 *      3 = W
-----------------------------------------------------------------------------*/
template <typename num_t>
union LS_API vec4_t {
    // data
    num_t v[4];

    // Main Constructor
    constexpr vec4_t(num_t inX, num_t inY, num_t inZ, num_t inW);

    // Delegated Constructors
    constexpr vec4_t() = default;
    constexpr vec4_t(num_t n);
    constexpr vec4_t(const vec4_t<num_t>& input);
    constexpr vec4_t(vec4_t<num_t>&& input);

    ~vec4_t() = default;

    // Conversions & Casting
    template <typename other_t>
    inline explicit operator vec4_t<other_t>() const;

    const num_t* operator&() const;
    inline num_t* operator&();

    // Subscripting Operators
    template <typename index_t>
    constexpr num_t operator[](index_t i) const;

    template <typename index_t>
    inline num_t& operator[](index_t i);

    // vector-vector operators
    constexpr vec4_t operator+(const vec4_t<num_t>&) const;
    constexpr vec4_t operator-(const vec4_t<num_t>&) const;
    constexpr vec4_t operator-() const;
    constexpr vec4_t operator*(const vec4_t<num_t>&) const;
    constexpr vec4_t operator/(const vec4_t<num_t>&) const;
    vec4_t& operator=(const vec4_t<num_t>&);
    vec4_t& operator=(vec4_t<num_t>&&);
    vec4_t& operator+=(const vec4_t<num_t>&);
    vec4_t& operator-=(const vec4_t<num_t>&);
    vec4_t& operator*=(const vec4_t<num_t>&);
    vec4_t& operator/=(const vec4_t<num_t>&);
    vec4_t& operator++(); //prefix operators
    vec4_t& operator--();
    vec4_t operator++(int); //postfix operators
    vec4_t operator--(int);
    constexpr bool operator==(const vec4_t<num_t>& compare) const; //comparisons
    constexpr bool operator!=(const vec4_t<num_t>& compare) const;
    constexpr bool operator<(const vec4_t<num_t>& compare) const;
    constexpr bool operator>(const vec4_t<num_t>& compare) const;
    constexpr bool operator<=(const vec4_t<num_t>& compare) const;
    constexpr bool operator>=(const vec4_t<num_t>& compare) const;

    // vector-matrix operators (implementation in the matrix4 header)
    constexpr mat4_t<num_t> operator+(const mat4_t<num_t>&) const;
    constexpr mat4_t<num_t> operator-(const mat4_t<num_t>&) const;
    constexpr vec4_t<num_t> operator*(const mat4_t<num_t>&) const;
    vec4_t& operator*=(const mat4_t<num_t>&);

    // vector-scalar operators
    vec4_t operator=(num_t);
    constexpr vec4_t operator+(num_t) const;
    constexpr vec4_t operator-(num_t) const;
    constexpr vec4_t operator*(num_t) const;
    constexpr vec4_t operator/(num_t) const;
    vec4_t& operator+=(num_t);
    vec4_t& operator-=(num_t);
    vec4_t& operator*=(num_t);
    vec4_t& operator/=(num_t);
};

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr
vec4_t<num_t> operator+(num_t n, const vec4_t<num_t>& v);

template <typename num_t> constexpr
vec4_t<num_t> operator-(num_t n, const vec4_t<num_t>& v);

template <typename num_t> constexpr
vec4_t<num_t> operator*(num_t n, const vec4_t<num_t>& v);

/*-------------------------------------
    4D Vector Specializations
-------------------------------------*/
/*
LS_DECLARE_STRUCT_TYPE(vec4f, vec4_t, float);
LS_DECLARE_STRUCT_TYPE(vec4d, vec4_t, double);
LS_DECLARE_STRUCT_TYPE(vec4i, vec4_t, int);
LS_DECLARE_STRUCT_TYPE(vec4ui, vec4_t, unsigned);
LS_DECLARE_STRUCT_TYPE(vec4x, vec4_t, medp_t);
LS_DECLARE_STRUCT_TYPE(vec4, vec4_t, LS_FLOAT);
*/
typedef vec4_t<float>    vec4f;
typedef vec4_t<double>   vec4d;
typedef vec4_t<int>      vec4i;
typedef vec4_t<unsigned> vec4u;
typedef vec4_t<medp_t>   vec4x;
typedef vec4_t<LS_FLOAT> vec4;

} //end math namespace
} //end ls namespace

#ifdef LS_ARCH_X86
    #include "lightsky/math/x86/vec4f_impl.h"
#elif defined(LS_ARCH_ARM)
    #include "lightsky/math/arm/vec4f_impl.h"
#endif

#include "lightsky/math/generic/vec4_impl.h"

#endif /* LS_MATH_VEC4_H */
