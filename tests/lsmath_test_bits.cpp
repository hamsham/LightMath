
#include <iostream>

#include "lightsky/math/bits.h"

namespace math = ls::math;


int main()
{
    const int32_t bitsi32 = 0x01010100;
    std::cout << "i32-bit Popcount for " << bitsi32 << ": " << math::popcnt_i32(bitsi32) << std::endl;

    const uint32_t bitsu32 = 0x01010100u;
    std::cout << "u32-bit Popcount for " << bitsu32 << ": " << math::popcnt_u32(bitsu32) << std::endl;

    const int64_t bitsi64 = 0x0101010101010100ll;
    std::cout << "i64-bit Popcount for " << bitsi64 << ": " << math::popcnt_i64(bitsi64) << std::endl;

    const uint64_t bitsu64 = 0x0101010101010100ull;
    std::cout << "u64-bit Popcount for " << bitsu64 << ": " << math::popcnt_u64(bitsu64) << std::endl;

    std::cout << "i32-bit CLZ for " << bitsi32 << ": " << math::clz_i32(bitsi32) << std::endl;

    std::cout << "u32-bit CLZ for " << bitsu32 << ": " << math::clz_u32(bitsu32) << std::endl;

    std::cout << "i64-bit CLZ for " << bitsi64 << ": " << math::clz_i64(bitsi64) << std::endl;

    std::cout << "u64-bit CLZ for " << bitsu64 << ": " << math::clz_u64(bitsu64) << std::endl;

    std::cout << "i32-bit CTZ for " << bitsi32 << ": " << math::ctz_i32(bitsi32) << std::endl;

    std::cout << "u32-bit CTZ for " << bitsu32 << ": " << math::ctz_u32(bitsu32) << std::endl;

    std::cout << "i64-bit CTZ for " << bitsi64 << ": " << math::ctz_i64(bitsi64) << std::endl;

    std::cout << "u64-bit CTZ for " << bitsu64 << ": " << math::ctz_u64(bitsu64) << std::endl;

    std::cout << "i32-bit left-rotate for " << bitsi32 << ": " << math::lrotate_i32(bitsi32, 15) << std::endl;

    std::cout << "u32-bit left-rotate for " << bitsu32 << ": " << math::lrotate_u32(bitsu32, 15) << std::endl;

    std::cout << "i64-bit left-rotate for " << bitsi64 << ": " << math::lrotate_i64(bitsi64, 31) << std::endl;

    std::cout << "u64-bit left-rotate for " << bitsu64 << ": " << math::lrotate_u64(bitsu64, 31) << std::endl;

    std::cout << "i32-bit right-rotate for " << bitsi32 << ": " << math::rrotate_i32(bitsi32, 15) << std::endl;

    std::cout << "u32-bit right-rotate for " << bitsu32 << ": " << math::rrotate_u32(bitsu32, 15) << std::endl;

    std::cout << "i64-bit right-rotate for " << bitsi64 << ": " << math::rrotate_i64(bitsi64, 31) << std::endl;

    std::cout << "u64-bit right-rotate for " << bitsu64 << ": " << math::rrotate_u64(bitsu64, 31) << std::endl;

    std::cout << "i32-bit rotate for " << bitsi32 << ": " << math::lrotate_i32(math::rrotate_i32(bitsi32, 15), 15) << std::endl;

    std::cout << "u32-bit rotate for " << bitsu32 << ": " << math::lrotate_u32(math::rrotate_u32(bitsu32, 15), 15) << std::endl;

    std::cout << "i64-bit rotate for " << bitsi64 << ": " << math::lrotate_i64(math::rrotate_i64(bitsi64, 31), 31) << std::endl;

    std::cout << "u64-bit rotate for " << bitsu64 << ": " << math::lrotate_u64(math::rrotate_u64(bitsu64, 31), 31) << std::endl;

    const uint32_t mask = 0x05;

    {
        const uint32_t mask0 = math::popcnt_u32(mask & 0x00);
        const uint32_t mask1 = math::popcnt_u32(mask & 0x01);
        const uint32_t mask2 = math::popcnt_u32(mask & 0x03);
        const uint32_t mask3 = math::popcnt_u32(mask & 0x07);
        std::cout
            << "Selection Mask to indices:"
            << "\nMask:    " << mask
            << "\nIndex 0: " << mask0
            << "\nIndex 1: " << mask1
            << "\nIndex 2: " << mask2
            << "\nIndex 3: " << mask3
            << std::endl;
    }

    {
        const uint32_t mask0 = (mask & 0x00);
        const uint32_t mask1 = (mask & 0x01);
        const uint32_t mask2 = ((mask & 0x02) >> 1) + (mask & 0x01);
        const uint32_t mask3 = ((mask & 0x04) >> 2) + ((mask & 0x02) >> 1) + (mask & 0x01);
        std::cout
            << "Selection Mask to indices:"
            << "\nMask:    " << mask
            << "\nIndex 0: " << mask0
            << "\nIndex 1: " << mask1
            << "\nIndex 2: " << mask2
            << "\nIndex 3: " << mask3
            << std::endl;
    }

    return 0;
}
