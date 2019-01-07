
#include <iostream>

#include "lightsky/math/fixed.h"
#include "lightsky/math/vec3.h"

#define FixedType ls::math::ulong_lowp_t



inline std::ostream& operator << (std::ostream& os, const FixedType& fx)
{
    const FixedType::base_type n = fx.number >> FixedType::fraction_digits;
    const FixedType::base_type d = fx.number ^ (n << FixedType::fraction_digits);
    return os << n << '.' << d;
}



int main()
{
    float f = 1.f;
    FixedType fx(f);

    std::cout << f << " == " << fx.number << '\n' << std::endl;

    f *= 4.f;
    fx *= ls::math::fixed_cast<FixedType>(4);
    std::cout << f << " == " << (float)fx << " && " << fx << '\n' << std::endl;

    f *= 9876.54321f;
    fx *= FixedType(9875.54321f);
    std::cout << f << " == " << (float)fx << " && " << fx << '\n' << std::endl;

    f /= LS_PI;
    fx /= FixedType(LS_PI);
    std::cout << f << " == " << (float)fx << " && " << fx << '\n' << std::endl;

    ls::math::vec3 v{LS_E, LS_E, LS_E};
    ls::math::vec3_t<FixedType> vx = (ls::math::vec3_t<FixedType>)v;
    for (unsigned i = 0; i < 3; ++i)
    {
        std::cout << v[i] << " == " << vx[i] << " && " << vx[i] << std::endl;
    }

    return 0;
}
