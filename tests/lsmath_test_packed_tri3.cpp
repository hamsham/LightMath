/*
 * File:   lsmath_test_packed_tri3.cpp
 * Author: hammy
 *
 * Created on Jul 22, 2023 at 6:22 PM
 */

#include <chrono>
#include <iostream>

#include "lightsky/math/mat_utils.h"
#include "lightsky/math/vec_utils.h"
#include "lightsky/math/quat_utils.h"

// Control accuracy vs performance with quaternions vs rotation matrices
#ifndef TRI_PACK_NORMALIZE_ROTATIONS
    #define TRI_PACK_NORMALIZE_ROTATIONS 0
#endif

namespace math = ls::math;



/*-----------------------------------------------------------------------------
 * Packed Triangle Structure
-----------------------------------------------------------------------------*/
struct alignas(alignof(uint64_t)*2) PackedTriangle
{
    math::half distance;
    math::vec2_t<math::half> circumcenter;

    math::vec2_t<math::half> normal;
    math::half angleA;
    math::half angleB;
    math::half angleC;
};

static_assert(sizeof(PackedTriangle) == sizeof(uint64_t)*2, "Invalid size of packed triangle structure.");



/*-----------------------------------------------------------------------------
 * Bit Packing Operations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Place 2 bits into the least-significant bits of a half-float
-------------------------------------*/
template <uint16_t numShifts>
inline math::half encode_2_bits_in_float(math::half f, math::half bits) noexcept
{
    uint16_t maskedBits = bits.bits & (0x0003u << numShifts);
    f.bits |= maskedBits << (14-numShifts);
    return f;
}



/*-------------------------------------
 * Extract 2 bits from the least-significant bits of a half-float
-------------------------------------*/
template <uint16_t numShifts>
inline uint16_t decode_2_bits_in_float(const math::half f) noexcept
{
    uint16_t maskedBits = (f.bits & 0xC000) >> (14-numShifts);
    return maskedBits;
}



/*-------------------------------------
 * Place a bit into the sign bits of a half-float
-------------------------------------*/
template <uint16_t bitPos>
inline uint16_t extract_sign_bit(math::half f) noexcept
{
    uint16_t bit = f.bits & 0x8000;
    return bit >> (15-bitPos);
}



/*-------------------------------------
 * Extract a bit from the sign bits of a half-float
-------------------------------------*/
template <uint16_t bitPos>
inline math::half insert_sign_bit(math::half f, math::half bits) noexcept
{
    uint16_t bit = (bits.bits & (1 << bitPos));
    f.bits |= bit << (15-bitPos);
    return f;
}


/*-------------------------------------
 * Encode a 15-bit half-float within unused bits of 8 half-floats
-------------------------------------*/
inline PackedTriangle encode_tri_radius(const PackedTriangle& tri, const math::half& radius) noexcept
{
    // exploit the spare 2 bits of each of the 7 input variables, plus sign bit
    // of the circumcenter's distance from origin, for a total of 15 spare bits

    #if !defined(LS_X86_BMI2)
        PackedTriangle result;
        result.distance        = insert_sign_bit<0>(tri.distance,               radius);
        result.circumcenter[0] = encode_2_bits_in_float<1>(tri.circumcenter[0], radius);
        result.circumcenter[1] = encode_2_bits_in_float<3>(tri.circumcenter[1], radius);
        result.normal[0]       = encode_2_bits_in_float<5>(tri.normal[0],       radius);
        result.normal[1]       = encode_2_bits_in_float<7>(tri.normal[1],       radius);
        result.angleA          = encode_2_bits_in_float<9>(tri.angleA,          radius);
        result.angleB          = encode_2_bits_in_float<11>(tri.angleB,         radius);
        result.angleC          = encode_2_bits_in_float<13>(tri.angleC,         radius);

    #else
        PackedTriangle result = tri;
        uint64_t* const outLoBits = reinterpret_cast<uint64_t*>(&result) + 0;
        uint64_t* const outHiBits = reinterpret_cast<uint64_t*>(&result) + 1;

        const uint64_t radBits    = (uint64_t)radius.bits;
        const uint64_t radLoBits  = _pdep_u64(radBits >> 0ull, 0xC000C000C0008000ull);
        const uint64_t radHiBits  = _pdep_u64(radBits >> 7ull, 0xC000C000C000C000ull);

        *outLoBits |= radLoBits;
        *outHiBits |= radHiBits;
    #endif

    return result;
}



/*-------------------------------------
 * Decode a 15-bit half-float from the unused bits of 8 half-floats
-------------------------------------*/
inline math::half decode_tri_radius(PackedTriangle& tri) noexcept
{
    math::half result{0};

    #if !defined(LS_X86_BMI2)
        result.bits |= extract_sign_bit<0>(tri.distance);
        result.bits |= decode_2_bits_in_float<1>(tri.circumcenter[0]);
        result.bits |= decode_2_bits_in_float<3>(tri.circumcenter[1]);
        result.bits |= decode_2_bits_in_float<5>(tri.normal[0]);
        result.bits |= decode_2_bits_in_float<7>(tri.normal[1]);
        result.bits |= decode_2_bits_in_float<9>(tri.angleA);
        result.bits |= decode_2_bits_in_float<11>(tri.angleB);
        result.bits |= decode_2_bits_in_float<13>(tri.angleC);

    #else
    {
        const uint64_t loBits    = (reinterpret_cast<const uint64_t*>(&tri))[0];
        const uint64_t hiBits    = (reinterpret_cast<const uint64_t*>(&tri))[1];
        const uint64_t bits_0_7  = _pext_u64(loBits, 0xC000C000C0008000ull) << 0ull;
        const uint64_t bits_8_15 = _pext_u64(hiBits, 0xC000C000C000C000ull) << 7ull;
        result.bits = bits_8_15 | bits_0_7;
    }
    #endif

    // Leaving this commented-out to see what's actually happening with the
    // bitmasks.
    #if 0
        // Reset the highest 2 bits of each IEEE half-float
        tri.distance.bits        &= 0x7FFF; // only reset the sign bit here
        tri.circumcenter[0].bits &= 0x3FFF;
        tri.circumcenter[1].bits &= 0x3FFF;
        tri.normal[0].bits       &= 0x3FFF;
        tri.normal[1].bits       &= 0x3FFF;
        tri.angleA.bits          &= 0x3FFF;
        tri.angleB.bits          &= 0x3FFF;
        tri.angleC.bits          &= 0x3FFF;

    #else
    {
        uint64_t* loBits = (reinterpret_cast<uint64_t*>(&tri)) + 0;
        uint64_t* hiBits = (reinterpret_cast<uint64_t*>(&tri)) + 1;

        // Reset the highest 2 bits of each IEEE half-float, but only reset the
        // lowest sign bit if PackedTriangle::distance (for 15 total bits).
        constexpr uint64_t loMask = 0x3FFF3FFF3FFF7FFFull;
        constexpr uint64_t hiMask = 0x3FFF3FFF3FFF3FFFull;

        *loBits &= loMask;
        *hiBits &= hiMask;
    }
    #endif

    return result;
}



/*-----------------------------------------------------------------------------
 * Triangle Attributes
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Triangle Circumcenter
-------------------------------------*/
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



/*-------------------------------------
 * Triangle Incenter
-------------------------------------*/
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



/*-----------------------------------------------------------------------------
 * Normal Vector Representation
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Spheremap Encoding (3D -> 2D)
-------------------------------------*/
inline math::vec2 spheremap_norm_encode(const math::vec3& n) noexcept
{
    // Extrapolated from https://www.shadertoy.com/view/llfcRl
    return math::vec2_cast(n) / std::sqrt((n[2]+n[2]) + 2.f);
    //return math::vec2_cast(n) * math::inversesqrt(n[2] + n[2] + 2.f);
}



/*-------------------------------------
 * Spheremap Decoding (2D -> 3D)
-------------------------------------*/
inline math::vec3 spheremap_norm_decode(const math::vec2& n) noexcept
{
    // Extrapolated from https://www.shadertoy.com/view/llfcRl
    float f = math::length_squared(n);
    return math::vec3_cast((n + n) * std::sqrt(1.f - f), 1.f - (f + f));
}



/*-----------------------------------------------------------------------------
 * Coordinate Systems & Rotations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Combined Cosine+Sine Approximation
-------------------------------------*/
// Cosine/Sine approximation adapted from Demofox,
// https://www.shadertoy.com/view/XddSzH
//
// New version by milianw:
// https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b/28050328#28050328
//
// Note: This function expects the input angle to be between 0 and 1,
// representing an angle bewteen 0 and 2pi.
inline LS_INLINE math::vec2 cos_sin(float x) noexcept
{
    math::vec2 sc{x, x - 0.25f};
    sc -= math::floor(sc + 0.25f) + 0.25f;
    sc *= (math::abs(sc) - 0.5f) * 16.f;
    return sc + ((math::abs(sc) - 1.f) * sc * 0.225f);
}



/*-------------------------------------
 * cos(atan2(theta) / 2)
-------------------------------------*/
inline float cos_atan2(float y, float x) noexcept
{
    #if TRI_PACK_NORMALIZE_ROTATIONS != 0
        const math::vec2&& point = math::normalize(math::vec2{x, y});
        x = point[0];
        y = point[1];
    #endif

    const float sign = y < 0.f ? -1.f : 1.f;
    const float x2 = x*x;
    const float y2 = y*y;
    const float l2 = x2+y2;
    const float z = std::sqrt(l2) + x;
    return sign * math::inversesqrt(1.f + (y2 * math::rcp(z*z)));
}



/*-------------------------------------
 * Generate an Orthonormal Basis from a Normal Vector
-------------------------------------*/
inline LS_INLINE math::mat3 create_orthonormal_basis(const math::vec3& n) noexcept
{
    const float sign = math::copysign(1.f, n[2]);
    const float a = -1.f / (sign+n[2]);
    const float b = n[0] * n[1] * a;

    return math::mat3{
        math::normalize(math::vec3{1.f + sign * (n[0] * n[0]) * a, sign * b, -sign * n[0]}),
        math::normalize(-math::vec3{b, sign + (n[1] * n[1]) * a, -n[1]}),
        n * -sign
    };
}



/*-------------------------------------
 * Generate an Orthonormal Basis' X-direction from a Normal Vector
-------------------------------------*/
inline LS_INLINE math::vec3 create_orthonormal_basis_x(const math::vec3& n) noexcept
{
    const float sign = math::copysign(1.f, n[2]);
    const float a = -sign * math::rcp(sign+n[2]);
    const float b = (n[0] * n[1]) * a;

    return math::normalize(math::vec3{1.f + (n[0] * n[0]) * a, b, -sign * n[0]});
}



/*-------------------------------------
 * Packed Triangle Decoding
-------------------------------------*/
inline LS_INLINE math::mat3 rotate_axes_quaternion(const math::vec3& n, float angleA, float angleB, float angleC) noexcept
{
    const math::vec3&& basisX = create_orthonormal_basis_x(n);
    const float sinA = std::sqrt(1.f - angleA*angleA);
    const float sinB = std::sqrt(1.f - angleB*angleB);
    const float sinC = std::sqrt(1.f - angleC*angleC);

    const math::quat&& basisA = math::quat_cast(n*sinA, angleA);
    const math::quat&& basisB = math::quat_cast(n*sinB, angleB);
    const math::quat&& basisC = math::quat_cast(n*sinC, angleC);

    return math::mat3{
        math::rotate(basisX, basisA),
        math::rotate(basisX, basisB),
        math::rotate(basisX, basisC)
    };
}



/*-----------------------------------------------------------------------------
 * Triangle Packing/Unpacking
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Packed Triangle Encoding
-------------------------------------*/
void test_tri_packing(const math::vec3& a, const math::vec3& b, const math::vec3& c, PackedTriangle& outTriData) noexcept
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

    // Generate an orthonormal basis using the revised Frisvad method from Duff
    // et. al:
    // https://jcgt.org/published/0006/01/01/
    const math::vec3&& basisX = create_orthonormal_basis_x(n);
    const math::vec2&& m = spheremap_norm_encode(n);

    // Retrieve the angles to each vertex along the triangle's plane using our
    // orthonormal basis.
    float angleA, angleB, angleC;
    {
        const math::vec3&& axx = math::cross(basisX, as);
        const math::vec3&& bxx = math::cross(basisX, bs);
        const math::vec3&& cxx = math::cross(basisX, cs);

        const float axn = math::dot(axx, n);
        const float bxn = math::dot(bxx, n);
        const float cxn = math::dot(cxx, n);

        const float adx = math::dot(basisX, as);
        const float bdx = math::dot(basisX, bs);
        const float cdx = math::dot(basisX, cs);

        angleA = cos_atan2(axn, adx);
        angleB = cos_atan2(bxn, bdx);
        angleC = cos_atan2(cxn, cdx);
    }

    // Force all values to be within the range of (0, 1), except for the
    // distance to our triangle's circumcenter. Because all 8 values are IEEE
    // 16-bit half-precision floats we can exploit the highest 2 bits* of each
    // variable (for a total of 15 reclaimed bits) to encode the circumcenter's
    // radius without the explicit need for extra storage.
    //
    // *The circumcenter's distance is unbounded above zero, so we may only use
    // the sign-bit. This is fine as the radius is always positive and only
    // needs 15 bits to be stored correctly.
    PackedTriangle result = {
        (math::half)d,
        (math::vec2_t<math::half>)math::saturate(sh * 0.5f + 0.5f),
        (math::vec2_t<math::half>)math::saturate(m  * 0.5f + 0.5f),
        (math::half)math::saturate(angleA * 0.5f + 0.5f),
        (math::half)math::saturate(angleB * 0.5f + 0.5f),
        (math::half)math::saturate(angleC * 0.5f + 0.5f)
    };

    // Encode the radius' 15 bits in our reclaimed spare bits
    outTriData = encode_tri_radius(result, (math::half)r);
}

void test_tri_unpacking(PackedTriangle triData, math::vec3& a, math::vec3& b, math::vec3& c) noexcept
{
    // Decode the radius' 15 bits from our reclaimed spare bits
    const float r = (float)decode_tri_radius(triData);

    // decode the distance to the triangle's circumcenter
    const float d = (float)triData.distance;

    // decode the direction to our triangle's circumcenter
    const math::vec2&& sn = (math::vec2)triData.circumcenter * 2.f - 1.f;

    // decode the triangle's face normal
    const math::vec2&& m = (math::vec2)triData.normal * 2.f - 1.f;

    const math::vec3&& s = spheremap_norm_decode(sn) * d;
    const math::vec3&& n = spheremap_norm_decode(m);

    // Decode the angles from the circumcenter's orthonormal basis to each
    // vertex. All angles are between 0 - 1, corresponding to 0 - 2pi
    const float angleA = (float)triData.angleA * 2.f - 1.f;
    const float angleB = (float)triData.angleB * 2.f - 1.f;
    const float angleC = (float)triData.angleC * 2.f - 1.f;

    // Rebuild the orthonormal basis of our triangle using the same method
    // performed during encoding. This will give us a fairly accurate
    // reconstruction of each vertex.
    math::mat3&& v = rotate_axes_quaternion(n, angleA, angleB, angleC);

    #if TRI_PACK_NORMALIZE_ROTATIONS
        v[0] = math::normalize(v[0]);
        v[1] = math::normalize(v[1]);
        v[2] = math::normalize(v[2]);
    #endif

    // Expand the vertices to their original positions
    a = v[0] * r + s;
    b = v[1] * r + s;
    c = v[2] * r + s;
}



/*-----------------------------------------------------------------------------
 * Functional Tests
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Calculate the average of a group of numbers
-------------------------------------*/
template <typename T, typename... U>
constexpr T average(U... values) noexcept
{
    return math::sum<U...>(values...) / (T)sizeof...(U);
}



/*-------------------------------------
 * Calculate the relative error between two variables
-------------------------------------*/
constexpr float calc_relative_error(float x, float y) noexcept
{
    return ls::math::abs<float>(x - y) / ls::math::abs<float>(x);
}



/*-------------------------------------
 * Triangle Circumcenter Validation
-------------------------------------*/
void test_tri_circumcenter(const math::vec3& a, const math::vec3 b, const math::vec3& c)
{
    math::vec3 s, n;
    float r = circumcenter(a, b, c, s, n);

    std::cout
        << "Circumcenter:"
        << "\n\tV0:     {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tV1:     {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tV2:     {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\n\tCenter: {" << s[0] << ", " << s[1] << ", " << s[2] << '}'
        << "\n\tNormal: {" << n[0] << ", " << n[1] << ", " << n[2] << '}'
        << "\n\tRadius: " << r
        << '\n' << std::endl;
}



/*-------------------------------------
 * Triangle Incenter Validation
-------------------------------------*/
void test_tri_incenter(const math::vec3& a, const math::vec3 b, const math::vec3& c)
{
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



/*-------------------------------------
 * Packed Triangle Validation
-------------------------------------*/
void test_tri_packing(const math::vec3& a, const math::vec3 b, const math::vec3& c)
{
    PackedTriangle triData{};
    math::vec3 x = a;
    math::vec3 y = b;
    math::vec3 z = c;

    test_tri_packing(x, y, z, triData);
    test_tri_unpacking(triData, x, y, z);

    float errA = average<float>(calc_relative_error(a[0], x[0]), calc_relative_error(a[1], x[1]), calc_relative_error(a[2], x[2])) * 100.f;
    float errB = average<float>(calc_relative_error(b[0], y[0]), calc_relative_error(b[1], y[1]), calc_relative_error(b[2], y[2])) * 100.f;
    float errC = average<float>(calc_relative_error(c[0], z[0]), calc_relative_error(c[1], z[1]), calc_relative_error(c[2], z[2])) * 100.f;

    std::cout
        << "Triangle Packing:"
        << "\nIn Triangle:"
        << "\n\tA: {" << a[0] << ", " << a[1] << ", " << a[2] << '}'
        << "\n\tB: {" << b[0] << ", " << b[1] << ", " << b[2] << '}'
        << "\n\tC: {" << c[0] << ", " << c[1] << ", " << c[2] << '}'
        << "\nOut Triangle:"
        << "\n\tA: {" << x[0] << ", " << x[1] << ", " << x[2] << '}'
        << "\n\tB: {" << y[0] << ", " << y[1] << ", " << y[2] << '}'
        << "\n\tC: {" << z[0] << ", " << z[1] << ", " << z[2] << '}'
        << "\n\tAverage Error: {" << errA << ", " << errB << ", " << errC << '}'
        << '\n' << std::endl;
}



/*-----------------------------------------------------------------------------
 * Benchmarks
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Packed Triangle Benchmark
-------------------------------------*/
void benchmark_tri_packing(const math::vec3& a, const math::vec3 b, const math::vec3& c)
{
    typedef std::chrono::system_clock::time_point system_time_point;
    typedef std::chrono::duration<long double, std::milli> system_duration;

    std::cout << "Benchmarking triangle packing..." << std::endl;
    PackedTriangle triData{};
    math::vec3 x;
    math::vec3 y;
    math::vec3 z;

    const system_time_point&& startTime = std::chrono::system_clock::now();
    for (unsigned i = 0; i < 10000000u; ++i)
    {
        x = a;
        y = b;
        z = c;

        test_tri_packing(x, y, z, triData);
        test_tri_unpacking(triData, x, y, z);
    }

    const system_duration&& execTime = system_duration{std::chrono::system_clock::now() - startTime};
    std::cout << "\tDone. Test completed in " << execTime.count() << "ms." << std::endl;
}



/*-----------------------------------------------------------------------------
 * Main()
-----------------------------------------------------------------------------*/
int main()
{
    constexpr math::vec3 a{5.75f, 6.9f, 4.25f};
    constexpr math::vec3 b{13.77f, 8.96f, 2.7f};
    constexpr math::vec3 c{1.234f, -3.12f, -1.1f};
    test_tri_circumcenter(a, b, c);
    test_tri_incenter(a, b, c);

    test_tri_packing(a, b, c);

    test_tri_packing(
        math::vec3{2.f, 0.f, 0.f} + math::vec3{0.25f, 0.6f,   0.8f},
        math::vec3{0.f, 2.f, 0.f} + math::vec3{0.4f,  0.125f, 0.2f},
        math::vec3{0.f, 0.f, 2.f} + math::vec3{1.f,   0.f,    1.f}
    );

    // benchmark after validation test since some instructions might have been
    // placed into the CPU's instruction cache (found a 150ms performance win)
    benchmark_tri_packing(a, b, c);

    return 0;
}
