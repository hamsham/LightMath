
/*
 * Testing acquisition of a sign bit from different types
 */

#include <iostream>
#include "lightsky/math/scalar_utils.h"



int main()
{
    constexpr char c = -42;
    constexpr int cSign = ls::math::sign_bit<decltype(c)>(c);
    std::cout << "Sign bit of " << (int)c << " == " << cSign << std::endl;

    constexpr unsigned char uc = (unsigned char)c;
    constexpr int ucSign = ls::math::sign_bit<decltype(uc)>(uc);
    std::cout << "Sign bit of " << (unsigned)uc << " == " << ucSign << std::endl;

    constexpr short s = -42;
    constexpr int sSign = ls::math::sign_bit<decltype(s)>(s);
    std::cout << "Sign bit of " << s << " == " << sSign << std::endl;

    constexpr unsigned short us = (unsigned short)s;
    constexpr int usSign = ls::math::sign_bit<decltype(us)>(us);
    std::cout << "Sign bit of " << us << " == " << usSign << std::endl;

    constexpr long long l = -42;
    constexpr int lSign = ls::math::sign_bit<decltype(l)>(l);
    std::cout << "Sign bit of " << l << " == " << lSign << std::endl;

    constexpr unsigned long long ul = (unsigned long long)l;
    constexpr int ulSign = ls::math::sign_bit<decltype(ul)>(ul);
    std::cout << "Sign bit of " << ul << " == " << ulSign << std::endl;

    constexpr float f = -42.f;
    constexpr int fSign = ls::math::sign_bit<float>(f);
    std::cout << "Sign bit of " << f << " == " << fSign << std::endl;

    constexpr long double ld = -42.0l;
    constexpr int ldSign = ls::math::sign_bit<long double>(ld);
    std::cout << "Sign bit of " << ld << " == " << ldSign << std::endl;

    return 0;
}
