
#include <climits> // CHAR_BIT

#include "lightsky/setup/Api.h"
#include "lightsky/setup/Compiler.h"

#ifdef LS_COMPILER_MSC
    #include <intrin.h>
#endif

namespace ls
{



/*----------------------------------------------------------------------------
 * Bit-Count functions
----------------------------------------------------------------------------*/
/*-------------------------------------
 * Popcnt: i32
 *
 * https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
-------------------------------------*/
inline LS_INLINE int32_t math::popcnt_i32(int32_t n) noexcept
{
    #if !defined(LS_COMPILER_GNU)
        n = n - ((n >> 1) & 0x55555555);                       // reuse input as temporary
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);        // temp
        return ((n + (n >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
    #else
        return __builtin_popcount((unsigned)n);
    #endif
}



/*-------------------------------------
 * Popcnt: u32
-------------------------------------*/
inline LS_INLINE uint32_t math::popcnt_u32(uint32_t n) noexcept
{
    #if !defined(LS_COMPILER_GNU)
        n = n - ((n >> 1) & 0x55555555);                       // reuse input as temporary
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);        // temp
        return ((n + (n >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
    #else
        return __builtin_popcount(n);
    #endif
}



/*-------------------------------------
 * Popcnt: i64
-------------------------------------*/
inline LS_INLINE int64_t math::popcnt_i64(int64_t n) noexcept
{
    #if !defined(LS_COMPILER_GNU)
        n = n - ((n >> 1ll) & 0x5555555555555555ll);                                   // reuse input as temporary
        n = (n & 0x3333333333333333ll) + ((n >> 2ll) & 0x3333333333333333ll);          // temp
        return ((n + (n >> 4ll) & 0xF0F0F0F0F0F0F0Fll) * 0x101010101010101ll) >> 56ll; // count
    #else
        return __builtin_popcountll((unsigned long long)n);
    #endif
}



/*-------------------------------------
 * Popcnt: u64
-------------------------------------*/
inline LS_INLINE uint64_t math::popcnt_u64(uint64_t n) noexcept
{
    #if !defined(LS_COMPILER_GNU)
        n = n - ((n >> 1ull) & 0x5555555555555555ull);                                     // reuse input as temporary
        n = (n & 0x3333333333333333ull) + ((n >> 2ull) & 0x3333333333333333ull);           // temp
        return ((n + (n >> 4ull) & 0xF0F0F0F0F0F0F0Full) * 0x101010101010101ull) >> 56ull; // count
    #else
        return __builtin_popcountll(n);
    #endif
}



/*-------------------------------------
 * Count leading zeroes (i32).
-------------------------------------*/
inline LS_INLINE int32_t math::clz_i32(int32_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_clz((unsigned)n);
    #elif defined(LS_COMPILER_MSC)
        unsigned long ret;
        if (_BitScanReverse(&ret, (unsigned long)n))
        {
            return 31 - (int32_t)ret;
        }
        return 32;
    #else
        int32_t ret = 0;
        while (!(n & 0x80000000))
        {
            n <<= 1;
            ++ret;
        }
        return ret;
    #endif
}



/*-------------------------------------
 * Count leading zeroes (u32).
-------------------------------------*/
inline LS_INLINE uint32_t math::clz_u32(uint32_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_clz(n);
    #elif defined(LS_COMPILER_MSC)
        unsigned long ret;
        if (_BitScanReverse(&ret, (unsigned long)n))
        {
            return 31u - (uint32_t)ret;
        }
        return 32u;
    #else
        int32_t ret = 0;
        while (!(n & 0x80000000u))
        {
            n <<= 1;
            ++ret;
        }
        return ret;
    #endif
}



/*-------------------------------------
 * Count leading zeroes (i64).
-------------------------------------*/
inline LS_INLINE int64_t math::clz_i64(int64_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_clzll((unsigned long long)n);
    #elif defined(LS_COMPILER_MSC) && defined(LS_ARCH_X86) && LS_ARCH_X86 == 64
        unsigned long ret;
        if (_BitScanReverse64(&ret, (unsigned long)n))
        {
            return 31ll - (int64_t)ret;
        }
        return 32ll;
    #else
        int64_t ret = 0ll;
        while (!(n & 0x8000000000000000ll))
        {
            n <<= 1;
            ++ret;
        }
        return ret;
    #endif
}



/*-------------------------------------
 * Count leading zeroes (u64).
-------------------------------------*/
inline LS_INLINE uint64_t math::clz_u64(uint64_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_clzll(n);
    #elif defined(LS_COMPILER_MSC) && defined(LS_ARCH_X86) && LS_ARCH_X86 == 64
        unsigned long ret;
        if (_BitScanReverse64(&ret, n))
        {
            return 63ull - ret;
        }
        return 64ull;
    #else
        uint64_t ret = 0ull;
        while (!(n & 0x8000000000000000ull))
        {
            n <<= 1;
            ++ret;
        }
        return ret;
    #endif
}



/*-------------------------------------
 * Count trailing zeroes (i32).
-------------------------------------*/
inline LS_INLINE int32_t math::ctz_i32(int32_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_ctz((unsigned)n);
    #elif defined(LS_COMPILER_MSC)
        unsigned long ret;
        if (_BitScanForward(&ret, (unsigned long)n))
        {
            return (int32_t)ret;
        }
        return 32;
    #else
        int32_t ret = 0;
        while (!(n & 0x01))
        {
            n >>= 1;
            ++ret;
        }
        return ret;
    #endif
}



/*-------------------------------------
 * Count trailing zeroes (u32).
-------------------------------------*/
inline LS_INLINE uint32_t math::ctz_u32(uint32_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_ctz(n);
    #elif defined(LS_COMPILER_MSC)
        unsigned long ret;
        if (_BitScanForward(&ret, (unsigned long)n))
        {
            return (uint32_t)ret;
        }
        return 32u;
    #else
        uint32_t ret = 0u;
        while (!(n & 0x01u))
        {
            n >>= 1u;
            ++ret;
        }
        return ret;
    #endif
}



/*-------------------------------------
 * Count trailing zeroes (i64).
-------------------------------------*/
inline LS_INLINE int64_t math::ctz_i64(int64_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_ctzll(n);
    #elif defined(LS_COMPILER_MSC) && defined(LS_ARCH_X86) && LS_ARCH_X86 == 64
        unsigned long ret;
        if (_BitScanForward64(&ret, (unsigned long)n))
        {
            return (int64_t)ret;
        }
        return 64ull;
    #else
        int64_t ret = 0ll;
        while (!(n & 0x01ll))
        {
            n >>= 1ll;
            ++ret;
        }
        return ret;
    #endif
}



/*-------------------------------------
 * Count trailing zeroes (u64).
-------------------------------------*/
inline LS_INLINE uint64_t math::ctz_u64(uint64_t n) noexcept
{
    #if defined(LS_COMPILER_GNU)
        return __builtin_ctzll(n);
    #elif defined(LS_COMPILER_MSC)
        unsigned long ret;
        if (_BitScanForward(&ret, (unsigned long)n))
        {
            return ret;
        }
        return 64ull;
    #else
        uint64_t ret = 0ull;
        while (!(n & 0x01ull))
        {
            n >>= 1ull;
            ++ret;
        }
        return ret;
    #endif
}



/*----------------------------------------------------------------------------
 * Rotation functions
----------------------------------------------------------------------------*/
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



} // end ls namespace
