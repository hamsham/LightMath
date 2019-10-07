
#ifndef LS_MATH_VEC3_H
#define LS_MATH_VEC3_H

#include "lightsky/setup/Api.h"

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/* 3x3 Matrix forward declaration */
template <typename num_t>
struct mat3_t;



/**----------------------------------------------------------------------------
 *  @brief 3D Vector Structure
 *
 *  Recommended for use with non-integral types
 *
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
 *      2 = Z
-----------------------------------------------------------------------------*/
template <typename num_t>
struct alignas(sizeof(num_t)) vec3_t
{
    typedef num_t value_type;
    static constexpr unsigned num_components() noexcept { return 3; }

    // data
    num_t v[3];

    // Main Constructor
    constexpr vec3_t(num_t inX, num_t inY, num_t inZ);

    // Delegated Constructors
    vec3_t() = default;
    constexpr vec3_t(num_t n);
    constexpr vec3_t(const vec3_t<num_t>&) = default;
    constexpr vec3_t(vec3_t<num_t>&&) = default;

    ~vec3_t() = default;

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator vec3_t<other_t>() const;

    constexpr const num_t* operator&() const;
    inline num_t* operator&();

    // Subscripting Operators
    template <typename index_t>
    constexpr num_t operator[](index_t i) const;

    template <typename index_t>
    inline num_t& operator[](index_t i);

    //vector-vector operators
    constexpr vec3_t operator+(const vec3_t<num_t>&) const;
    constexpr vec3_t operator-(const vec3_t<num_t>&) const;
    constexpr vec3_t operator-() const;
    constexpr vec3_t operator*(const vec3_t<num_t>&) const;
    constexpr vec3_t operator/(const vec3_t<num_t>&) const;
    vec3_t& operator=(const vec3_t<num_t>&) = default;
    vec3_t& operator=(vec3_t<num_t>&&) = default;
    vec3_t& operator+=(const vec3_t<num_t>&);
    vec3_t& operator-=(const vec3_t<num_t>&);
    vec3_t& operator*=(const vec3_t<num_t>&);
    vec3_t& operator/=(const vec3_t<num_t>&);
    vec3_t& operator++(); //prefix operators
    vec3_t& operator--();
    vec3_t operator++(int); //postfix operators
    vec3_t operator--(int);
    constexpr bool operator==(const vec3_t<num_t>& compare) const; //comparisons
    constexpr bool operator!=(const vec3_t<num_t>& compare) const;
    constexpr bool operator<(const vec3_t<num_t>& compare) const;
    constexpr bool operator>(const vec3_t<num_t>& compare) const;
    constexpr bool operator<=(const vec3_t<num_t>& compare) const;
    constexpr bool operator>=(const vec3_t<num_t>& compare) const;

    //vector-matrix operators (implementation in the matrix3 header)
    constexpr mat3_t<num_t> operator+(const mat3_t<num_t>&) const;
    constexpr mat3_t<num_t> operator-(const mat3_t<num_t>&) const;
    constexpr vec3_t<num_t> operator*(const mat3_t<num_t>&) const;
    vec3_t& operator*=(const mat3_t<num_t>&);

    //vector-scalar operators
    vec3_t operator=(num_t);
    constexpr vec3_t operator+(num_t) const;
    constexpr vec3_t operator-(num_t) const;
    constexpr vec3_t operator*(num_t) const;
    constexpr vec3_t operator/(num_t) const;
    vec3_t& operator+=(num_t);
    vec3_t& operator-=(num_t);
    vec3_t& operator*=(num_t);
    vec3_t& operator/=(num_t);
};

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr
vec3_t<num_t> operator+(num_t n, const vec3_t<num_t>& v);

template <typename num_t> constexpr
vec3_t<num_t> operator-(num_t n, const vec3_t<num_t>& v);

template <typename num_t> constexpr
vec3_t<num_t> operator*(num_t n, const vec3_t<num_t>& v);

/*-------------------------------------
    3D Vector Specializations
-------------------------------------*/
/*
LS_DECLARE_STRUCT_TYPE(vec3f, vec3_t, float);
LS_DECLARE_STRUCT_TYPE(vec3f, vec3_t, float);
LS_DECLARE_STRUCT_TYPE(vec3d, vec3_t, double);
LS_DECLARE_STRUCT_TYPE(vec3i, vec3_t, int);
LS_DECLARE_STRUCT_TYPE(vec3ui, vec3_t, unsigned);
LS_DECLARE_STRUCT_TYPE(vec3x, vec3_t, medp_t);
LS_DECLARE_STRUCT_TYPE(vec3, vec3_t, LS_FLOAT);
*/
typedef vec3_t<float>    vec3f;
typedef vec3_t<double>   vec3d;
typedef vec3_t<int>      vec3i;
typedef vec3_t<unsigned> vec3u;
typedef vec3_t<medp_t>   vec3x;
typedef vec3_t<LS_FLOAT> vec3;

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/vec3_impl.h"

#endif /* LS_MATH_VEC3_H */
