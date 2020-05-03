
#ifndef LS_MATH_MAT4_H
#define LS_MATH_MAT4_H

#include "lightsky/setup/Api.h"
#include "lightsky/setup/Arch.h"

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"
#include "lightsky/math/vec4.h"
#include "lightsky/math/mat3.h"

namespace ls {
namespace math {



/**----------------------------------------------------------------------------
 *  @brief 4D Matrix Structure
 *  recommended for use with non-integral types
 *
 *  @note
 *  Matrix is Row-Major
 *  Orientation is as follows:
 *      0[0-3] = XX  XY  XZ  XW
 *      1[0-3] = YX  YY  YZ  YW
 *      2[0-3] = ZX  ZY  ZZ  ZW
 *      3[0-3] = WX  WY  WZ  WW
-----------------------------------------------------------------------------*/
template <typename num_t>
struct alignas(sizeof(vec4_t<num_t>)) mat4_t {
    // data
    vec4_t<num_t> m[4];

    // Main Constructor
    constexpr mat4_t(
        num_t inXX, num_t inXY, num_t inXZ, num_t inXW,
        num_t inYX, num_t inYY, num_t inYZ, num_t inYW,
        num_t inZX, num_t inZY, num_t inZZ, num_t inZW,
        num_t inWX, num_t inWY, num_t inWZ, num_t inWW
        );

    // Delegated constructors
    constexpr mat4_t() = default;
    constexpr mat4_t(num_t);
    constexpr mat4_t(const mat3_t<num_t>&);
    constexpr mat4_t(const mat4_t<num_t>&);
    constexpr mat4_t(mat3_t<num_t>&&);
    constexpr mat4_t(mat4_t<num_t>&&);
    constexpr mat4_t(
        const vec4_t<num_t>& x,
        const vec4_t<num_t>& y,
        const vec4_t<num_t>& z,
        const vec4_t<num_t>& w
    );

    ~mat4_t() = default;

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator mat4_t<other_t>() const;

    // Subscripting Operators
    template <typename index_t>
    constexpr const vec4_t<num_t>& operator[](index_t) const;

    template <typename index_t>
    inline vec4_t<num_t>& operator[](index_t);

    //matrix-matrix operators
    mat4_t& operator++(); //prefix operators
    mat4_t& operator--();
    mat4_t operator++(int); //postfix operators
    mat4_t operator--(int);
    constexpr mat4_t operator+(const mat4_t<num_t>&) const;
    constexpr mat4_t operator-(const mat4_t<num_t>&) const;
    constexpr mat4_t operator-() const;
    inline mat4_t operator*(const mat4_t<num_t>&) const;
    mat4_t& operator=(const mat4_t<num_t>&);
    mat4_t& operator=(mat4_t<num_t>&&);
    mat4_t& operator+=(const mat4_t<num_t>&);
    mat4_t& operator-=(const mat4_t<num_t>&);
    mat4_t& operator*=(const mat4_t<num_t>&);
    constexpr bool operator==(const mat4_t<num_t>&) const;
    constexpr bool operator!=(const mat4_t<num_t>&) const;

    //matrix-vector operators
    constexpr mat4_t operator+(const vec4_t<num_t>&) const;
    constexpr mat4_t operator-(const vec4_t<num_t>&) const;
    inline vec4_t<num_t> operator*(const vec4_t<num_t>&) const;
    mat4_t& operator=(const vec4_t<num_t>&);
    mat4_t& operator+=(const vec4_t<num_t>&);
    mat4_t& operator-=(const vec4_t<num_t>&);

    //matrix-scalar operators
    constexpr mat4_t operator+(num_t) const;
    constexpr mat4_t operator-(num_t) const;
    constexpr mat4_t operator*(num_t) const;
    constexpr mat4_t operator/(num_t) const;
    mat4_t& operator=(num_t);
    mat4_t& operator+=(num_t);
    mat4_t& operator-=(num_t);
    mat4_t& operator*=(num_t);
    mat4_t& operator/=(num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr
mat4_t<num_t> operator+(num_t n, const mat4_t<num_t>& m);

template <typename num_t> constexpr
mat4_t<num_t> operator-(num_t n, const mat4_t<num_t>& m);

template <typename num_t> constexpr
mat4_t<num_t> operator*(num_t n, const mat4_t<num_t>& m);

/*-------------------------------------
    4x4 Matrix Specializations
-------------------------------------*/
/*
LS_DECLARE_STRUCT_TYPE(mat4f, mat4_t, float);
LS_DECLARE_STRUCT_TYPE(mat4d, mat4_t, double);
LS_DECLARE_STRUCT_TYPE(mat4i, mat4_t, int);
LS_DECLARE_STRUCT_TYPE(mat4u, mat4_t, unsigned);
LS_DECLARE_STRUCT_TYPE(mat4x, mat4_t, medp_t);
LS_DECLARE_STRUCT_TYPE(mat4, mat4_t, LS_FLOAT);
*/
struct half;

typedef mat4_t<half>     mat4h;
typedef mat4_t<float>    mat4f;
typedef mat4_t<double>   mat4d;
typedef mat4_t<int>      mat4i;
typedef mat4_t<unsigned> mat4u;
typedef mat4_t<medp_t>   mat4x;
typedef mat4_t<LS_FLOAT> mat4;

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/mat4_impl.h"

#ifdef LS_ARCH_X86
    #include "lightsky/math/x86/mat4f_impl.h"
#elif defined(LS_ARCH_ARM)
    #include "lightsky/math/arm/mat4f_impl.h"
#endif

#endif /*LS_MATH_MAT4_H*/
