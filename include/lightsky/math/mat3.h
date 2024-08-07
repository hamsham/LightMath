
#ifndef LS_MATH_MAT3_H
#define LS_MATH_MAT3_H

#include "lightsky/math/fixed.h"
#include "lightsky/math/vec3.h"

namespace ls {
namespace math {

struct half;

template<typename num_t>
struct mat4_t;



/**
 *  @brief 3D Matrix Structure
 *  recommended for use with non-integral types
 *
 *  @note
 *  Matrix is Row-Major
 *  Orientation is as follows:
 *      0[0-2] = XX  XY  XZ
 *      1[0-2] = YX  YY  YZ
 *      2[0-2] = ZX  ZY  ZZ
 */
template <typename num_t>
struct alignas(sizeof(num_t)) mat3_t
{
    // data
    vec3_t<num_t> m[3];

    ~mat3_t() = default;

    constexpr mat3_t(
        num_t inXX, num_t inXY, num_t inXZ,
        num_t inYX, num_t inYY, num_t inYZ,
        num_t inZX, num_t inZY, num_t inZZ
    );

    // Delegated Constructors
    constexpr mat3_t();
    constexpr mat3_t(num_t);
    constexpr mat3_t(const mat3_t<num_t>&);
    constexpr mat3_t(mat3_t<num_t>&&);
    constexpr mat3_t(const mat4_t<num_t>&); // defined in the mat4 header
    constexpr mat3_t(
        const vec3_t<num_t>& x,
        const vec3_t<num_t>& y,
        const vec3_t<num_t>& z
    );

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator mat3_t<other_t>() const;

    //Subscripting operators
    template <typename index_t>
    constexpr const vec3_t<num_t>& operator[](index_t i) const;

    template <typename index_t>
    inline vec3_t<num_t>& operator[](index_t i);

    //matrix-matrix operators
    mat3_t& operator++(); //prefix operators
    mat3_t& operator--();
    mat3_t operator++(int); //postfix operators
    mat3_t operator--(int);
    constexpr mat3_t operator+(const mat3_t<num_t>& input) const;
    constexpr mat3_t operator-(const mat3_t<num_t>& input) const;
    constexpr mat3_t operator-() const;
    constexpr mat3_t operator*(const mat3_t<num_t>& input) const;
    mat3_t& operator=(const mat3_t<num_t>& input);
    mat3_t& operator=(mat3_t<num_t>&& input);
    mat3_t& operator+=(const mat3_t<num_t>& input);
    mat3_t& operator-=(const mat3_t<num_t>& input);
    mat3_t& operator*=(const mat3_t<num_t>& input);
    constexpr bool operator==(const mat3_t<num_t>& input) const;
    constexpr bool operator!=(const mat3_t<num_t>& input) const;

    //matrix-vector operators
    constexpr mat3_t operator+(const vec3_t<num_t>&) const;
    constexpr mat3_t operator-(const vec3_t<num_t>&) const;
    constexpr vec3_t<num_t> operator*(const vec3_t<num_t>&) const;
    mat3_t& operator=(const vec3_t<num_t>&);
    mat3_t& operator+=(const vec3_t<num_t>&);
    mat3_t& operator-=(const vec3_t<num_t>&);

    //matrix-scalar operators
    constexpr mat3_t operator+(num_t) const;
    constexpr mat3_t operator-(num_t) const;
    constexpr mat3_t operator*(num_t) const;
    constexpr mat3_t operator/(num_t) const;
    mat3_t& operator=(num_t);
    mat3_t& operator+=(num_t);
    mat3_t& operator-=(num_t);
    mat3_t& operator*=(num_t);
    mat3_t& operator/=(num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr
mat3_t<num_t> operator+(num_t n, const mat3_t<num_t>& m);

template <typename num_t> constexpr
mat3_t<num_t> operator-(num_t n, const mat3_t<num_t>& m);

template <typename num_t> constexpr
mat3_t<num_t> operator*(num_t n, const mat3_t<num_t>& m);

/*-------------------------------------
    3x3 Matrix Specializations
-------------------------------------*/
typedef mat3_t<half>     mat3h;
typedef mat3_t<float>    mat3f;
typedef mat3_t<double>   mat3d;
typedef mat3_t<int>      mat3i;
typedef mat3_t<unsigned> mat3u;
typedef mat3_t<medp_t>   mat3x;

typedef mat3_t<float> mat3;

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/mat3_impl.h"

#endif /*LS_MATH_MAT3_H*/
