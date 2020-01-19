
#include <iostream>

#include "lightsky/math/fixed.h"
#include "lightsky/math/vec3.h"

#define FixedType ls::math::long_medp_t



inline std::ostream& operator << (std::ostream& os, const FixedType& fx)
{
    const FixedType::base_type n = fx.number >> FixedType::fraction_digits;
    os << n << '.';

    FixedType::base_type d = fx.number & FixedType::fraction_mask;

    if (!d)
    {
        return os << '0';
    }

    while (d > 0)
    {
        d *= 10;
        os << ('0' + (d >> FixedType::fraction_digits));
        d &= 1ull << (FixedType::fraction_digits - 1u);
    }

    return os;
}



int main()
{
    float f = 1.f;
    FixedType fx(f);

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

    FixedType pi = FixedType{LS_PI};

    FixedType e = FixedType{LS_E};

    std::cout << "PI:        " << LS_PI                             << " = " << pi                                           << std::endl;
    std::cout << "1/PI:      " << ls::math::rcp(LS_PI)              << " = " << ls::math::rcp(FixedType{LS_PI})              << std::endl;
    std::cout << "E:         " << LS_E                              << " = " << e                                            << std::endl;
    std::cout << "Floor:     " << e                                 << " = " << ls::math::floor(e)                           << std::endl;
    std::cout << "Ceil:      " << e                                 << " = " << ls::math::ceil(e)                            << std::endl;
    std::cout << "Round:     " << e                                 << " = " << ls::math::round(e)                           << std::endl;
    std::cout << "Sin(PI/6): " << ls::math::sin(LS_PI_OVER_6) << " = " << ls::math::sin(FixedType{LS_PI_OVER_6}) << std::endl;
    std::cout << "Cos(PI/6): " << ls::math::cos(LS_PI_OVER_6) << " = " << ls::math::cos(FixedType{LS_PI_OVER_6}) << std::endl;
    std::cout << "Tan(PI/6): " << ls::math::tan(LS_PI_OVER_6) << " = " << ls::math::tan(FixedType{LS_PI_OVER_6}) << std::endl;

    return 0;
}
