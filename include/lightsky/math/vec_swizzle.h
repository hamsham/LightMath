/*
 * File:   vec_swizzle.hpp
 * Author: hammy
 * Created on February 26, 2024, at 7:09 PM
 */

#ifndef LS_MATH_VEC_SWIZZLE_HPP
#define LS_MATH_VEC_SWIZZLE_HPP

#include "lightsky/math/vec2.h"
#include "lightsky/math/vec3.h"
#include "lightsky/math/vec4.h"

namespace ls
{
namespace math
{

/*-----------------------------------------------------------------------------
 * 1D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
template <typename num_t> constexpr num_t swizzle_x(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr num_t swizzle_y(const ls::math::vec2_t<num_t>& v) noexcept;

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
template <typename num_t> constexpr num_t swizzle_x(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr num_t swizzle_y(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr num_t swizzle_z(const ls::math::vec3_t<num_t>& v) noexcept;

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
template <typename num_t> constexpr num_t swizzle_x(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr num_t swizzle_y(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr num_t swizzle_z(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr num_t swizzle_w(const ls::math::vec4_t<num_t>& v) noexcept;



/*-----------------------------------------------------------------------------
 * 2D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
// X-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xy(const ls::math::vec2_t<num_t>& v) noexcept;

// Y-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yy(const ls::math::vec2_t<num_t>& v) noexcept;

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
// X-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xz(const ls::math::vec3_t<num_t>& v) noexcept;

// Y-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yz(const ls::math::vec3_t<num_t>& v) noexcept;

// Z-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_zx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_zy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_zz(const ls::math::vec3_t<num_t>& v) noexcept;

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_xw(const ls::math::vec4_t<num_t>& v) noexcept;

// Y-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_yw(const ls::math::vec4_t<num_t>& v) noexcept;

// Z-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_zx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_zy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_zz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_zw(const ls::math::vec4_t<num_t>& v) noexcept;

// W-
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_wx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_wy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_wz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec2_t<num_t> swizzle_ww(const ls::math::vec4_t<num_t>& v) noexcept;



/*-----------------------------------------------------------------------------
 * 3D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyy(const ls::math::vec2_t<num_t>& v) noexcept;

// Y--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyy(const ls::math::vec2_t<num_t>& v) noexcept;

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xzz(const ls::math::vec3_t<num_t>& v) noexcept;

// Y--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yzz(const ls::math::vec3_t<num_t>& v) noexcept;

// Z--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zzz(const ls::math::vec3_t<num_t>& v) noexcept;

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_xww(const ls::math::vec4_t<num_t>& v) noexcept;

// Y--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_ywx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_ywy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_ywz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_yww(const ls::math::vec4_t<num_t>& v) noexcept;

// Z--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_zww(const ls::math::vec4_t<num_t>& v) noexcept;

// W--
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_wwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec3_t<num_t> swizzle_www(const ls::math::vec4_t<num_t>& v) noexcept;



/*-----------------------------------------------------------------------------
 * 4D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyy(const ls::math::vec2_t<num_t>& v) noexcept;

// Y---
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxy(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyx(const ls::math::vec2_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyy(const ls::math::vec2_t<num_t>& v) noexcept;

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxzz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyzz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzzz(const ls::math::vec3_t<num_t>& v) noexcept;

// Y--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxzz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyzz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzzz(const ls::math::vec3_t<num_t>& v) noexcept;

// Z--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxzz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyzz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzxx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzxy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzxz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzyx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzyy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzyz(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzzx(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzzy(const ls::math::vec3_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzzz(const ls::math::vec3_t<num_t>& v) noexcept;

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xxww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xywx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xywy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xywz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xyww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xzww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_xwww(const ls::math::vec4_t<num_t>& v) noexcept;

// Y--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yxww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yywx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yywy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yywz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yyww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_yzww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_ywww(const ls::math::vec4_t<num_t>& v) noexcept;

// Z--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zxww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zywx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zywy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zywz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zyww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zzww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_zwww(const ls::math::vec4_t<num_t>& v) noexcept;

// W--
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wxww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wywx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wywy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wywz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wyww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wzww(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwxx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwxy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwxz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwxw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwyx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwyy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwyz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwyw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwzx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwzy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwzz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwzw(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwwx(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwwy(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwwz(const ls::math::vec4_t<num_t>& v) noexcept;
template <typename num_t> constexpr ls::math::vec4_t<num_t> swizzle_wwww(const ls::math::vec4_t<num_t>& v) noexcept;



} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/vec_swizzle_impl.h"

#if defined(LS_ARCH_X86)
    #include "lightsky/math/x86/vecf_swizzle_impl.h"
#endif

#endif /* LS_MATH_VEC_SWIZZLE_HPP */
