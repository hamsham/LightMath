
#include <iostream>

#include "lightsky/math/fixed.h"

#define FixedType ls::math::long_medp_t



inline std::ostream& operator << (std::ostream& os, const FixedType& fx) noexcept
{
    const FixedType::base_type n = fx.number >> FixedType::fraction_digits;
    const FixedType::base_type d = fx.number & FixedType::fraction_mask;
    return os << n << '.' << d;
}



int main()
{
    float f = 1.f;
    FixedType fx{f};

    std::cout << f << " == " << fx << '\n' << std::endl;

    f *= 42.f;
    fx *= ls::math::fixed_cast<FixedType>((FixedType::base_type)42);
    std::cout << f << " == " << ls::math::float_cast<float>(fx) << " && " << fx << '\n' << std::endl;

    f *= 123.456789f;
    fx *= FixedType(123.456789f);
    std::cout << f << " == " << ls::math::float_cast<float>(fx) << " && " << fx << '\n' << std::endl;

    f /= LS_PI;
    FixedType fx2 = fx * ls::math::rcp<FixedType::base_type, FixedType::fraction_digits>(FixedType(LS_PI));
    fx /= FixedType(LS_PI);
    std::cout << f << " == " << ls::math::float_cast<float>(fx) << " && " << fx << ' ' << fx2 << '\n' << std::endl;

    constexpr FixedType pi = FixedType{LS_PI};
    constexpr FixedType e = FixedType{LS_E};

    std::cout << "-PI:       " << -LS_PI                            << " = " << -pi                                         << std::endl;
    std::cout << "1/PI:      " << ls::math::rcp(LS_PI)              << " = " << ls::math::rcp(FixedType{LS_PI})             << std::endl;
    std::cout << "ABS(-PI):  " << ls::math::abs(-LS_PI)             << " = " << ls::math::abs(FixedType{-LS_PI})            << std::endl;
    std::cout << "E:         " << LS_E                              << " = " << e                                           << std::endl;
    std::cout << "Floor:     " << e                                 << " = " << ls::math::floor(e)                          << std::endl;
    std::cout << "Ceil:      " << e                                 << " = " << ls::math::ceil(e)                           << std::endl;
    std::cout << "Round:     " << e                                 << " = " << ls::math::round(e)                          << std::endl;
    std::cout << "Fract:     " << e                                 << " = " << ls::math::fract(e)                          << std::endl;
    std::cout << "Sin(PI/6): " << ls::math::sin(LS_PI_OVER_3) << " = " << ls::math::sin<FixedType>(FixedType{LS_PI_OVER_3}) << std::endl;
    std::cout << "Cos(PI/6): " << ls::math::cos(LS_PI_OVER_3) << " = " << ls::math::cos<FixedType>(FixedType{LS_PI_OVER_3}) << std::endl;
    std::cout << "Tan(PI/6): " << ls::math::tan(LS_PI_OVER_3) << " = " << ls::math::tan<FixedType>(FixedType{LS_PI_OVER_3}) << std::endl;

    return 0;
}
