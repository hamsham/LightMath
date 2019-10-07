
#ifndef LS_MATH_VEC2_H
#define LS_MATH_VEC2_H

#include "lightsky/setup/Api.h"

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/* 2x2 Matrix forward declaration */
template <typename num_t>
struct mat2_t;



/**----------------------------------------------------------------------------
 *  @brief 2D Vector Structure
 *
 *  Recommended for use with non-integral types
 *
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
-----------------------------------------------------------------------------*/
template <typename num_t>
struct alignas(sizeof(num_t)) vec2_t
{
    typedef num_t value_type;
    static constexpr unsigned num_components() noexcept { return 2; }

    // data
    num_t v[2];

    // Main Constructor
    constexpr vec2_t(num_t inX, num_t inY);

    // Delegated Constructors
    constexpr vec2_t();
    constexpr vec2_t(num_t n);
    constexpr vec2_t(const vec2_t<num_t>& input);
    constexpr vec2_t(vec2_t<num_t>&& input);

    ~vec2_t() = default;

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator vec2_t<other_t>() const;

    constexpr const num_t* operator&() const;
    inline num_t* operator&();

    // Subscripting Operators
    template <typename index_t>
    constexpr num_t operator[](index_t i) const;

    template <typename index_t>
    inline num_t& operator[](index_t i);

    //vector-vector operators
    constexpr vec2_t operator+(const vec2_t<num_t>&) const;
    constexpr vec2_t operator-(const vec2_t<num_t>&) const;
    constexpr vec2_t operator-() const;
    constexpr vec2_t operator*(const vec2_t<num_t>&) const;
    constexpr vec2_t operator/(const vec2_t<num_t>&) const;
    vec2_t& operator=(const vec2_t<num_t>&);
    vec2_t& operator=(vec2_t<num_t>&&);
    vec2_t& operator+=(const vec2_t<num_t>&);
    vec2_t& operator-=(const vec2_t<num_t>&);
    vec2_t& operator*=(const vec2_t<num_t>&);
    vec2_t& operator/=(const vec2_t<num_t>&);
    vec2_t& operator++(); //prefix operators
    vec2_t& operator--();
    vec2_t operator++(int); //postfix operators
    vec2_t operator--(int);
    constexpr bool operator==(const vec2_t<num_t>& compare) const; //comparisons
    constexpr bool operator!=(const vec2_t<num_t>& compare) const;
    constexpr bool operator<(const vec2_t<num_t>& compare) const;
    constexpr bool operator>(const vec2_t<num_t>& compare) const;
    constexpr bool operator<=(const vec2_t<num_t>& compare) const;
    constexpr bool operator>=(const vec2_t<num_t>& compare) const;

    //vector-matrix operators (implementation in the matrix2 header)
    constexpr mat2_t<num_t> operator+(const mat2_t<num_t>&) const;
    constexpr mat2_t<num_t> operator-(const mat2_t<num_t>&) const;
    constexpr vec2_t<num_t> operator*(const mat2_t<num_t>&) const;
    vec2_t& operator*=(const mat2_t<num_t>&);

    //vector-scalar operators
    vec2_t operator=(num_t);
    constexpr vec2_t operator+(num_t) const;
    constexpr vec2_t operator-(num_t) const;
    constexpr vec2_t operator*(num_t) const;
    constexpr vec2_t operator/(num_t) const;
    vec2_t& operator+=(num_t);
    vec2_t& operator-=(num_t);
    vec2_t& operator*=(num_t);
    vec2_t& operator/=(num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr
vec2_t<num_t> operator+(num_t n, const vec2_t<num_t>& v);

template <typename num_t> constexpr
vec2_t<num_t> operator-(num_t n, const vec2_t<num_t>& v);

template <typename num_t> constexpr
vec2_t<num_t> operator*(num_t n, const vec2_t<num_t>& v);

/*-------------------------------------
    2D Vector Specializations
-------------------------------------*/
/*
LS_DECLARE_STRUCT_TYPE(vec2f, vec2_t, float);
LS_DECLARE_STRUCT_TYPE(vec2d, vec2_t, double);
LS_DECLARE_STRUCT_TYPE(vec2i, vec2_t, int);
LS_DECLARE_STRUCT_TYPE(vec2ui, vec2_t, unsigned);
LS_DECLARE_STRUCT_TYPE(vec2x, vec2_t, medp_t);
LS_DECLARE_STRUCT_TYPE(vec2, vec2_t, LS_FLOAT);
*/
typedef vec2_t<float>    vec2f;
typedef vec2_t<double>   vec2d;
typedef vec2_t<int>      vec2i;
typedef vec2_t<unsigned> vec2u;
typedef vec2_t<medp_t>   vec2x;
typedef vec2_t<LS_FLOAT> vec2;

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/vec2_impl.h"

#endif /* LS_MATH_VEC2_H */
