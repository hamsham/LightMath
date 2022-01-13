
#ifndef LS_MATH_BITSF_IMPL_H
#define LS_MATH_BITSF_IMPL_H

#include <immintrin.h>
#include <climits> // CHAR_BIT

#include "lightsky/setup/Api.h"
#include "lightsky/setup/Compiler.h" // GCC has finally surprised me, there's no rotate intrinsics

#ifdef LS_COMPILER_GNU
    #include <x86intrin.h>
#elif defined(LS_COMPILER_MSC)
    #include <intrin.h>
#endif

namespace ls
{



/*----------------------------------------------------------------------------
 * Bit-Count intrinsics
----------------------------------------------------------------------------*/
/*-------------------------------------
 * Popcnt: i32
-------------------------------------*/
inline LS_INLINE int32_t math::popcnt_i32(int32_t n) noexcept
{
    return (int32_t)_mm_popcnt_u32((uint32_t)n);
}



/*-------------------------------------
 * Popcnt: u32
-------------------------------------*/
inline LS_INLINE uint32_t math::popcnt_u32(uint32_t n) noexcept
{
    return (uint32_t)_mm_popcnt_u32(n);
}



/*-------------------------------------
 * Popcnt: i64
-------------------------------------*/
inline LS_INLINE int64_t math::popcnt_i64(int64_t n) noexcept
{
    return (int64_t)_mm_popcnt_u64((uint64_t)n);
}



/*-------------------------------------
 * Popcnt: u64
-------------------------------------*/
inline LS_INLINE uint64_t math::popcnt_u64(uint64_t n) noexcept
{
    return (uint64_t)_mm_popcnt_u64(n);
}



/*-------------------------------------
 * Count leading zeroes (i32).
-------------------------------------*/
inline LS_INLINE int32_t math::clz_i32(int32_t n) noexcept
{
    return (int32_t)_lzcnt_u32((uint32_t)n);
}



/*-------------------------------------
 * Count leading zeroes (u32).
-------------------------------------*/
inline LS_INLINE uint32_t math::clz_u32(uint32_t n) noexcept
{
    return _lzcnt_u32(n);
}



/*-------------------------------------
 * Count leading zeroes (i64).
-------------------------------------*/
inline LS_INLINE int64_t math::clz_i64(int64_t n) noexcept
{
    return (int64_t)_lzcnt_u64((uint64_t)n);
}



/*-------------------------------------
 * Count leading zeroes (u64).
-------------------------------------*/
inline LS_INLINE uint64_t math::clz_u64(uint64_t n) noexcept
{
    return _lzcnt_u64(n);
}



/*-------------------------------------
 * Count trailing zeroes (i32).
-------------------------------------*/
inline LS_INLINE int32_t math::ctz_i32(int32_t n) noexcept
{
    return (int64_t)_tzcnt_u32((uint32_t)n);
}



/*-------------------------------------
 * Count trailing zeroes (u32).
-------------------------------------*/
inline LS_INLINE uint32_t math::ctz_u32(uint32_t n) noexcept
{
    return _tzcnt_u32(n);
}



/*-------------------------------------
 * Count trailing zeroes (i64).
-------------------------------------*/
inline LS_INLINE int64_t math::ctz_i64(int64_t n) noexcept
{
    return (int64_t)_tzcnt_u64((uint64_t)n);
}



/*-------------------------------------
 * Count trailing zeroes (u64).
-------------------------------------*/
inline LS_INLINE uint64_t math::ctz_u64(uint64_t n) noexcept
{
    return _tzcnt_u64(n);
}




/*----------------------------------------------------------------------------
 * Rotation intrinsics
----------------------------------------------------------------------------*/
#ifndef LS_COMPILER_GNU
/*-------------------------------------
 * Left-rotate (i32)
-------------------------------------*/
inline LS_INLINE int32_t math::lrotate_i32(int32_t n, int32_t count) noexcept
{
    return (int32_t)_rotl((uint32_t)n, count);
}



/*-------------------------------------
 * Left-rotate (u32)
-------------------------------------*/
inline LS_INLINE uint32_t math::lrotate_u32(uint32_t n, uint32_t count) noexcept
{
    return _rotl(n, (int32_t)count);
}



/*-------------------------------------
 * Left-rotate (i64)
-------------------------------------*/
inline LS_INLINE int64_t math::lrotate_i64(int64_t n, int64_t count) noexcept
{
    return (int64_t)_rotl64((uint64_t)n, count);
}



/*-------------------------------------
 * Left-rotate (u64)
-------------------------------------*/
inline LS_INLINE uint64_t math::lrotate_u64(uint64_t n, uint64_t count) noexcept
{
    return _rotl64(n, (int64_t)count);
}



/*-------------------------------------
 * Right-rotate (i32).
-------------------------------------*/
inline LS_INLINE int32_t math::rrotate_i32(int32_t n, int32_t count) noexcept
{
    return (int32_t)_rotr((uint32_t)n, count);
}



/*-------------------------------------
 * Right-rotate (u32).
-------------------------------------*/
inline LS_INLINE uint32_t math::rrotate_u32(uint32_t n, uint32_t count) noexcept
{
    return _rotr(n, (int32_t)count);
}



/*-------------------------------------
 * Right-rotate (i64).
-------------------------------------*/
inline LS_INLINE int64_t math::rrotate_i64(int64_t n, int64_t count) noexcept
{
    return (int64_t)_rotr64((uint64_t)n, count);
}



/*-------------------------------------
 * Right-rotate (u64).
-------------------------------------*/
inline LS_INLINE uint64_t math::rrotate_u64(uint64_t n, uint64_t count) noexcept
{
    return _rotr64(n, (int64_t)count);
}



#else // LS_COMPILER_GCC



/*-------------------------------------
 * Left-rotate (i32)
-------------------------------------*/
inline LS_INLINE int32_t math::lrotate_i32(int32_t n, int32_t count) noexcept
{
    constexpr int32_t mask = CHAR_BIT*sizeof(int32_t) - 1;
    count &= mask;
    return (n << count) | (n >> ((-count) & mask));
}



/*-------------------------------------
 * Left-rotate (u32)
-------------------------------------*/
inline LS_INLINE uint32_t math::lrotate_u32(uint32_t n, uint32_t count) noexcept
{
    constexpr uint32_t mask = CHAR_BIT*sizeof(uint32_t) - 1u;
    count &= mask;
    return (n << count) | (n >> ((-count) & mask));
}



/*-------------------------------------
 * Left-rotate (i64)
-------------------------------------*/
inline LS_INLINE int64_t math::lrotate_i64(int64_t n, int64_t count) noexcept
{
    constexpr int64_t mask = CHAR_BIT*sizeof(int64_t) - 1ll;
    count &= mask;
    return (n << count) | (n >> ((-count) & mask));
}



/*-------------------------------------
 * Left-rotate (u64)
-------------------------------------*/
inline LS_INLINE uint64_t math::lrotate_u64(uint64_t n, uint64_t count) noexcept
{
    constexpr uint64_t mask = CHAR_BIT*sizeof(uint64_t) - 1ull;
    count &= mask;
    return (n << count) | (n >> ((-count) & mask));
}



/*-------------------------------------
 * Right-rotate (i32).
-------------------------------------*/
inline LS_INLINE int32_t math::rrotate_i32(int32_t n, int32_t count) noexcept
{
    constexpr int32_t mask = CHAR_BIT*sizeof(int32_t) - 1;
    count &= mask;
    return (n >> count) | (n << ((-count) & mask));
}



/*-------------------------------------
 * Right-rotate (u32).
-------------------------------------*/
inline LS_INLINE uint32_t math::rrotate_u32(uint32_t n, uint32_t count) noexcept
{
    constexpr uint32_t mask = CHAR_BIT*sizeof(uint32_t) - 1u;
    count &= mask;
    return (n >> count) | (n << ((-count) & mask));
}



/*-------------------------------------
 * Right-rotate (i64).
-------------------------------------*/
inline LS_INLINE int64_t math::rrotate_i64(int64_t n, int64_t count) noexcept
{
    constexpr int64_t mask = CHAR_BIT*sizeof(int64_t) - 1ll;
    count &= mask;
    return (n >> count) | (n << ((-count) & mask));
}



/*-------------------------------------
 * Right-rotate (u64).
-------------------------------------*/
inline LS_INLINE uint64_t math::rrotate_u64(uint64_t n, uint64_t count) noexcept
{
    constexpr uint64_t mask = CHAR_BIT*sizeof(uint64_t) - 1ull;
    count &= mask;
    return (n >> count) | (n << ((-count) & mask));
}
#endif



} // end ls namespace

#endif /* LS_MATH_BITSF_IMPL_H */
