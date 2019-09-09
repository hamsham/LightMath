
#include <iostream>

#include <lightsky/math/half.h>



int main()
{
    for (int i = -100; i <= 100; ++i)
    {
        float f = (float)i / 100.f;
        ls::math::Half h = f;

        std::cout << f << ' ' << h.bits << ' ' << (float)h << std::endl;
    }
    return 0;
}
