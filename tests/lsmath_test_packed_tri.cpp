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

    return area/s; // radius
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



inline math::vec2 spheremap_norm_encode(const math::vec3& n) noexcept
{
    // Extrapolated from https://www.shadertoy.com/view/llfcRl
    //return math::vec2_cast(n) / std::sqrt(2.f * n[2] + 2.f);
    return math::vec2_cast(n) * math::inversesqrt(2.f * n[2] + 2.f);
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



inline math::mat3 axial_rotation_matrix(const math::mat3& r, float angleA, float angleB, float angleC) noexcept
{
    const float cx = std::cos(angleA);
    const float sx = std::sin(angleA);

    const float cy = std::cos(angleB);
    const float sy = std::sin(angleB);

    const float cz = std::cos(angleC);
    const float sz = std::sin(angleC);

    return math::mat3{
        math::normalize(math::vec3{(r.m[0][0] * cx) + (r.m[0][1] * sx), (r.m[1][0] * cx) + (r.m[1][1] * sx), (r.m[2][0] * cx) + (r.m[2][1] * sx)}),
        math::normalize(math::vec3{(r.m[0][0] * cy) + (r.m[0][1] * sy), (r.m[1][0] * cy) + (r.m[1][1] * sy), (r.m[2][0] * cy) + (r.m[2][1] * sy)}),
        math::normalize(math::vec3{(r.m[0][0] * cz) + (r.m[0][1] * sz), (r.m[1][0] * cz) + (r.m[1][1] * sz), (r.m[2][0] * cz) + (r.m[2][1] * sz)})
    };
}



inline math::mat3 create_orthonormal_basis(const math::vec3& n) noexcept
{
    const float sign = n[2] < 0.f ? -1.f : 1.f;
    const float a = -1.f / (sign+n[2]);
    const float b = n[0] * n[1] * a;

    return math::mat3{
        math::vec3{1.f + sign * (n[0] * n[0]) * a, sign * b, -sign * n[0]},
        -math::vec3{b, sign + (n[1] * n[1]) * a, -n[1]},
        n
    };
}



inline math::vec3 create_orthonormal_basis_x(const math::vec3& n) noexcept
{
    const float sign = n[2] < 0.f ? -1.f : 1.f;
    const float a = -1.f / (sign+n[2]);
    const float b = n[0] * n[1] * a;

    return math::vec3{1.f + sign * (n[0] * n[0]) * a, sign * b, -sign * n[0]};
}



struct alignas(uint16_t) PackedTriangle
{
    math::vec2_t<math::half> circumcenter;
    math::vec2_t<math::half> normal;

    math::half distance;
    math::half angleA;
    math::half angleB;
    math::half angleC;
};

static_assert(sizeof(PackedTriangle) == sizeof(uint16_t)*8, "Invalid size of packed triangle structure.");



template <uint16_t numShifts>
inline math::half encode_2_bits_in_float(math::half f, math::half bits) noexcept
{
    uint16_t maskedBits = bits.bits & (0x0003u << numShifts);
    f.bits |= maskedBits << (14-numShifts);
    return f;
}



template <uint16_t numShifts>
inline uint16_t decode_2_bits_in_float(const math::half f) noexcept
{
    uint16_t maskedBits = (f.bits & 0xC000) >> (14-numShifts);
    return maskedBits;
}



template <uint16_t bitPos>
inline uint16_t extract_sign_bit(math::half f) noexcept
{
    uint16_t bit = f.bits & 0x8000;
    return bit >> (15-bitPos);
}



template <uint16_t bitPos>
inline math::half insert_sign_bit(math::half f, math::half bits) noexcept
{
    uint16_t bit = (bits.bits & (1 << bitPos));
    f.bits |= bit << (15-bitPos);
    return f;
}



inline PackedTriangle encode_tri_radius(const PackedTriangle& tri, const math::half& radius) noexcept
{
    // exploit the spare 2 bits of each of the 7 input variables, plus sign bit
    // of the circumcenter's distance from origin, for a total of 15 spare bits
    PackedTriangle result;
    result.circumcenter[0] = encode_2_bits_in_float<0>(tri.circumcenter[0], radius);
    result.circumcenter[1] = encode_2_bits_in_float<2>(tri.circumcenter[1], radius);
    result.normal[0]       = encode_2_bits_in_float<4>(tri.normal[0],       radius);
    result.normal[1]       = encode_2_bits_in_float<6>(tri.normal[1],       radius);
    result.angleA          = encode_2_bits_in_float<8>(tri.angleA,          radius);
    result.angleB          = encode_2_bits_in_float<10>(tri.angleB,         radius);
    result.angleC          = encode_2_bits_in_float<12>(tri.angleC,         radius);
    result.distance        = insert_sign_bit<14>(tri.distance,              radius);

    return result;
}



inline math::half decode_tri_radius(PackedTriangle& tri) noexcept
{
    math::half result{0};

    result.bits |= decode_2_bits_in_float<0>(tri.circumcenter[0]);
    result.bits |= decode_2_bits_in_float<2>(tri.circumcenter[1]);
    result.bits |= decode_2_bits_in_float<4>(tri.normal[0]);
    result.bits |= decode_2_bits_in_float<6>(tri.normal[1]);
    result.bits |= decode_2_bits_in_float<8>(tri.angleA);
    result.bits |= decode_2_bits_in_float<10>(tri.angleB);
    result.bits |= decode_2_bits_in_float<12>(tri.angleC);
    result.bits |= extract_sign_bit<14>(tri.distance);

    // Reset the highest 2 bits of each IEEE half-float
    tri.circumcenter[0].bits &= 0x3FFF;
    tri.circumcenter[1].bits &= 0x3FFF;
    tri.normal[0].bits &= 0x3FFF;
    tri.normal[1].bits &= 0x3FFF;
    tri.angleA.bits &= 0x3FFF;
    tri.angleB.bits &= 0x3FFF;
    tri.angleC.bits &= 0x3FFF;
    tri.distance.bits &= 0x7FFF; // only reset the sign bit here

    return result;
}



void test_tri_packing(PackedTriangle& outTriData)
{
    math::vec3 a = {5.75f, 6.9f, 4.25f};
    math::vec3 b = {13.77f, 8.96f, 2.7f};
    math::vec3 c = {1.234f, -3.12f, -1.1f};

    math::vec3 s, n;

    // triangle packing using the circumcenter and signed angles to each vertex
    float r = circumcenter(a, b, c, s, n);
    float d = math::length(s);

    // subtract circumcenter from each vertex to place them in a common basis
    const math::vec3&& as = math::normalize(a-s);
    const math::vec3&& bs = math::normalize(b-s);
    const math::vec3&& cs = math::normalize(c-s);

    // encode the circumcenter and normal as 2-component vectors in the range
    // of (0, 1). This range will help with reconstruction
    const math::vec3&& sn = math::normalize(s);

    // Although Spheremap-encoding is more expensive to encode/decode than
    // Octahedral normal encoding, it allows for a signed z-component.
    const math::vec2&& sh = spheremap_norm_encode(sn);
    const math::vec2&& m = spheremap_norm_encode(n);

    // Generate an orthonormal basis using the revised Frisvad method from Duff
    // et. al:
    // https://jcgt.org/published/0006/01/01/
    const math::vec3&& right = create_orthonormal_basis_x(n);

    // Retrieve the angles to each vertex along the triangle's plane using our
    // orthonormal basis
    float angleA = -std::atan2(math::dot(math::cross(right, as), n), math::dot(as, right));
    float angleB = -std::atan2(math::dot(math::cross(right, bs), n), math::dot(bs, right));
    float angleC = -std::atan2(math::dot(math::cross(right, cs), n), math::dot(cs, right));

    // Ensure all values are greater than 0 (see below for reasoning).
    angleA += LS_TWO_PI * math::step(angleA, -0.f);
    angleB += LS_TWO_PI * math::step(angleB, -0.f);
    angleC += LS_TWO_PI * math::step(angleC, -0.f);

    // Debug
    std::cout
        << "In Triangle:"
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\tS: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tD:  " << d
        << "\n\tN: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tR:  " << r
        << "\n\ta:  " << angleA
        << "\n\tb:  " << angleB
        << "\n\tc:  " << angleC
        << '\n' << std::endl;

    // Force all values to be within the range of (0, 1), with the exception of
    // the distance to our triangle's circumcenter. Because all 8 values are
    // IEEE 16-bit half-precision floats we can exploit the highest 2 bits* of
    // each variable (for a total of 15 reclaimed bits) to encode the
    // circumcenter's radius without the explicit need for extra storage.
    //
    // *The circumcenter's distance is unbounded above zero, so we may only use
    // the sign-bit. This is fine as the radius is always positive and only
    // needs 15 bits to be stored correctly.
    PackedTriangle result;
    result.circumcenter = (math::vec2_t<math::half>)math::clamp(sh * 0.5f + 0.5f, math::vec2{0.f}, math::vec2{1.f});
    result.normal = (math::vec2_t<math::half>)math::clamp(m * 0.5f + 0.5f, math::vec2{0.f}, math::vec2{1.f});
    result.distance = (math::half)d;
    result.angleA = (math::half)math::clamp(angleA/LS_TWO_PI, 0.f, 1.f);
    result.angleB = (math::half)math::clamp(angleB/LS_TWO_PI, 0.f, 1.f);
    result.angleC = (math::half)math::clamp(angleC/LS_TWO_PI, 0.f, 1.f);

    // Encode the radius' 15 bits in our reclaimed spare bits
    outTriData = encode_tri_radius(result, (math::half)r);
}



void test_tri_unpacking(PackedTriangle triData)
{
    // Decode the radius' 15 bits from our reclaimed spare bits
    const float r = (float)decode_tri_radius(triData);

    // decode the direction to our triangle's circumcenter
    const math::vec2&& sn = (math::vec2)triData.circumcenter * 2.f - 1.f;

    // decode the triangle's face normal
    const math::vec2&& m = (math::vec2)triData.normal * 2.f - 1.f;

    // decode the distance to the triangle's circumcenter
    float d = (float)triData.distance;

    // Decode the angles from the circumcenter's orthonormal basis to each
    // vertex.
    const float angleA = (float)triData.angleA * LS_TWO_PI;
    const float angleB = (float)triData.angleB * LS_TWO_PI;
    const float angleC = (float)triData.angleC * LS_TWO_PI;

    const math::vec3&& s = spheremap_norm_decode(sn) * d;
    const math::vec3&& n = spheremap_norm_decode(m);

    // Rebuild the orthonormal basis of our triangle using the same method
    // performed during encoding. This will give us a fairly accurate
    // reconstruction of each vertex.
    const math::mat3&& o = create_orthonormal_basis(n);
    const math::mat3&& v = axial_rotation_matrix(o, angleA, angleB, angleC);

    // Expand the vertices to their original positions
    const math::vec3&& a = (v[0] * r) + s;
    const math::vec3&& b = (v[1] * r) + s;
    const math::vec3&& c = (v[2] * r) + s;

    std::cout
        << "Out Triangle:"
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\tS: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tD:  " << d
        << "\n\tN: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tR:  " << r
        << "\n\ta:  " << angleA
        << "\n\tb:  " << angleB
        << "\n\tc:  " << angleC
        << '\n' << std::endl;
}



int main()
{
    /*
    test_tri_circumcenter();
    test_tri_incenter();
    */

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