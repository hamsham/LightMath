
#include <iostream>

#include "lightsky/math/bits.h"


int main()
{
    const int32_t bitsi32 = 0x01010100;
    std::cout << "i32-bit Popcount for " << bitsi32 << ": " << ls::math::popcnt_i32(bitsi32) << std::endl;

    const uint32_t bitsu32 = 0x01010100u;
    std::cout << "u32-bit Popcount for " << bitsu32 << ": " << ls::math::popcnt_u32(bitsu32) << std::endl;

    const int64_t bitsi64 = 0x0101010101010100ll;
    std::cout << "i64-bit Popcount for " << bitsi64 << ": " << ls::math::popcnt_i64(bitsi64) << std::endl;

    const uint64_t bitsu64 = 0x0101010101010100ull;
    std::cout << "u64-bit Popcount for " << bitsu64 << ": " << ls::math::popcnt_u64(bitsu64) << std::endl;

    std::cout << "i32-bit CLZ for " << bitsi32 << ": " << ls::math::clz_i32(bitsi32) << std::endl;

    std::cout << "u32-bit CLZ for " << bitsu32 << ": " << ls::math::clz_u32(bitsu32) << std::endl;

    std::cout << "i64-bit CLZ for " << bitsi64 << ": " << ls::math::clz_i64(bitsi64) << std::endl;

    std::cout << "u64-bit CLZ for " << bitsu64 << ": " << ls::math::clz_u64(bitsu64) << std::endl;

    std::cout << "i32-bit CTZ for " << bitsi32 << ": " << ls::math::ctz_i32(bitsi32) << std::endl;

    std::cout << "u32-bit CTZ for " << bitsu32 << ": " << ls::math::ctz_u32(bitsu32) << std::endl;

    std::cout << "i64-bit CTZ for " << bitsi64 << ": " << ls::math::ctz_i64(bitsi64) << std::endl;

    std::cout << "u64-bit CTZ for " << bitsu64 << ": " << ls::math::ctz_u64(bitsu64) << std::endl;

    std::cout << "i32-bit left-rotate for " << bitsi32 << ": " << ls::math::lrotate_i32(bitsi32, 15) << std::endl;

    std::cout << "u32-bit left-rotate for " << bitsu32 << ": " << ls::math::lrotate_u32(bitsu32, 15) << std::endl;

    std::cout << "i64-bit left-rotate for " << bitsi64 << ": " << ls::math::lrotate_i64(bitsi64, 31) << std::endl;

    std::cout << "u64-bit left-rotate for " << bitsu64 << ": " << ls::math::lrotate_u64(bitsu64, 31) << std::endl;

    std::cout << "i32-bit right-rotate for " << bitsi32 << ": " << ls::math::rrotate_i32(bitsi32, 15) << std::endl;

    std::cout << "u32-bit right-rotate for " << bitsu32 << ": " << ls::math::rrotate_u32(bitsu32, 15) << std::endl;

    std::cout << "i64-bit right-rotate for " << bitsi64 << ": " << ls::math::rrotate_i64(bitsi64, 31) << std::endl;

    std::cout << "u64-bit right-rotate for " << bitsu64 << ": " << ls::math::rrotate_u64(bitsu64, 31) << std::endl;

    std::cout << "i32-bit rotate for " << bitsi32 << ": " << ls::math::lrotate_i32(ls::math::rrotate_i32(bitsi32, 15), 15) << std::endl;

    std::cout << "u32-bit rotate for " << bitsu32 << ": " << ls::math::lrotate_u32(ls::math::rrotate_u32(bitsu32, 15), 15) << std::endl;

    std::cout << "i64-bit rotate for " << bitsi64 << ": " << ls::math::lrotate_i64(ls::math::rrotate_i64(bitsi64, 31), 31) << std::endl;

    std::cout << "u64-bit rotate for " << bitsu64 << ": " << ls::math::lrotate_u64(ls::math::rrotate_u64(bitsu64, 31), 31) << std::endl;

    return 0;
}
