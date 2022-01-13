
#ifndef LS_MATH_BITS_H
#define LS_MATH_BITS_H

#include <cstdint> // fixed-width types

#include "lightsky/setup/Arch.h"
#include "lightsky/setup/Compiler.h"



namespace ls
{
namespace math
{



/**
 * Count the number of set bits in an integer.
 *
 * @param n
 * A 32-bit signed integer.
 *
 * @return The signed number of bits in n.
 */
int32_t popcnt_i32(int32_t n) noexcept;



/**
 * Count the number of set bits in an integer.
 *
 * @param n
 * A 32-bit unsigned integer.
 *
 * @return The unsigned number of bits in n.
 */
uint32_t popcnt_u32(uint32_t n) noexcept;



/**
 * Count the number of set bits in an integer.
 *
 * @param n
 * A 64-bit signed integer.
 *
 * @return The signed number of bits in n.
 */
int64_t popcnt_i64(int64_t n) noexcept;



/**
 * Count the number of set bits in an integer.
 *
 * @param n
 * A 64-bit unsigned integer.
 *
 * @return The unsigned number of bits in n.
 */
uint64_t popcnt_u64(uint64_t n) noexcept;



/**
 * @brief Count the number of leading zeroes in a set of bits.
 *
 * @param n
 * A 32-bit signed integer.
 *
 * @return The number of leading zeroes in n.
 */
int32_t clz_i32(int32_t n) noexcept;



/**
 * @brief Count the number of leading zeroes in a set of bits.
 *
 * @param n
 * A 32-bit unsigned integer.
 *
 * @return The number of leading zeroes in n.
 */
uint32_t clz_u32(uint32_t n) noexcept;



/**
 * @brief Count the number of leading zeroes in a set of bits.
 *
 * @param n
 * A 64-bit signed integer.
 *
 * @return The number of leading zeroes in n.
 */
int64_t clz_i64(int64_t n) noexcept;



/**
 * @brief Count the number of leading zeroes in a set of bits.
 *
 * @param n
 * A 64-bit unsigned integer.
 *
 * @return The number of leading zeroes in n.
 */
uint64_t clz_u64(uint64_t n) noexcept;



/**
 * @brief Count the number of trailing zeroes in a set of bits.
 *
 * @param n
 * A 32-bit signed integer.
 *
 * @return The number of trailing zeroes in n.
 */
int32_t ctz_i32(int32_t n) noexcept;



/**
 * @brief Count the number of trailing zeroes in a set of bits.
 *
 * @param n
 * A 32-bit unsigned integer.
 *
 * @return The number of trailing zeroes in n.
 */
uint32_t ctz_u32(uint32_t n) noexcept;



/**
 * @brief Count the number of trailing zeroes in a set of bits.
 *
 * @param n
 * A 64-bit signed integer.
 *
 * @return The number of trailing zeroes in n.
 */
int64_t ctz_i64(int64_t n) noexcept;



/**
 * @brief Count the number of trailing zeroes in a set of bits.
 *
 * @param n
 * A 64-bit unsigned integer.
 *
 * @return The number of trailing zeroes in n.
 */
uint64_t ctz_u64(uint64_t n) noexcept;



/**
 * @brief Rotate the bits of an integer to the left.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the left.
 */
int32_t lrotate_i32(int32_t n, int32_t count) noexcept;



/**
 * @brief Rotate the bits of an integer to the left.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the left.
 */
uint32_t lrotate_u32(uint32_t n, uint32_t count) noexcept;



/**
 * @brief Rotate the bits of an integer to the left.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the left.
 */
int64_t lrotate_i64(int64_t n, int64_t count) noexcept;



/**
 * @brief Rotate the bits of an integer to the left.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the left.
 */
uint64_t lrotate_u64(uint64_t n, uint64_t count) noexcept;



/**
 * @brief Rotate the bits of an integer to the right.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the right.
 */
int32_t rrotate_i32(int32_t n, int32_t count) noexcept;



/**
 * @brief Rotate the bits of an integer to the right.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the right.
 */
uint32_t rrotate_u32(uint32_t n, uint32_t count) noexcept;



/**
 * @brief Rotate the bits of an integer to the right.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the right.
 */
int64_t rrotate_i64(int64_t n, int64_t count) noexcept;



/**
 * @brief Rotate the bits of an integer to the right.
 *
 * @param n
 * The number whose bits will be rotated.
 *
 * @param count
 * The amount of bits to shift/rotate.
 *
 * @return The input, n, with its internal bit positions rotated to the right.
 */
uint64_t rrotate_u64(uint64_t n, uint64_t count) noexcept;



} // end math namespace
} // end ls namespace



#if defined(LS_X86_SSE4_2) && LS_ARCH_X86 == 64 && !defined(LS_COMPILER_MSC)
    #include "lightsky/math/x86/bits_impl.h"
#else
    #include "lightsky/math/generic/bits_impl.h"
#endif



#endif /* LS_MATH_BITS_H */
