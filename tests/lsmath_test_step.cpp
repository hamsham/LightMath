
#include <cmath>
#include <iostream>

#include "lightsky/math/vec_utils.h"

int main()
{
    ls::math::vec4 a = {0.25f, 0.35f, 0.45f, 0.5f};
    ls::math::vec4 b = ls::math::smoothstep<float>(ls::math::vec4{0.f}, ls::math::vec4{1.f}, a);
    ls::math::vec4 c = ls::math::smoothstep(ls::math::vec4{0.f}, ls::math::vec4{1.f}, a);

    std::cout << "Standard smoothstep:";
    for (unsigned i = 0; i < 4; ++i)
    {
        std::cout << "\n\t" << b[i];
    }
    std::cout << std::endl;

    std::cout << "Specialized smoothstep:";
    for (unsigned i = 0; i < 4; ++i)
    {
        std::cout << "\n\t" << c[i];
    }
    std::cout << std::endl;

    return 0;
}
