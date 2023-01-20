/*
 * File:   lsmath_test_custom_float.cpp
 * Author: hammy
 *
 * Created on Jan 13, 2023 at 8:34 PM
 */

#include <cassert>
#include <iostream>

#include "lightsky/math/bits.h"
#include "lightsky/math/half.h"
#include "lightsky/math/scalar_utils.h"



template <typename data_t, unsigned ExponentBits, unsigned MantissaBits, unsigned Bias>
class CustomFloat
{
  public:
    enum SL_RGB9e5Limits : uint64_t
    {
        SIGN_BIT             = ls::setup::IsSigned<data_t>::value ? (1ull << (ExponentBits+MantissaBits)) : 0,
        EXPONENT_BITS        = ExponentBits,
        MANTISSA_BITS        = MantissaBits,
        EXP_BIAS             = Bias,
        MAX_VALID_BIASED_EXP = (uint64_t)((1 << ExponentBits)-1)
    };

    static constexpr float MAX_EXP_VALUE      = (float)(1 << (MAX_VALID_BIASED_EXP - EXP_BIAS));
    static constexpr float MANTISSA_HIGH_BIT  = (float)(1 << MANTISSA_BITS);
    static constexpr float MANTISSA_MASK      = (float)(MANTISSA_HIGH_BIT - 1);
    static constexpr float MAX_FLOAT_VALUE    = MANTISSA_MASK / MANTISSA_HIGH_BIT * MAX_EXP_VALUE;

    struct IEEE754Bits
    {
        uint32_t mantissa : 23;
        uint32_t biasedExponent : 8;
        uint32_t negative : 1;
    };

    union Float754
    {
        uint32_t raw;
        float value;
        IEEE754Bits field;
    };

    struct CustomFloatBits
    {
        uint64_t value : MANTISSA_BITS;
        uint64_t biasedExponent : EXPONENT_BITS;
    };

    union CustomFloatInternal
    {
        uint64_t raw;
        CustomFloatBits field;
    };

    static inline float clamp_value(float x) noexcept
    {
        return ls::math::clamp(x, 0.f, MAX_FLOAT_VALUE);
    }

    // FloorLog2 is not correct for the denorm and zero values, but we are
    // going to do a max of this value with the minimum rgb9e5 exponent that
    // will hide these problem cases.
    static inline uint64_t floor_log2(float x) noexcept
    {
        Float754 f;
        f.value = x;

        // 127 is the bias of the input float
        return (f.field.biasedExponent - 127ull);
    }

    static constexpr CustomFloatInternal set_sign(const CustomFloatInternal& bits, bool sign) noexcept
    {
        return CustomFloatInternal{bits.raw | ((SIGN_BIT != 0 && sign) ? SIGN_BIT : 0)};
    }

    static data_t to_custom(float f) noexcept
    {
        bool amSigned = f < 0.f;
        f = std::abs(f);
        const float c = clamp_value(f);
        int64_t exp_shared = ls::math::max<int64_t>(-EXP_BIAS-1, (int64_t)floor_log2(f));

        exp_shared = exp_shared + 1ll + (int64_t)EXP_BIAS;

        assert(exp_shared <= (int64_t)MAX_VALID_BIASED_EXP);
        assert(exp_shared >= 0ll);

        // This pow function could be replaced by a table.
        float denom = std::exp2((float)(exp_shared - (int64_t)EXP_BIAS - (int64_t)MANTISSA_BITS));

        float rDenom = 1.f / denom;
        const int64_t maxm = (int64_t)std::floor(ls::math::fmadd(c, rDenom, 0.5f));
        if (maxm == (int64_t)(MANTISSA_MASK + 1))
        {
            //denom *= 2.f;
            denom += denom;
            exp_shared += 1ll;
            assert(exp_shared <= (int64_t)MAX_VALID_BIASED_EXP);
        }
        else
        {
            assert(maxm <= (int64_t)MANTISSA_MASK);
        }

        rDenom = 1.f / denom;
        const int64_t fm = (int64_t)std::floor(ls::math::fmadd(f, rDenom, 0.5f));

        assert(fm <= (int64_t)MANTISSA_MASK);

        CustomFloatInternal retval;
        retval.field.value = (int64_t)fm;
        retval.field.biasedExponent = (int64_t)exp_shared;
        retval = set_sign(retval, amSigned);

        return (data_t)retval.raw;
    }

    static inline float to_float(data_t bits) noexcept
    {
        CustomFloatInternal v;
        v.raw = (uint64_t)bits;
        const float exponent = (float)((int64_t)v.field.biasedExponent - (int64_t)EXP_BIAS - (int64_t)MANTISSA_BITS);
        const float scale = std::exp2(exponent);
        float value = (float)v.field.value * scale;

        if (SIGN_BIT != 0 && (v.raw & SIGN_BIT))
        {
            value = -value;
        }

        return value;
    }
};



template <typename data_t, unsigned ExponentBits, unsigned MantissaBits, unsigned Bias>
void run_test(float inVal)
{
    typedef CustomFloat<data_t, ExponentBits, MantissaBits, Bias> CustomFloat16;
    float val = inVal;

    data_t bits = CustomFloat16::to_custom(val);
    float inverse = CustomFloat16::to_float(bits);

    std::cout << "Value:   " << val << std::endl;
    std::cout << "Bits:    " << bits << std::endl;
    std::cout << "Inverse: " << inverse << std::endl;
    std::cout << "Half:    " << (float)((ls::math::half)val) << std::endl;
    std::cout << std::endl;
}



int main()
{
    // 16-bit floats
    run_test<uint16_t, 5, 10, 15>(-42.77);
    run_test<int16_t, 5, 10, 15>(-42.77);

    // Like GL_R9E5
    run_test<uint16_t, 5, 9, 15>(-42.77);
    run_test<int16_t, 5, 9, 15>(-42.77);

    // Like GL_R11F_G11F_B10F
    run_test<uint16_t, 5, 5, 15>(-42.77);
    run_test<uint16_t, 5, 6, 15>(-42.77);

    return 0;
}