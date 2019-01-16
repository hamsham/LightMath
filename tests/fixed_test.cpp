
#include <iostream>

#include "lightsky/math/fixed.h"
#include "lightsky/math/vec3.h"

#define FixedType ls::math::long_lowp_t



inline std::ostream& operator << (std::ostream& os, const FixedType& fx)
{
    const FixedType::base_type n = fx.number >> FixedType::fraction_digits;
    os << n << '.';

    FixedType::base_type d = fx.number ^ (FixedType::base_type)((unsigned long long)n << FixedType::fraction_digits);

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

    f *= 4.f;
    fx *= ls::math::fixed_cast<FixedType>(4);
    std::cout << f << " == " << (float)fx << " && " << fx << '\n' << std::endl;

    f *= 9876.54321f;
    fx *= FixedType(9875.54321f);
    std::cout << f << " == " << (float)fx << " && " << fx << '\n' << std::endl;

    f /= LS_PI;
    fx /= FixedType(LS_PI);
    std::cout << f << " == " << (float)fx << " && " << fx << '\n' << std::endl;

    ls::math::vec3 v{LS_PI, LS_E, LS_E};
    ls::math::vec3_t<FixedType> vx = (ls::math::vec3_t<FixedType>)v;
    for (unsigned i = 0; i < 3; ++i)
    {
        std::cout << v[i] << " == " << (float)vx[i] << " && " << vx[i] << std::endl;
    }

    std::cout << '\n';

    const FixedType rounding = ls::math::fixed_cast<FixedType>(10) / ls::math::fixed_cast<FixedType>(5);
    std::cout << rounding << std::endl;
    std::cout << "Floor: " << vx[0]+rounding << " == " << ls::math::floor(vx[0]+rounding) << std::endl;
    std::cout << "Ceil:  " << vx[0]+rounding << " == " << ls::math::ceil(vx[0]+rounding) << std::endl;
    std::cout << "Round: " << vx[0]+rounding << " == " << ls::math::round(vx[0]+rounding) << std::endl;

    FixedType five = FixedType{(FixedType::base_type)(1ull << FixedType::fraction_digits) - 1} / ls::math::fixed_cast<FixedType>(1);
    std::cout << five << ' ' << std::hex  << five.number << std::endl;

    return 0;
}
