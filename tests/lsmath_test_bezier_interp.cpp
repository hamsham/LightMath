
#include <iostream>

#include "lightsky/math/Interpolate.h"

namespace math = ls::math;

int main()
{
    std::cout << "factorial(4): " << math::impl::_binomial_factorial<unsigned>(4) << std::endl;
    std::cout << "binomial_coeff<4, 3>(): " << math::impl::_binomial_coeff<4, 3>() << std::endl;

    std::cout << "Bezier Quadratic: " << math::bezier_quadratic<float>(0.5f, 3.f, 6.f, 7.f) << std::endl;
    std::cout << "Bezier General (quadratic): " << math::bezier_general<float, float, float, float>(0.5f, 3.f, 6.f, 7.f) << std::endl;

    std::cout << "Bezier Cubic: " << math::bezier_cubic<float>(0.8f, 3.f, 6.f, 7.f, 1.f) << std::endl;
    std::cout << "Bezier General (cubic): " << math::bezier_general<float, float, float, float, float>(0.8f, 3.f, 6.f, 7.f, 1.f) << std::endl;

    return 0;
}
