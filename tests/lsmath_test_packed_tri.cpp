/*
 * File:   lsmath_test_packed_tri.cpp
 * Author: hammy
 *
 * Created on Jan 12, 2023 at 6:22 PM
 */

#include <iostream>
#include <iomanip>
#include <limits>

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



math::vec3 circumcenter(const math::vec3& a, const math::vec3& b, const math::vec3& c) noexcept
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
    return a + (abx * acLen + acx * abLen) / (abacLen + abacLen);
}



float incenter(const math::vec3& a, const math::vec3& b, const math::vec3& c, math::vec3& outCircumcenter, math::vec3& outTriNormal) noexcept
{
    const math::vec3&& bc = b - c;
    const math::vec3&& ac = a - c;
    const math::vec3&& ab = a - b;
    const math::vec3&& abac = math::cross(ab, ac); // triangle normal

    const float la = math::length(bc);
    const float lb = math::length(ac);
    const float lc = math::length(ab);
    const float p = math::sum(la, lb, lc);

    const math::vec3&& center = (la*a + lc*b + lc*c) / p;

    // add vector A to get the location of the circumcenter
    outCircumcenter = center;
    outTriNormal = math::normalize(abac);

    const float s = p * 0.5f;
    const float sa = s-la;
    const float sb = s-lb;
    const float sc = s-lc;
    const float area = std::sqrt(s*sa*sb*sc);

    return (2.f*area)/p; // radius
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



inline math::vec2 hemimax_norm_encode(const math::vec3& n) noexcept
{
    math::vec3&& m = n / (math::abs(n[0]) + math::abs(n[1]) + math::abs(n[2]));
    return math::vec2{m[0] + m[1], m[0] - m[1]};
}



inline math::vec3 hemimax_norm_decode(const math::vec2& n) noexcept
{
    const math::vec2&& f = math::vec2{n[0] + n[1], n[0] - n[1]};
    return math::normalize(math::vec3{f[0], f[1], 2.f - math::abs(f[0]) - math::abs(f[1])});
}



inline math::vec2 spherical_norm_encode(const math::vec3& n) noexcept
{
    const math::vec2&& v = math::vec2{
        std::atan2(n[1], n[0]),
        std::acos(n[2])
    };

    return math::vec2{
        v[0] + LS_TWO_PI * math::step(n[0], -0.f),
        v[1] + LS_TWO_PI * math::step(n[1], -0.f)
    };
}



inline math::vec3 spherical_norm_decode(const math::vec2& n) noexcept
{
    return math::vec3{
        std::sin(n[1]) * std::cos(n[0]),
        std::sin(n[1]) * std::sin(n[0]),
        std::cos(n[1])
    };
}



template <bool positiveY>
inline math::mat3 axial_rotation_matrix(const math::mat3& r, float angleA, float angleB, float angleC) noexcept
{
    const float cx = std::cos(angleA);
    const float sx = math::sin(angleA);

    const float cy = std::cos(angleB);
    const float sy = math::sin(angleB);

    const float cz = std::cos(angleC);
    const float sz = math::sin(angleC);

    if (!positiveY)
    {
        return math::mat3{
            math::normalize(math::vec3{(r.m[0][0] * cx) + (r.m[0][1] * sx), -(r.m[1][0] * cx) - (r.m[1][1] * sx), (r.m[2][0] * cx) + (r.m[2][1] * sx)}),
            math::normalize(math::vec3{(r.m[0][0] * cy) + (r.m[0][1] * sy), -(r.m[1][0] * cy) - (r.m[1][1] * sy), (r.m[2][0] * cy) + (r.m[2][1] * sy)}),
            math::normalize(math::vec3{(r.m[0][0] * cz) + (r.m[0][1] * sz), -(r.m[1][0] * cz) - (r.m[1][1] * sz), (r.m[2][0] * cz) + (r.m[2][1] * sz)})
        };
    }

    return math::mat3{
        math::normalize(math::vec3{(r.m[0][0] * cx) + (r.m[0][1] * sx), (r.m[1][0] * cx) + (r.m[1][1] * sx), (r.m[2][0] * cx) + (r.m[2][1] * sx)}),
        math::normalize(math::vec3{(r.m[0][0] * cy) + (r.m[0][1] * sy), (r.m[1][0] * cy) + (r.m[1][1] * sy), (r.m[2][0] * cy) + (r.m[2][1] * sy)}),
        math::normalize(math::vec3{(r.m[0][0] * cz) + (r.m[0][1] * sz), (r.m[1][0] * cz) + (r.m[1][1] * sz), (r.m[2][0] * cz) + (r.m[2][1] * sz)})
    };
}



inline void create_orthonormal_basis(const math::vec3& n, math::vec3& x, math::vec3& y) noexcept
{
    const float sign = n[2] < 0.f ? -1.f : 1.f;
    const float a = -1.f / (sign+n[2]);
    const float b = n[0] * n[1] * a;
    x = math::vec3{1.f + sign * (n[0] * n[0]) * a, sign * b, -sign * n[0]};
    y = math::vec3{b, sign + (n[1] * n[1]) * a, -n[1]};
}



math::quat create_orthonormal_basis(const math::vec3& forward, const math::vec3& up) noexcept
{
    // forward and size vectors of the coordinate frame
    const math::vec3 side = math::normalize(math::cross(up, forward));

    // cross product of bisection and [0, 0, -1] gives you the
    // half-sine values required to orientate [0, 0, -1] to f
    // the dot product gives you half the cosine
    const math::vec3&& b = math::normalize(forward + math::vec3(0.f, 0.f, -1.f));
    const math::quat&& p = math::from_axis_angle(math::cross(b, forward), math::dot(b, forward));

    // now we need an additional rotation around the f vector
    // to orientate the side vector.
    math::vec3 r{
        p[3] * p[3] + p[0] * p[0] - p[1] * p[1] - p[2] * p[2],
        (2.f * p[0] * p[1]) - (2.f * p[3] * p[2]),
        2.f * p[0] * p[2] + 2.f * p[3] * p[1]
    };

    const math::vec3&& c = math::normalize(side + r);
    const math::quat&& q = math::from_axis_angle(math::cross(side, c), math::dot(c, side));

    // now we can take the product of q and p
    return math::normalize(p * q);
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



void test_tri_incenter()
{
    math::vec3 a = {5.75f, 6.9f, 4.25f};
    math::vec3 b = {13.77f, 8.96f, 2.7f};
    math::vec3 c = {1.234f, -3.12f, -1.1f};
    math::vec3 s, n;
    float r = incenter(a, b, c, s, n);

    std::cout
        << "Incenter:"
        << "\n\tV0:     {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tV1:     {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tV2:     {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\tCenter: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tNormal: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tRadius: " << r
        << '\n' << std::endl;
}



inline unsigned octahedral_to_int16(const math::vec2& o) noexcept
{
    unsigned x = (unsigned)((o[0] * 0.5f + 0.5f)*256.f);
    unsigned y = (unsigned)((o[1] * 0.5f + 0.5f)*256.f);
    return x + y * 256u;
}



inline math::vec2 int16_to_octahedral(const unsigned o) noexcept
{
    float x = (float)(o % 256u) / 256.f;
    float y = (float)(o / 256u) / 256.f;
    return math::vec2{x, y} * 2.f - 1.f;
}



struct PackedTriangle
{
    math::vec2 circumcenter;
    float distance;

    unsigned normal;
    float radius;

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
    const math::vec2&& sh = spheremap_norm_encode(sn);

    const math::vec3&& as = math::normalize(a-s);
    const math::vec3&& bs = math::normalize(b-s);
    const math::vec3&& cs = math::normalize(c-s);

    #if 1
        math::vec3 right;
        math::vec3 up;
        create_orthonormal_basis(n, right, up);
    #else
        const math::mat3&& o = math::pure_look_at(math::vec3{0.f}, n, math::vec3{0.f, 1.f, 0.f});
        const math::vec3& x = o[0];
        const math::vec3& y = o[1];
        const math::vec3& z = o[2];
        const math::vec3 right = {x[0], y[0], z[0]};
    #endif

    const float angleA = -std::atan2(math::dot(math::cross(right, as), n), math::dot(as, right));
    const float angleB = -std::atan2(math::dot(math::cross(right, bs), n), math::dot(bs, right));
    const float angleC = -std::atan2(math::dot(math::cross(right, cs), n), math::dot(cs, right));

    d = n[2] > -0.f ? d : -d;
    n[2] = std::abs(n[2]);
    const math::vec2&& m = hemimax_norm_encode(n);

    std::cout
        << "In Triangle:"
        << "\n\tS: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tD:  " << d
        << "\n\tN: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tM: {" << m[0] << ", " << m[1] << '}'
        << "\n\tR:  " << r
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\ta:  " << angleA
        << "\n\tb:  " << angleB
        << "\n\tc:  " << angleC
        << '\n' << std::endl;

    outTriData.circumcenter = sh;
    outTriData.distance = d;

    outTriData.normal = octahedral_to_int16(m);
    outTriData.radius = r;

    outTriData.angleA = angleA;
    outTriData.angleB = angleB;
    outTriData.angleC = angleC;
}



void test_tri_unpacking(const PackedTriangle& triData)
{
    const math::vec3&& sn = spheremap_norm_decode(triData.circumcenter);
    const float d = triData.distance;
    const math::vec3&& s = sn * math::abs(d);

    const math::vec2 m = int16_to_octahedral(triData.normal);
    math::vec3&& n = hemimax_norm_decode(m);
    float r = triData.radius;

    n[2] = d > -0.f ? n[2] : -n[2];

    const float angleA = triData.angleA;
    const float angleB = triData.angleB;
    const float angleC = triData.angleC;

    math::mat3 v;

    #if 1
        math::mat3 o;
        o[2] = n;
        create_orthonormal_basis(n, o[0], o[1]);
        v = axial_rotation_matrix<false>(o, angleA, angleB, angleC);
    #else
        const math::mat3&& o = math::pure_look_at(math::vec3{0.f}, n, math::vec3{0.f, 1.f, 0.f});
        v = axial_rotation_matrix<true>(o, angleA, angleB, angleC);
    #endif

    const math::vec3& x = v[0];
    const math::vec3& y = v[1];
    const math::vec3& z = v[2];

    const math::vec3&& a = (x * r) + s;
    const math::vec3&& b = (y * r) + s;
    const math::vec3&& c = (z * r) + s;

    std::cout //<< std::setprecision(std::numeric_limits<float>::digits)
        << "Out Triangle:"
        << "\n\tS: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tD:  " << d
        << "\n\tN: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tM: {" << m[0] << ", " << m[1] << '}'
        << "\n\tR:  " << r
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\ta:  " << angleA
        << "\n\tb:  " << angleB
        << "\n\tc:  " << angleC
        << '\n' << std::endl;
}



int main()
{
    //test_packed_tri_length();
    //test_tri_circumcemath::length(nter();
    //test_tri_incenter();

    PackedTriangle triData;
    test_tri_packing(triData);
    test_tri_unpacking(triData);

    #if 0
    math::vec3&& m = math::normalize(math::vec3{1.5f, 1.3f, 2.f});
    math::vec3&& n = math::normalize(math::vec3{8.f, 1.42f, 0.77f});
    std::cout << "M: {" << m[0] << ", " << m[1] << ", " << m[2] << '}' << std::endl;
    std::cout << "N: {" << n[0] << ", " << n[1] << ", " << n[2] << '}' << std::endl;

    math::vec2 sh = hemimax_norm_encode(m);
    math::vec2 nh = hemimax_norm_encode(n);
    std::cout << "R:  " << math::length(sh) << std::endl;
    std::cout << "R:  " << math::length(nh) << std::endl;
    std::cout << "E: {" << sh[0] << ", " << sh[1] << '}' << std::endl;
    std::cout << "F: {" << nh[0] << ", " << nh[1] << '}' << std::endl;

    math::vec2 r = sh / nh;
    std::cout << "R0: " << r[0] << std::endl;
    std::cout << "R1: " << r[1] << std::endl;

    m = hemimax_norm_decode(math::vec2{sh[1]-sh[0], -sh[0]});
    n = hemimax_norm_decode(sh / r);

    std::cout << "M: {" << m[0] << ", " << m[1] << ", " << m[2] << '}' << std::endl;
    std::cout << "N: {" << n[0] << ", " << n[1] << ", " << n[2] << '}' << std::endl;
    #endif

    return 0;
}