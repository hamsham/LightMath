
#ifndef LS_MATH_MAT2_H
#define LS_MATH_MAT2_H

#include "lightsky/math/fixed.h"
#include "lightsky/math/vec2.h"

namespace ls {
namespace math {

struct half;



/**
 *  @brief 2D Matrix Structure
 *  recommended for use with non-integral types
 *
 *  @note
 *  Matrix is Row-Major
 *  Orientation is as follows:
 *      0[0-1] = XX  XY
 *      1[0-1] = YX  YY
 */
template <typename num_t>
struct alignas(sizeof(num_t)) mat2_t
{
    // data
    vec2_t<num_t> m[2];

    ~mat2_t() = default;

    constexpr mat2_t(
        num_t inXX, num_t inXY,
        num_t inYX, num_t inYY
    );

    // Delegated constructors
    constexpr mat2_t() = default;
    constexpr mat2_t(num_t);
    constexpr mat2_t(const mat2_t<num_t>&);
    constexpr mat2_t(mat2_t<num_t>&&);
    constexpr mat2_t(
        const vec2_t<num_t>& x,
        const vec2_t<num_t>& y
    );

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator mat2_t<other_t>() const;

    // Subscripting
    template <typename index_t>
    constexpr const vec2_t<num_t>& operator[](index_t i) const;

    template <typename index_t>
    inline vec2_t<num_t>& operator[](index_t i);

    //mat-mat operators
    mat2_t& operator++(); //prefix operators
    mat2_t& operator--();
    mat2_t operator++(int); //postfix operators
    mat2_t operator--(int);
    constexpr mat2_t operator+(const mat2_t<num_t>& input) const;
    constexpr mat2_t operator-(const mat2_t<num_t>& input) const;
    constexpr mat2_t operator-() const;
    constexpr mat2_t operator*(const mat2_t<num_t>& input) const;
    mat2_t& operator=(const mat2_t<num_t>& input);
    mat2_t& operator=(mat2_t<num_t>&& input);
    mat2_t& operator+=(const mat2_t<num_t>& input);
    mat2_t& operator-=(const mat2_t<num_t>& input);
    mat2_t& operator*=(const mat2_t<num_t>& input);
    constexpr bool operator==(const mat2_t<num_t>& input) const;
    constexpr bool operator!=(const mat2_t<num_t>& input) const;

    //mat-vector operators
    constexpr mat2_t operator+(const vec2_t<num_t>&) const;
    constexpr mat2_t operator-(const vec2_t<num_t>&) const;
    constexpr vec2_t<num_t> operator*(const vec2_t<num_t>&) const;
    mat2_t& operator=(const vec2_t<num_t>&);
    mat2_t& operator+=(const vec2_t<num_t>&);
    mat2_t& operator-=(const vec2_t<num_t>&);

    //mat-scalar operators
    constexpr mat2_t operator+(num_t) const;
    constexpr mat2_t operator-(num_t) const;
    constexpr mat2_t operator*(num_t) const;
    constexpr mat2_t operator/(num_t) const;
    mat2_t& operator=(num_t);
    mat2_t& operator+=(num_t);
    mat2_t& operator-=(num_t);
    mat2_t& operator*=(num_t);
    mat2_t& operator/=(num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr
mat2_t<num_t> operator+(num_t n, const mat2_t<num_t>& m);

template <typename num_t> constexpr
mat2_t<num_t> operator-(num_t n, const mat2_t<num_t>& m);

template <typename num_t> constexpr
mat2_t<num_t> operator*(num_t n, const mat2_t<num_t>& m);

/*-------------------------------------
    2x2 Matrix Specializations
-------------------------------------*/
typedef mat2_t<half>     mat2h;
typedef mat2_t<float>    mat2f;
typedef mat2_t<double>   mat2d;
typedef mat2_t<int>      mat2i;
typedef mat2_t<unsigned> mat2u;
typedef mat2_t<medp_t>   mat2x;

typedef mat2_t<float> mat2;

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/mat2_impl.h"

#endif /*LS_MATH_MAT2_H*/
