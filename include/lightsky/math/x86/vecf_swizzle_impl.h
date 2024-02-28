/*
 * File:   vecf_swizzle_impl.h
 * Author: hammy
 * Created on February 27, 2024, at 2:04 PM
 */

#ifndef LS_MATH_VECF_SWIZZLE_IMPL_H
#define LS_MATH_VECF_SWIZZLE_IMPL_H

namespace ls
{
namespace math
{

/*-----------------------------------------------------------------------------
 * 1D permutations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
inline LS_INLINE float swizzle_x(const math::vec4_t<float>& v) noexcept { return _mm_cvtss_f32(v.simd); }

#if defined(LS_X86_AVX)
inline LS_INLINE float swizzle_y(const math::vec4_t<float>& v) noexcept { return _mm_cvtss_f32(_mm_permute_ps(v.simd, 0x01)); }
inline LS_INLINE float swizzle_z(const math::vec4_t<float>& v) noexcept { return _mm_cvtss_f32(_mm_permute_ps(v.simd, 0x02)); }
inline LS_INLINE float swizzle_w(const math::vec4_t<float>& v) noexcept { return _mm_cvtss_f32(_mm_permute_ps(v.simd, 0x03)); }

#else
inline LS_INLINE float swizzle_y(const math::vec4_t<float>& v) noexcept { return _mm_cvtss_f32(_mm_shuffle_ps(v.simd, _mm_undefined_ps(), 0x01)); }
inline LS_INLINE float swizzle_z(const math::vec4_t<float>& v) noexcept { return _mm_cvtss_f32(_mm_shuffle_ps(v.simd, _mm_undefined_ps(), 0x02)); }
inline LS_INLINE float swizzle_w(const math::vec4_t<float>& v) noexcept { return _mm_cvtss_f32(_mm_shuffle_ps(v.simd, _mm_undefined_ps(), 0x03)); }
#endif



/*-----------------------------------------------------------------------------
 * 4D permutations
-----------------------------------------------------------------------------*/
#if defined(LS_X86_AVX)
/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X---
inline LS_INLINE math::vec4_t<float> swizzle_xxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 3, 0))}; }

// Y---
inline LS_INLINE math::vec4_t<float> swizzle_yxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 3, 1))}; }

// Z---
inline LS_INLINE math::vec4_t<float> swizzle_zxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 3, 2))}; }

// W---
inline LS_INLINE math::vec4_t<float> swizzle_wxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(0, 3, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(1, 3, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(2, 3, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_permute_ps(v.simd, _MM_SHUFFLE(3, 3, 3, 3))}; }

#else
/*-------------------------------------
 * 4D Vectors
-------------------------------------*/
// X---
inline LS_INLINE math::vec4_t<float> swizzle_xxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 0, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 1, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 2, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 3, 0))}; }
inline LS_INLINE math::vec4_t<float> swizzle_xwww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 3, 0))}; }

// Y---
inline LS_INLINE math::vec4_t<float> swizzle_yxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 0, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 1, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_yzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 2, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 3, 1))}; }
inline LS_INLINE math::vec4_t<float> swizzle_ywww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 3, 1))}; }

// Z---
inline LS_INLINE math::vec4_t<float> swizzle_zxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 0, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 1, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 2, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 3, 2))}; }
inline LS_INLINE math::vec4_t<float> swizzle_zwww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 3, 2))}; }

// W---
inline LS_INLINE math::vec4_t<float> swizzle_wxxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wxww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 0, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wywx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wywy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wywz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wyww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 1, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wzww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 2, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwxw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 0, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwyw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 1, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwzw(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 2, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwwx(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 3, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwwy(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 3, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwwz(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 3, 3, 3))}; }
inline LS_INLINE math::vec4_t<float> swizzle_wwww(const math::vec4_t<float>& v) noexcept { return vec4_t<float>{_mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 3, 3))}; }

#endif

} // end math namespace
} // end ls namespace

#endif /* LS_MATH_VECF_SWIZZLE_IMPL_H */
