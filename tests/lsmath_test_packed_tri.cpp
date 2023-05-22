/*
 * File:   lsmath_test_packed_tri.cpp
 * Author: hammy
 *
 * Created on Jan 12, 2023 at 6:22 PM
 */

#include <chrono>
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
    return math::vec2_cast(n) * math::inversesqrt(n[2] + n[2] + 2.f);
}



inline math::vec3 spheremap_norm_decode(const math::vec2& n) noexcept
{
    // Extrapolated from https://www.shadertoy.com/view/llfcRl
    float f = math::length_squared(n);
    return math::vec3_cast((n + n) * std::sqrt(1.f - f), 1.f - (f + f));
}



// Cosine/Sine approximation adapted from Demofox,
// https://www.shadertoy.com/view/XddSzH
inline LS_INLINE math::vec2 cos_sin(float x) noexcept
{
    #if defined(LS_X86_SSE)
    const __m128 absMask = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
    const __m128 c = _mm_set_ss(x);
    const __m128 s = _mm_sub_ss(c, _mm_set_ss(LS_PI_OVER_2));

    const __m128 x0 = _mm_unpacklo_ps(c, s);

    // This step is not necessary if x is between 0-1, corresponding to 0-360 degrees
    const __m128 x1 = _mm_mul_ps(x0, _mm_set1_ps(1.f / LS_TWO_PI));
    const __m128 x2Floor = _mm_floor_ps(_mm_add_ps(x1, _mm_set1_ps(0.25f)));

    const __m128 x2 = _mm_sub_ps(x1, _mm_add_ps(_mm_set1_ps(0.25f), x2Floor));

    const __m128 x3Abs = _mm_sub_ps(_mm_and_ps(absMask, x2), _mm_set1_ps(0.5f));
    const __m128 x3 = _mm_mul_ps(_mm_mul_ps(x2, _mm_set1_ps(16.f)), x3Abs);

    const __m128 x4Norm = _mm_mul_ps(x3, _mm_sub_ps(_mm_and_ps(absMask, x3), _mm_set1_ps(1.f)));

    #if defined(LS_X86_FMA)
        const __m128 x4 = _mm_fmadd_ps(_mm_set1_ps(0.225f), x4Norm, x3);
    #else
        const __m128 x4 = _mm_add_ps(_mm_mul_ps(_mm_set_ps(0.225f), x4Norm), x3);
    #endif

    math::vec2 result;
    _mm_storel_pd(reinterpret_cast<double*>(&result.v[0]), _mm_castpd_ps(x4));

    #else
        math::vec2 result{
            math::cos(x),
            math::sin(x)
        };

    #endif

    return result;
}



inline math::mat3 axial_rotation_matrix(const math::mat3& basis, float angleA, float angleB, float angleC) noexcept
{
    #if 1
        const math::vec2&& x = cos_sin(angleA);
        const math::vec2&& y = cos_sin(angleB);
        const math::vec2&& z = cos_sin(angleC);
    #else
        const math::vec2&& x = math::vec2{std::cos(angleA), std::sin(angleA)};
        const math::vec2&& y = math::vec2{std::cos(angleB), std::sin(angleB)};
        const math::vec2&& z = math::vec2{std::cos(angleC), std::sin(angleC)};
    #endif

    const math::vec2&& bx = math::vec2_cast(basis[0]);
    const math::vec2&& by = math::vec2_cast(basis[1]);
    const math::vec2&& bz = math::vec2_cast(basis[2]);

    // normalize?
    return math::mat3{
        math::vec3{math::dot(bx, x), math::dot(by, x), math::dot(bz, x)},
        math::vec3{math::dot(bx, y), math::dot(by, y), math::dot(bz, y)},
        math::vec3{math::dot(bx, z), math::dot(by, z), math::dot(bz, z)}
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



struct alignas(sizeof(uint64_t)*2) PackedTriangle
{
    math::vec2_t<math::half> circumcenter;
    math::vec2_t<math::half> normal;

    math::half distance;
    math::half angleA;
    math::half angleB;
    math::half angleC;
};

static_assert(sizeof(PackedTriangle) == sizeof(uint64_t)*2, "Invalid size of packed triangle structure.");



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

    #if !defined(LS_X86_BMI2)
        PackedTriangle result;
        result.circumcenter[0] = encode_2_bits_in_float<0>(tri.circumcenter[0], radius);
        result.circumcenter[1] = encode_2_bits_in_float<2>(tri.circumcenter[1], radius);
        result.normal[0]       = encode_2_bits_in_float<4>(tri.normal[0],       radius);
        result.normal[1]       = encode_2_bits_in_float<6>(tri.normal[1],       radius);
        result.angleA          = encode_2_bits_in_float<8>(tri.angleA,          radius);
        result.angleB          = encode_2_bits_in_float<10>(tri.angleB,         radius);
        result.angleC          = encode_2_bits_in_float<12>(tri.angleC,         radius);
        result.distance        = insert_sign_bit<14>(tri.distance,              radius);

    #else
        PackedTriangle result = tri;
        uint64_t* const outLoBits = reinterpret_cast<uint64_t*>(&result) + 0;
        uint64_t* const outHiBits = reinterpret_cast<uint64_t*>(&result) + 1;

        const uint64_t radBits    = (uint64_t)radius.bits;
        const uint64_t radLoBits  = _pdep_u64(radBits >> 0ull, 0xC000C000C000C000ull);
        const uint64_t radHiBits  = _pdep_u64(radBits >> 8ull, 0xC000C000C0000000ull);
        const uint64_t radSignBit = (radBits & 0x0000000000004000ull) << 1ull;

        *outLoBits |= radLoBits;
        *outHiBits |= radHiBits | radSignBit;
    #endif

    return result;
}



inline math::half decode_tri_radius(PackedTriangle& tri) noexcept
{
    math::half result{0};

    #if !defined(LS_X86_BMI2)
        result.bits |= decode_2_bits_in_float<0>(tri.circumcenter[0]);
        result.bits |= decode_2_bits_in_float<2>(tri.circumcenter[1]);
        result.bits |= decode_2_bits_in_float<4>(tri.normal[0]);
        result.bits |= decode_2_bits_in_float<6>(tri.normal[1]);
        result.bits |= decode_2_bits_in_float<8>(tri.angleA);
        result.bits |= decode_2_bits_in_float<10>(tri.angleB);
        result.bits |= decode_2_bits_in_float<12>(tri.angleC);
        result.bits |= extract_sign_bit<14>(tri.distance);

    #else
    {
        const uint64_t loBits    = (reinterpret_cast<const uint64_t*>(&tri))[0];
        const uint64_t hiBits    = (reinterpret_cast<const uint64_t*>(&tri))[1];
        const uint64_t bits_0_7  = _pext_u64(loBits, 0xC000C000C000C000ull) << 0ull;
        const uint64_t bits_8_14 = _pext_u64(hiBits, 0xC000C000C0000000ull) << 8ull;
        const uint64_t bit15     = (hiBits & 0x0000000000008000ull) >> 1ull;
        result.bits = bit15 | bits_8_14 | bits_0_7;
    }
    #endif

    // Leaving this commented-out to see what's actually happening with the
    // bitmasks.
    #if 0
        // Reset the highest 2 bits of each IEEE half-float
        tri.circumcenter[0].bits &= 0x3FFF;
        tri.circumcenter[1].bits &= 0x3FFF;
        tri.normal[0].bits &= 0x3FFF;
        tri.normal[1].bits &= 0x3FFF;
        tri.angleA.bits &= 0x3FFF;
        tri.angleB.bits &= 0x3FFF;
        tri.angleC.bits &= 0x3FFF;
        tri.distance.bits &= 0x7FFF; // only reset the sign bit here

    #else
    {
        uint64_t* loBits = (reinterpret_cast<uint64_t*>(&tri)) + 0;
        uint64_t* hiBits = (reinterpret_cast<uint64_t*>(&tri)) + 1;
        constexpr uint64_t loMask = 0x3FFF3FFF3FFF3FFFull; // Reset the highest 2 bits of each IEEE half-float
        constexpr uint64_t hiMask = 0x3FFF3FFF3FFF7FFFull; // but only reset the lowest sign bit here (for 15 total bits)

        *loBits &= loMask;
        *hiBits &= hiMask;
    }
    #endif

    return result;
}



void test_tri_packing(const math::vec3& a, const math::vec3& b, const math::vec3& c, PackedTriangle& outTriData)
{
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
    float angleA = -math::atan2(math::dot(math::cross(right, as), n), math::dot(as, right));
    float angleB = -math::atan2(math::dot(math::cross(right, bs), n), math::dot(bs, right));
    float angleC = -math::atan2(math::dot(math::cross(right, cs), n), math::dot(cs, right));

    // Ensure all angles are greater than 0 (see below for reasoning) and less
    // than or equal to 1. This way we ensure two bits in each angle variable
    // are available by exploiting the IEEE data format.
    if (angleA < 0.f) { angleA += LS_TWO_PI; }
    if (angleB < 0.f) { angleB += LS_TWO_PI; }
    if (angleC < 0.f) { angleC += LS_TWO_PI; }

    angleA /= LS_TWO_PI;
    angleB /= LS_TWO_PI;
    angleC /= LS_TWO_PI;

    // Debug
    /*
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
    */

    // Force all values to be within the range of (0, 1), with the exception of
    // the distance to our triangle's circumcenter. Because all 8 values are
    // IEEE 16-bit half-precision floats we can exploit the highest 2 bits* of
    // each variable (for a total of 15 reclaimed bits) to encode the
    // circumcenter's radius without the explicit need for extra storage.
    //
    // *The circumcenter's distance is unbounded above zero, so we may only use
    // the sign-bit. This is fine as the radius is always positive and only
    // needs 15 bits to be stored correctly.
    PackedTriangle result = {
        (math::vec2_t<math::half>)math::clamp(sh * 0.5f + 0.5f, math::vec2{0.f}, math::vec2{1.f}),
        (math::vec2_t<math::half>)math::clamp(m  * 0.5f + 0.5f, math::vec2{0.f}, math::vec2{1.f}),
        (math::half)d,
        (math::half)math::clamp(angleA, 0.f, 1.f),
        (math::half)math::clamp(angleB, 0.f, 1.f),
        (math::half)math::clamp(angleC, 0.f, 1.f)
    };

    // Encode the radius' 15 bits in our reclaimed spare bits
    outTriData = encode_tri_radius(result, (math::half)r);
}



void test_tri_unpacking(PackedTriangle triData, math::vec3& a, math::vec3& b, math::vec3& c)
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
    // vertex. All angles are between 0 - 1, corresponding to 0 - 2pi
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
    a = (v[0] * r) + s;
    b = (v[1] * r) + s;
    c = (v[2] * r) + s;

    // Debug
    /*
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
    */
}



int main()
{
    test_tri_circumcenter();
    test_tri_incenter();

    typedef std::chrono::system_clock::time_point system_time_point;
    typedef std::chrono::duration<long double, std::milli> system_duration;

    math::vec3 a = {5.75f, 6.9f, 4.25f};
    math::vec3 b = {13.77f, 8.96f, 2.7f};
    math::vec3 c = {1.234f, -3.12f, -1.1f};

    std::cout
        << "In Triangle:"
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << std::endl;

    std::cout << "Benchmarking triangle packing..." << std::endl;
    system_duration execTime{0};
    PackedTriangle triData{};
    math::vec3 x;
    math::vec3 y;
    math::vec3 z;

    for (unsigned i = 0; i < 10000000u; ++i)
    {
        x = a;
        y = b;
        z = c;

        const system_time_point&& startTime = std::chrono::system_clock::now();

        test_tri_packing(x, y, z, triData);
        test_tri_unpacking(triData, x, y, z);

        execTime += system_duration{std::chrono::system_clock::now() - startTime};
    }
    std::cout << "\tDone. Test completed in " << execTime.count() << "ms." << std::endl;

    a = x;
    b = y;
    c = z;

    std::cout
        << "Out Triangle:"
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << std::endl;

    return 0;
}