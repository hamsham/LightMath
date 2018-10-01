
#include <iostream>

#include "lightsky/math/fixed.h"
#include "lightsky/math/vec3.h"

#define FixedType ls::math::long_lowp_t



int main()
{
    float f = 1.f;
    FixedType fx(f);

    std::cout << f << " == " << fx.number << '\n' << std::endl;

    f *= 4.f;
    fx *= FixedType(4.f);
    std::cout << f << " == " << (float)fx << " && " << (int)fx << '\n' << std::endl;

    f *= 9876.123456789f;
    fx *= FixedType(9876.123456789f);
    std::cout << f << " == " << (float)fx << " && " << (int)fx << '\n' << std::endl;

    f /= LS_PI;
    fx /= FixedType(LS_PI);
    std::cout << f << " == " << (float)fx << " && " << (int)fx << '\n' << std::endl;

    ls::math::vec3 v{LS_E, LS_E, LS_E};
    ls::math::vec3_t<FixedType> vx = (ls::math::vec3_t<FixedType>)v;
    for (unsigned i = 0; i < 3; ++i)
    {
        std::cout << v[i] << " == " << (float)vx[i] << " && " << (int)vx[i] << std::endl;
    }

    return 0;
}
