/*
 * File:   vec_swizzle_impl.h
 * Author: hammy
 * Created on February 27, 2024, at 2:04 PM
 */

#ifndef LS_MATH_VEC_SWIZZLE_IMPL_H
#define LS_MATH_VEC_SWIZZLE_IMPL_H

namespace ls
{

/*-----------------------------------------------------------------------------
 * 1D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
template <typename num_t> constexpr num_t math::swizzle_x(const math::vec2_t<num_t>& v) noexcept { return v[0]; }
template <typename num_t> constexpr num_t math::swizzle_y(const math::vec2_t<num_t>& v) noexcept { return v[1]; }

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
template <typename num_t> constexpr num_t math::swizzle_x(const math::vec3_t<num_t>& v) noexcept { return v[0]; }
template <typename num_t> constexpr num_t math::swizzle_y(const math::vec3_t<num_t>& v) noexcept { return v[1]; }
template <typename num_t> constexpr num_t math::swizzle_z(const math::vec3_t<num_t>& v) noexcept { return v[2]; }

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
template <typename num_t> constexpr num_t math::swizzle_x(const math::vec4_t<num_t>& v) noexcept { return v[0]; }
template <typename num_t> constexpr num_t math::swizzle_y(const math::vec4_t<num_t>& v) noexcept { return v[1]; }
template <typename num_t> constexpr num_t math::swizzle_z(const math::vec4_t<num_t>& v) noexcept { return v[2]; }
template <typename num_t> constexpr num_t math::swizzle_w(const math::vec4_t<num_t>& v) noexcept { return v[3]; }



/*-----------------------------------------------------------------------------
 * 2D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
// X-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xx(const math::vec2_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xy(const math::vec2_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[1]}; }

// Y-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yx(const math::vec2_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yy(const math::vec2_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[1]}; }

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
// X-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xx(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xy(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[1]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xz(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[2]}; }

// Y-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yx(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yy(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[1]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yz(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[2]}; }

// Z-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_zx(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[2], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_zy(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[2], v[1]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_zz(const math::vec3_t<num_t>& v) noexcept { return vec2_t<num_t>{v[2], v[2]}; }

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xx(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xy(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[1]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xz(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[2]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_xw(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[0], v[3]}; }

// Y-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yx(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yy(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[1]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yz(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[2]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_yw(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[1], v[3]}; }

// Z-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_zx(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[2], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_zy(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[2], v[1]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_zz(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[2], v[2]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_zw(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[2], v[3]}; }

// W-
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_wx(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[3], v[0]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_wy(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[3], v[1]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_wz(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[3], v[2]}; }
template <typename num_t> constexpr math::vec2_t<num_t> math::swizzle_ww(const math::vec4_t<num_t>& v) noexcept { return vec2_t<num_t>{v[3], v[3]}; }



/*-----------------------------------------------------------------------------
 * 3D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxx(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxy(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyx(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyy(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[1]}; }

// Y--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxx(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxy(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyx(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyy(const math::vec2_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[1]}; }

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xzx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xzy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xzz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[2], v[2]}; }

// Y--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yzx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yzy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yzz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[2], v[2]}; }

// Z--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zxx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zxy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zxz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zyx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zyy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zyz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zzx(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zzy(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zzz(const math::vec3_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[2], v[2]}; }

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xxw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[0], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xyw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[1], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xzx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xzy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xzz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xzw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[2], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xwx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[3], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xwy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[3], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xwz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[3], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_xww(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[0], v[3], v[3]}; }

// Y--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yxw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[0], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yyw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[1], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yzx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yzy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yzz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yzw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[2], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_ywx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[3], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_ywy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[3], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_ywz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[3], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_yww(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[1], v[3], v[3]}; }

// Z--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zxx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zxy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zxz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zxw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[0], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zyx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zyy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zyz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zyw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[1], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zzx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zzy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zzz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[2], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zzw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[2], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zwx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[3], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zwy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[3], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zwz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[3], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_zww(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[2], v[3], v[3]}; }

// W--
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wxx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[0], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wxy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[0], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wxz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[0], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wxw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[0], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wyx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[1], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wyy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[1], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wyz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[1], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wyw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[1], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wzx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[2], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wzy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[2], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wzz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[2], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wzw(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[2], v[3]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wwx(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[3], v[0]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wwy(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[3], v[1]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_wwz(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[3], v[2]}; }
template <typename num_t> constexpr math::vec3_t<num_t> math::swizzle_www(const math::vec4_t<num_t>& v) noexcept { return vec3_t<num_t>{v[3], v[3], v[3]}; }



/*-----------------------------------------------------------------------------
 * 4D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 2D Vectors
-------------------------------------*/
// X---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[1]}; }

// Y---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyx(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyy(const math::vec2_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[1]}; }

/*-------------------------------------
 * 3D Vectors
-------------------------------------*/
// X---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[2], v[2]}; }

// Y---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[2], v[2]}; }

// Z---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzxx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzxy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzxz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzyx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzyy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzyz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzzx(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzzy(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzzz(const math::vec3_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[2], v[2]}; }

/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xxww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[0], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xywx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xywy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xywz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xyww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[1], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xzww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[2], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_xwww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[0], v[3], v[3], v[3]}; }

// Y---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yxww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[0], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yywx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yywy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yywz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yyww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[1], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_yzww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[2], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_ywww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[1], v[3], v[3], v[3]}; }

// Z---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zxww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[0], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zywx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zywy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zywz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zyww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[1], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zzww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[2], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_zwww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[2], v[3], v[3], v[3]}; }

// W---
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wxww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[0], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wywx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wywy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wywz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wyww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[1], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wzww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[2], v[3], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwxx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[0], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwxy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[0], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwxz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[0], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwxw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[0], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwyx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[1], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwyy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[1], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwyz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[1], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwyw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[1], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwzx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[2], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwzy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[2], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwzz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[2], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwzw(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[2], v[3]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwwx(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[3], v[0]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwwy(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[3], v[1]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwwz(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[3], v[2]}; }
template <typename num_t> constexpr math::vec4_t<num_t> math::swizzle_wwww(const math::vec4_t<num_t>& v) noexcept { return vec4_t<num_t>{v[3], v[3], v[3], v[3]}; }

} // end ls namespace

#endif /* LS_MATH_VEC_SWIZZLE_IMPL_H */
