/*
 * File:   lsmath_test_packed_tri.cpp
 * Author: hammy
 *
 * Created on Jan 12, 2023 at 6:22 PM
 */

#include <iostream>

#include "lightsky/math/mat_utils.h"
#include "lightsky/math/quat_utils.h"
#include "lightsky/math/vec_utils.h"

namespace math = ls::math;



template <typename float_type>
struct PackedLineLength
{
    float_type invMaxLen; // store inverse to allow more precision
    float_type aOverC;
};

typedef PackedLineLength<float> PackedLineLength32;
typedef PackedLineLength<math::half> PackedLineLength16;



template <typename float_type>
struct PackedTriLength
{
    float_type invMaxLen; // store inverse to allow more precision
    float_type aOverC;
    float_type bOverC;
};

typedef PackedTriLength<float> PackedTriLength32;
typedef PackedTriLength<math::half> PackedTriLength16;



inline void sort_floats(float& a, float& b) noexcept
{
    float tmp;

    if (a > b)
    {
        tmp = a;
        a = b;
        b = tmp;
    }
}



inline void sort_floats(float& a, float& b, float& c) noexcept
{
    float tmp;

    if (a > b)
    {
        tmp = a;
        a = b;
        b = tmp;
    }

    if (a > c)
    {
        tmp = a;
        a = c;
        c = tmp;
    }

    if (b > c)
    {
        tmp = b;
        b = c;
        c = tmp;
    }
}



template <typename float_type>
PackedLineLength<float_type> pack_floats(float l0, float l1) noexcept
{
    sort_floats(l0, l1);

    // compressed form: a single angle and length
    const PackedLineLength<float_type> ret = {
        (float_type)(1.f/l1),
        (float_type)(l0/l1),
    };

    return ret;
}



template <typename float_type>
PackedTriLength<float_type> pack_floats(float l0, float l1, float l2) noexcept
{
    std::cout
        << "Input Lengths:"
        << "\n\tIN Len0: " << l0
        << "\n\tIN Len1: " << l1
        << "\n\tIN Len2: " << l2
        << '\n' << std::endl;

    sort_floats(l0, l1, l2);

    // compressed form: a single angle and length
    const PackedTriLength<float_type> ret = {
        (float_type)(1.f/l2),
        (float_type)(l0/l2),
        (float_type)(l1/l2),
    };

    /*
    std::cout
        << "Compressed data:"
        << "\n\tMid Length: " << ret.midLen
        << "\n\tA / B:      " << (float)ret.bOverC
        << "\n\tB / C:      " << (float)ret.aOverB
        << '\n' << std::endl;
    */

    return ret;
}



template <typename float_type>
PackedLineLength<float_type> pack_line_lengths(const math::vec3& a, const math::vec3& b) noexcept
{
    float l0 = math::length(a);
    float l1 = math::length(b);
    const PackedLineLength<float_type> ret = pack_floats<float_type>(l0, l1);

    return ret;
}



template <typename float_type>
PackedTriLength<float_type> pack_triangle_lengths(const math::vec3& a, const math::vec3& b, const math::vec3& c) noexcept
{
    float l0 = math::length(a);
    float l1 = math::length(b);
    float l2 = math::length(c);
    const PackedTriLength<float_type> ret = pack_floats<float_type>(l0, l1, l2);

    return ret;
}



template <typename float_type>
void unpack_line_lengths(const PackedLineLength<float_type>& tri, float& a, float& b) noexcept
{
    // output metadata
    float outCoeff0 = 1.f/(float)tri.invMaxLen;
    float aOverC    = (float)tri.aOverC;
    float outCoeff1 = aOverC;

    float outL0 = outCoeff0 * outCoeff1;
    float outL1 = outCoeff0;

    a = outL0;
    b = outL1;
}



template <typename float_type>
void unpack_triangle_lengths(const PackedTriLength<float_type>& tri, float& a, float& b, float& c) noexcept
{
    // output metadata
    float outCoeff0 = 1.f/(float)tri.invMaxLen;
    float aOverC    = (float)tri.aOverC;
    float bOverC    = (float)tri.bOverC;
    float outCoeff1 = aOverC;
    float outCoeff2 = bOverC;

    /*
    std::cout
        << "Output coefficients:"
        << "\n\tA / B:     " << aOverB
        << "\n\tB / C:     " << bOverC
        << "\n\tMid Len:   " << outCoeff1
        << '\n' << std::endl;
    */

    float outL0 = outCoeff0 * outCoeff1;
    float outL1 = outCoeff0 * outCoeff2;
    float outL2 = outCoeff0;

    /*
    std::cout
        << "Output Lengths:"
        << "\n\tLength 0: " << outL0
        << "\n\tLength 1: " << outL1
        << "\n\tLength 2: " << outL2
        << '\n' << std::endl;
    */

    a = outL0;
    b = outL1;
    c = outL2;
}



void test_packed_tri_length()
{
    //math::vec3 v0 = {42.f, 77.f, 96.f};
    //math::vec3 v1 = {13.f, -2.f, 86.f};
    //math::vec3 v2 = {82.f, -15.f, 7.f};

    math::vec3 v0 = {5.75f, 6.9f, 4.25f};
    math::vec3 v1 = {28.96f, 13.77f, 2.7f};
    math::vec3 v2 = {1.234f, -33.12f, -1.1f};

    float af, bf, cf;
    const PackedTriLength32&& test32 = pack_triangle_lengths<float>(v0, v1, v2);
    unpack_triangle_lengths<float>(test32, af, bf, cf);

    const PackedTriLength16&& test16 = pack_triangle_lengths<math::half>(v0, v1, v2);
    unpack_triangle_lengths<math::half>(test16, af, bf, cf);
}



float circumcenter(const math::vec3& a, const math::vec3& b, const math::vec3& c, math::vec3& outCircumcenter, math::vec3& outTriNormal) noexcept
{
    const math::vec3&& ac = c - a;
    const math::vec3&& ab = b - a;
    const math::vec3&& abac = math::cross(ab, ac); // triangle normal

    const float abLen = math::length_squared(ab);
    const float acLen = math::length_squared(ac);
    const float abacLen = math::length_squared(abac);

    const math::vec3&& abx = math::cross(abac, ab);
    const math::vec3&& acx = math::cross(ac, abac);

    // center is relative to the vector A
    const math::vec3&& center = (abx * acLen + acx * abLen) / (abacLen + abacLen);

    // add vector A to get the location of the circumcenter
    outCircumcenter = a + center;
    outTriNormal = math::normalize(abac);

    return math::length(center); // radius
}



inline math::vec2 spheremap_norm_encode(const math::vec3& n) noexcept
{
    // Extrapolated from https://www.shadertoy.com/view/llfcRl
    return math::vec2_cast(n) / std::sqrt(2.f * n[2] + 2.f);
}



inline math::vec3 spheremap_norm_decode(const math::vec2& n) noexcept
{
    // Extrapolated from https://www.shadertoy.com/view/llfcRl
    float f = math::length_squared(n);
    return math::vec3_cast(n * 2.f * std::sqrt(1.f - f), 1.f - 2.f * f);
}



inline math::mat3 axial_rotation_matrix(float angle) noexcept
{
    const float c = std::cos(angle);
    const float s = math::sin(angle);

    // z
    return math::mat3{
        c,   -s,  0.f,
        s,   c,   0.f,
        0.f, 0.f, 1.f
    };
}



inline math::mat3 axial_rotation_matrix(const math::mat3& r, float angleA, float angleB, float angleC) noexcept
{
    const float cx = std::cos(angleA);
    const float sx = math::sin(angleA);

    const float cy = std::cos(angleB);
    const float sy = math::sin(angleB);

    const float cz = std::cos(angleC);
    const float sz = math::sin(angleC);

    return math::mat3{
        math::normalize(math::vec3{(r.m[0][0] * cx) + (r.m[0][1] * sx), (r.m[1][0] * cx) + (r.m[1][1] * sx), (r.m[2][0] * cx) + (r.m[2][1] * sx)}),
        math::normalize(math::vec3{(r.m[0][0] * cy) + (r.m[0][1] * sy), (r.m[1][0] * cy) + (r.m[1][1] * sy), (r.m[2][0] * cy) + (r.m[2][1] * sy)}),
        math::normalize(math::vec3{(r.m[0][0] * cz) + (r.m[0][1] * sz), (r.m[1][0] * cz) + (r.m[1][1] * sz), (r.m[2][0] * cz) + (r.m[2][1] * sz)})
    };
}



void test_tri_circumcenter()
{
    math::vec3 a = {5.75f, 6.9f, 4.25f};
    math::vec3 b = {13.77f, 8.96f, 2.7f};
    math::vec3 c = {1.234f, -3.12f, -1.1f};
    math::vec3 s, n;
    float r = circumcenter(a, b, c, s, n);

    std::cout
        << "Curcumcenter:"
        << "\n\tV0:     {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tV1:     {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tV2:     {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\tCenter: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tNormal: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tRadius: " << r
        << '\n' << std::endl;
}



struct PackedTriangle
{
    math::vec3 circumcenter;
    float distance;

    math::vec3 debugNorm;
    math::vec2 normal;

    float angleA;
    float angleB;
    float angleC;
};



void test_tri_packing(PackedTriangle& outTriData)
{
    math::vec3 a = {5.75f, 6.9f, 4.25f};
    math::vec3 b = {13.77f, 8.96f, 2.7f};
    math::vec3 c = {1.234f, -3.12f, -1.1f};

    math::vec3 s, n;
    float r = circumcenter(a, b, c, s, n);
    float d = math::length(s);
    const math::vec3&& sn = math::normalize(s);

    const math::vec3&& as = math::normalize(a-s);
    const math::vec3&& bs = math::normalize(b-s);
    const math::vec3&& cs = math::normalize(c-s);

    const math::mat3&& o = math::pure_look_at(math::vec3{0.f}, n, math::vec3{0.f, 1.f, 0.f});
    const math::vec3& x = o[0];
    const math::vec3& y = o[1];
    const math::vec3& z = o[2];

    const math::vec3 right = {x[0], y[0], z[0]};

    const float angleA = -std::atan2(math::dot(math::cross(right, as), n), math::dot(as, right));
    const float angleB = -std::atan2(math::dot(math::cross(right, bs), n), math::dot(bs, right));
    const float angleC = -std::atan2(math::dot(math::cross(right, cs), n), math::dot(cs, right));

    const math::vec2&& m0 = math::normalize(spheremap_norm_encode(n));
    const math::vec2&& m1 = m0 * r;

    std::cout
        << "In Triangle:"
        << "\n\tS: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tD:  " << d
        << "\n\tN: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tM: {" << m0[0] << ", " << m0[1] << '}'
        << "\n\tM: {" << m1[0] << ", " << m1[1] << '}'
        << "\n\tR:  " << r
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\ta:  " << angleA
        << "\n\tb:  " << angleB
        << "\n\tc:  " << angleC
        << '\n' << std::endl;

    outTriData.circumcenter = sn;
    outTriData.distance = d;

    outTriData.debugNorm = n * r;
    outTriData.normal = m1;

    outTriData.angleA = angleA;
    outTriData.angleB = angleB;
    outTriData.angleC = angleC;
}



void test_tri_unpacking(const PackedTriangle& triData)
{
    const math::vec3& sn = triData.circumcenter;
    const float d = triData.distance;
    const math::vec3&& s = sn * d;

    const math::vec2& m1 = triData.normal;
    const float r = math::length(m1);
    const math::vec2&& m0 = m1 / r;
    //const math::vec3&& n = spheremap_norm_decode(m0);

    const math::vec3& mDebug = triData.debugNorm;
    const float rDebug = math::length(mDebug);
    const math::vec3&& n = mDebug / rDebug;

    const float angleA = triData.angleA;
    const float angleB = triData.angleB;
    const float angleC = triData.angleC;

    const math::mat3&& o = math::pure_look_at(math::vec3{0.f}, n, math::vec3{0.f, 1.f, 0.f});
    const math::mat3&& v = axial_rotation_matrix(o, angleA, angleB, angleC);

    const math::vec3& x = v[0];
    const math::vec3& y = v[1];
    const math::vec3& z = v[2];

    const math::vec3&& a = (x * r) + s;
    const math::vec3&& b = (y * r) + s;
    const math::vec3&& c = (z * r) + s;

    std::cout
        << "Out Triangle:"
        << "\n\tS: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tD:  " << d
        << "\n\tN: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tM: {" << m0[0] << ", " << m0[1] << '}'
        << "\n\tM: {" << m1[0] << ", " << m1[1] << '}'
        << "\n\tR:  " << r
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\ta:  " << angleA
        << "\n\tb:  " << angleB
        << "\n\tc:  " << angleC
        << '\n' << std::endl;
}



void test_quaternion_orientation()
{
    math::vec3 a = {5.75f, 6.9f, 4.25f};
    math::vec3 b = {13.77f, 8.96f, 2.7f};
    math::vec3 c = {1.234f, -3.12f, -1.1f};

    math::vec3 s, n;
    circumcenter(a, b, c, s, n);

    const math::vec3&& as = math::normalize(a - s);
    const math::vec3&& bs = math::normalize(b - s);
    const math::vec3&& cs = math::normalize(c - s);

    const math::mat3&& o = math::pure_look_at(math::vec3{0.f}, n, math::vec3{0.f, 1.f, 0.f});
    const math::vec3& x = o[0];
    const math::vec3& y = o[1];
    const math::vec3& z = o[2];

    const math::vec3 r{x[0], y[0], z[0]};

    const float angleA = -std::atan2(math::dot(math::cross(r, as), n), math::dot(as, r));
    const float angleB = -std::atan2(math::dot(math::cross(r, bs), n), math::dot(bs, r));
    const float angleC = -std::atan2(math::dot(math::cross(r, cs), n), math::dot(cs, r));

    const math::mat3&& v = axial_rotation_matrix(o, angleA, angleB, angleC);
    const math::vec3& vx = v[0];
    const math::vec3& vy = v[1];
    const math::vec3& vz = v[2];

    std::cout
        << "Orientations:"
        << "\n\tA:  {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB:  {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC:  {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << '\n'
        << "\n\tAT:  " << angleA
        << "\n\tBT:  " << angleB
        << "\n\tCT:  " << angleC
        << '\n'
        << "\n\tox: {" << x[0] << ", " << x[1] << ", " << x[2] << '}'
        << "\n\toy: {" << y[0] << ", " << y[1] << ", " << y[2] << '}'
        << "\n\toz: {" << z[0] << ", " << z[1] << ", " << z[2] << '}'
        << '\n'
        << "\n\tAN: {" << as[0] << ", " << as[1] << ", " << as[2] << '}'
        << "\n\tBN: {" << bs[0] << ", " << bs[1] << ", " << bs[2] << '}'
        << "\n\tCN: {" << cs[0] << ", " << cs[1] << ", " << cs[2] << '}'
        << '\n'
        << "\n\to: {" << vx[0] << ", " << vx[1] << ", " << vx[2] << '}'
        << "\n\to: {" << vy[0] << ", " << vy[1] << ", " << vy[2] << '}'
        << "\n\to: {" << vz[0] << ", " << vz[1] << ", " << vz[2] << '}'
        << '\n' << std::endl;
}



int main()
{
    //test_packed_tri_length();
    //test_tri_circumcenter();

    PackedTriangle triData;
    test_tri_packing(triData);
    test_tri_unpacking(triData);

    #if 0
    const math::vec3&& n = math::normalize(math::vec3{1.f, 1.f, 1.f});
    //n = n * 0.5f + 0.5f;

    std::cout << "Norm: {" << n[0] << ", " << n[1] << ", " << n[2] << '}' << std::endl;
    math::vec2 e = spheremap_norm_encode(n);
    std::cout << "Hemi: {" << e[0] << ", " << e[1] << '}' << std::endl;
    //e += 1.f;
    float temp = e[0];
    e[0] = e[1];
    e[1] = -temp;
    //e[0] = -e[0];
    //e[1] = -e[1];
    //e = e * math::rotate(math::mat2{1.f}, LS_PI_OVER_2);
    //e[0] = math::fmod_1(e[0]);
    //e[1] = math::fmod_1(e[1]);
    std::cout << "Hemi: {" << e[0] << ", " << e[1] << '}' << std::endl;
    const math::vec3&& m = math::normalize(spheremap_norm_decode(e));
    std::cout << "Norm: {" << m[0] << ", " << m[1] << ", " << m[2] << '}' << std::endl;
    #endif

    //test_quaternion_orientation();

    return 0;
}