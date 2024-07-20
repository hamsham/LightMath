
#ifndef LS_MATH_VEC_UTILS_IMPL_H
#define LS_MATH_VEC_UTILS_IMPL_H

#include <type_traits>

#include "lightsky/setup/Api.h" // LS_INLINE



namespace ls
{

/*-----------------------------------------------------------------------------
    2D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    2D Sum
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::sum(const vec2_t <num_t>& v) noexcept
{
    return v.v[0] + v.v[1];
}

/*-------------------------------------
    2D Reciprocal Sum
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::sum_inv(const vec2_t <num_t>& v) noexcept
{
    return math::rcp<num_t>(v.v[0] + v.v[1]);
}

/*-------------------------------------
    2D Dot
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::dot(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2) noexcept
{
    return math::sum<num_t>(v1 * v2);
}

/*-------------------------------------
    2D Cross
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::cross(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2) noexcept
{
    return (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0]);
}

/*-------------------------------------
    2D Normalize
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec2_t<num_t> math::normalize(const vec2_t <num_t>& v) noexcept
{
    //return v * inversesqrt(math::length_squared<num_t>(v));
    const math::vec2_t<num_t>&& temp = v * v;
    return v / std::sqrt(math::sum<num_t>(temp));
}

/*-------------------------------------
    2D Magnitude (squared)
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::length_squared(const vec2_t <num_t>& v) noexcept
{
    return math::sum<num_t>(v * v);
}

/*-------------------------------------
    2D Magnitude
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::length(const vec2_t <num_t>& v) noexcept
{
    return std::sqrt(math::length_squared<num_t>(v));
}

/*-------------------------------------
    2D Rotate
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec2_t<num_t> math::rotate(const vec2_t <num_t>& v, num_t angle) noexcept
{
    const num_t s = std::sin(angle);
    const num_t c = std::cos(angle);

    return vec2_t<num_t>((v.v[0] * c) - (v.v[1] * s), (v.v[0] * s) + (v.v[1] * c));
}

/*-------------------------------------
    2D Angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::angle_between(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2) noexcept
{
    return (num_t)math::acos(
        math::dot(v1, v2) / (math::length<num_t>(v1) * math::length<num_t>(v2))
    );
}

/*-------------------------------------
    2D Angle (with origin)
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::angle_between(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2, const vec2_t <num_t>& origin) noexcept
{
    return (num_t)math::acos(
        math::dot(v1 - origin, v2 - origin) / (math::length<num_t>(v1) * math::length<num_t>(v2))
    );
}

/*-------------------------------------
    2D Min
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::min(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2) noexcept
{
    return math::vec2_t<num_t>{
        math::min<num_t>(v1.v[0], v2.v[0]),
        math::min<num_t>(v1.v[1], v2.v[1])
    };
}

/*-------------------------------------
    2D Mix
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::mix(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2, num_t percent) noexcept
{
    return vec2_t < num_t > {v1 + ((v2 - v1) * percent)};
}

/*-------------------------------------
    2D Max
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::max(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2) noexcept
{
    return math::vec2_t<num_t>{
        math::max<num_t>(v1.v[0], v2.v[0]),
        math::max<num_t>(v1.v[1], v2.v[1])
    };
}

/*-------------------------------------
    2D Clamp
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::clamp(const vec2_t<num_t>& v, const vec2_t<num_t>& minVals, const vec2_t<num_t>& maxVals) noexcept
{
    return math::vec2_t<num_t>{
        math::clamp<num_t>(v.v[0], minVals.v[0], maxVals.v[0]),
        math::clamp<num_t>(v.v[1], minVals.v[1], maxVals.v[1])
    };
}

/*-------------------------------------
    2D Saturate
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::saturate(const vec2_t<num_t>& v) noexcept
{
    return math::vec2_t<num_t>{
        math::saturate<num_t>(v.v[0]),
        math::saturate<num_t>(v.v[1])
    };
}

/*-------------------------------------
    2D Projection
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec2_t<num_t> math::project(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2) noexcept
{
    const num_t v1Len = math::length<num_t>(v1);
    const num_t v2Len = math::length<num_t>(v2);

    const math::vec2_t<num_t>&& v1Norm = v1 / v1Len;
    const math::vec2_t<num_t>&& v2Norm = v2 / v2Len;

    const num_t cosTheta = math::dot(v1Norm, v2Norm);

    return v2Norm * cosTheta * v1Len;
}

/*-------------------------------------
    2D Reflection
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::reflect(const vec2_t <num_t>& v, const vec2_t <num_t>& norm) noexcept
{
    /*
    const math::vec2_t<num_t>&& nv = math::normalize<num_t>(v);

    const math::vec2_t<num_t>&& bounce = norm * (math::dot(nv, norm) * num_t {2});
    return bounce - nv;
    */
    return v - math::vec2_t<num_t>{2} * math::dot(v, norm) * norm;
}

/*-------------------------------------
    2D Mid
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::mid(const vec2_t <num_t>& v1, const vec2_t <num_t>& v2) noexcept
{
    return std::is_integral<num_t>::value
           ? ((v1 + v2) / num_t{2})
           : ((v1 + v2) * num_t{0.5});
}

/*-------------------------------------
    2D Step
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::step(const vec2_t <num_t>& edge, const vec2_t <num_t>& v) noexcept
{
    return math::vec2_t<num_t>{
        v.v[0] < edge.v[0] ? num_t{0} : num_t{1},
        v.v[1] < edge.v[1] ? num_t{0} : num_t{1}
    };
}

/*-------------------------------------
    2D Smoothstep
-------------------------------------*/
template<typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::smoothstep(const vec2_t<num_t>& a, const vec2_t<num_t>& b, const vec2_t<num_t>& x) noexcept
{
    return math::vec2_t<num_t>{
        math::smoothstep<num_t>(a.v[0], b.v[0], x.v[0]),
        math::smoothstep<num_t>(a.v[1], b.v[1], x.v[1])
    };
}

/*-------------------------------------
    2D RCP
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::rcp(const vec2_t <num_t>& v) noexcept
{
    return vec2_t < num_t > {
        ls::math::rcp(v.v[0]),
        ls::math::rcp(v.v[1])
    };
}

/*-------------------------------------
    2D Sign Bits
-------------------------------------*/
template <typename N> constexpr LS_INLINE
int math::sign_mask(const vec2_t <N>& x) noexcept
{
    return math::sign_mask(x.v[0]) | (math::sign_mask(x.v[1]) << 1);
}

/*-------------------------------------
    2D Signs
-------------------------------------*/
template <typename N> constexpr LS_INLINE
math::vec2_t<N> math::sign(const vec2_t <N>& x) noexcept
{
    return vec2_t < N > {
        math::sign(x.v[0]),
        math::sign(x.v[1])
    };
}

/*-------------------------------------
    2D floor
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::floor(const vec2_t <num_t>& v) noexcept
{
    return vec2_t < num_t > {
        ls::math::floor(v.v[0]),
        ls::math::floor(v.v[1])
    };
}

/*-------------------------------------
    2D ceil
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::ceil(const vec2_t <num_t>& v) noexcept
{
    return vec2_t < num_t > {
        ls::math::ceil(v.v[0]),
        ls::math::ceil(v.v[1])
    };
}

/*-------------------------------------
    2D round
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::round(const vec2_t <num_t>& v) noexcept
{
    return vec2_t < num_t > {
        ls::math::round(v.v[0]),
        ls::math::round(v.v[1])
    };
}

/*-------------------------------------
    2D abs
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec2_t<num_t> math::abs(const vec2_t <num_t>& v) noexcept
{
    return vec2_t < num_t > {
        ls::math::abs(v.v[0]),
        ls::math::abs(v.v[1])
    };
}

/*-------------------------------------
    log2
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec2_t<num_t> math::log2(const math::vec2_t<num_t>& n) noexcept
{
    return math::vec2_t<num_t>{
        (num_t)math::log2<float>((float)n.v[0]),
        (num_t)math::log2<float>((float)n.v[1])
    };
}

/*-------------------------------------
    log
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec2_t<num_t> math::log(const math::vec2_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) * 0.693147181f; // ln( 2 )
}

/*-------------------------------------
    log10
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec2_t<num_t> math::log10(const math::vec2_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) * 0.3010299956639812f; // 1.0 / log2( 10 )
}

/*-------------------------------------
    logN
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec2_t<num_t> math::logN(const math::vec2_t<num_t>& baseN, const math::vec2_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) / log2 < num_t > (baseN);
}

/*-------------------------------------
    pow
-------------------------------------*/
namespace math
{
namespace impl
{
template <typename num_t>
constexpr num_t powi_impl(const math::vec2_t<num_t>& p, const math::vec2_t<num_t>& y, const math::vec2_t<num_t>& result) noexcept
{
    return (y < math::vec2_t<num_t>{1}) ? result : math::impl::powi_impl<num_t>(p * p, y >> math::vec2_t<num_t>{2}, (y & math::vec2_t<num_t>{1}) ? (result * p) : result);
}
} // end impl namespace
} // end math namespace

template <typename num_t>
constexpr LS_INLINE math::vec2_t<num_t> math::pow(
    const typename setup::EnableIf<setup::IsIntegral<num_t>::value, math::vec2_t<num_t>>::type& x,
    const typename setup::EnableIf<setup::IsIntegral<num_t>::value, math::vec2_t<num_t>>::type& y) noexcept
{
    return math::impl::powi_impl<num_t>(x, y, math::vec2_t<num_t>{1});
}

template <typename num_t>
inline LS_INLINE math::vec2_t<num_t> math::pow(const math::vec2_t<num_t>& x, const math::vec2_t<num_t>& y) noexcept
{
    return math::exp<num_t>(math::log<num_t>(x) * y);
}

/*-------------------------------------
    exp
-------------------------------------*/
template <typename num_t>
inline LS_INLINE math::vec2_t<num_t> math::exp(math::vec2_t<num_t> x) noexcept
{
    x = math::vec2_t<num_t>{1.f} + x / math::vec2_t<num_t>{256.f};
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
}

/*-------------------------------------
    exp2
-------------------------------------*/
template <typename num_t>
inline LS_INLINE math::vec2_t<num_t> math::exp2(math::vec2_t<num_t> x) noexcept
{
    x = math::vec2_t<num_t>{1.f} + x * math::vec2_t<num_t>{num_t{0.002707606174}}; // ln(2)/256
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
}

/*-------------------------------------
    FMA
-------------------------------------*/
template <typename num_t>
constexpr LS_INLINE math::vec2_t<num_t> math::fmadd(const vec2_t <num_t>& x, const vec2_t <num_t>& m, const vec2_t <num_t>& a) noexcept
{
    return (x * m) + a;
}

/*-------------------------------------
    FMS
-------------------------------------*/
template <typename num_t>
constexpr LS_INLINE math::vec2_t<num_t> math::fmsub(const vec2_t <num_t>& x, const vec2_t <num_t>& m, const vec2_t <num_t>& a) noexcept
{
    return (x * m) - a;
}



/*-----------------------------------------------------------------------------
    3D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    3D Sum
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::sum(const vec3_t <num_t>& v) noexcept
{
    return v.v[0] + v.v[1] + v.v[2];
}

/*-------------------------------------
    3D Reciprocal Sum
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::sum_inv(const vec3_t <num_t>& v) noexcept
{
    return math::rcp<num_t>(v.v[0] + v.v[1] + v.v[2]);
}

/*-------------------------------------
    3D Dot
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::dot(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2) noexcept
{
    return math::sum<num_t>(v1 * v2);
}

/*-------------------------------------
    3D Cross
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::cross(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2) noexcept
{
    return vec3_t < num_t > {
        (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]),
        (v1.v[2] * v2.v[0]) - (v1.v[0] * v2.v[2]),
        (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0])
    };
}

/*-------------------------------------
    3D Normalize
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::normalize(const vec3_t <num_t>& v) noexcept
{
    //return v * inversesqrt(math::length_squared<num_t>(v));
    const math::vec3_t<num_t>&& temp = v * v;
    return v / std::sqrt(math::sum<num_t>(temp));
}

/*-------------------------------------
    3D Magnitude (squared)
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::length_squared(const vec3_t <num_t>& v) noexcept
{
    return math::sum<num_t>(v * v);
}

/*-------------------------------------
    3D Magnitude
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::length(const vec3_t <num_t>& v) noexcept
{
    return std::sqrt(math::length_squared<num_t>(v));
}

/*-------------------------------------
    3D X-Rotation
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::x_rotation(num_t angle) noexcept
{
    const num_t s = std::sin(angle);
    const num_t c = std::cos(angle);

    return vec3_t<num_t>(num_t{1}, c + s, c - s);
}

/*-------------------------------------
    3D Y-Rotation
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::y_rotation(num_t angle) noexcept
{
    const num_t s = std::sin(angle);
    const num_t c = std::cos(angle);

    return vec3_t<num_t>(c - s, num_t{1}, s + c);
}

/*-------------------------------------
    3D Z-Rotation
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::z_rotation(num_t angle) noexcept
{
    const num_t s = std::sin(angle);
    const num_t c = std::cos(angle);

    return vec3_t<num_t>(c + s, c - s, num_t{1});
}

/*-------------------------------------
    3D Angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::angle_between(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2) noexcept
{
    return (num_t)math::acos(
        math::dot(v1, v2) / (math::length<num_t>(v1) * math::length<num_t>(v2))
    );
}

/*-------------------------------------
    3D Angle (with origin)
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::angle_between(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2, const vec3_t <num_t>& origin) noexcept
{
    return (num_t)math::acos(
        math::dot(v1 - origin, v2 - origin) / (math::length<num_t>(v1) * math::length<num_t>(v2))
    );
}

/*-------------------------------------
    3D Min
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::min(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2) noexcept
{
    //return math::length_squared<num_t>(v1) < math::length_squared<num_t>(v2) ? v1 : v2;
    return math::vec3_t<num_t>{
        math::min<num_t>(v1.v[0], v2.v[0]),
        math::min<num_t>(v1.v[1], v2.v[1]),
        math::min<num_t>(v1.v[2], v2.v[2])
    };
}

/*-------------------------------------
    3D Mix
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::mix(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2, num_t percent) noexcept
{
    return vec3_t < num_t > {v1 + ((v2 - v1) * percent)};
}

/*-------------------------------------
    3D Max
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::max(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2) noexcept
{
    //return math::length_squared<num_t>(v1) > math::length_squared<num_t>(v2) ? v1 : v2;
    return math::vec3_t<num_t>{
        math::max<num_t>(v1.v[0], v2.v[0]),
        math::max<num_t>(v1.v[1], v2.v[1]),
        math::max<num_t>(v1.v[2], v2.v[2])
    };
}

/*-------------------------------------
    3D Clamp
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::clamp(const vec3_t<num_t>& v, const vec3_t<num_t>& minVals, const vec3_t<num_t>& maxVals) noexcept
{
    return math::vec3_t<num_t>{
        math::clamp<num_t>(v.v[0], minVals.v[0], maxVals.v[0]),
        math::clamp<num_t>(v.v[1], minVals.v[1], maxVals.v[1]),
        math::clamp<num_t>(v.v[2], minVals.v[2], maxVals.v[2])
    };
}

/*-------------------------------------
    3D Saturate
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::saturate(const vec3_t<num_t>& v) noexcept
{
    return math::vec3_t<num_t>{
        math::saturate<num_t>(v.v[0]),
        math::saturate<num_t>(v.v[1]),
        math::saturate<num_t>(v.v[2])
    };
}

/*-------------------------------------
    3D Projection
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::project(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2) noexcept
{
    const num_t v1Len = math::length<num_t>(v1);
    const num_t v2Len = math::length<num_t>(v2);

    const math::vec3_t<num_t>&& v1Norm = v1 / v1Len;
    const math::vec3_t<num_t>&& v2Norm = v2 / v2Len;

    const num_t cosTheta = math::dot(v1Norm, v2Norm);

    return v2Norm * cosTheta * v1Len;
}

/*-------------------------------------
    3D Reflect
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::reflect(const vec3_t <num_t>& v, const vec3_t <num_t>& norm) noexcept
{
    /*
    const math::vec4_t<num_t>&& nv = math::normalize(v);
    const math::vec4_t<num_t>&& bounce = norm * (math::dot(nv, norm) * num_t {2});
    return bounce - nv;
    */
    return v - math::vec3_t<num_t>{2} * math::dot(v, norm) * norm;
}

/*-------------------------------------
    3D Mid
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::mid(const vec3_t <num_t>& v1, const vec3_t <num_t>& v2) noexcept
{
    return std::is_integral<num_t>::value
           ? ((v1 + v2) / num_t{2})
           : ((v1 + v2) * num_t{0.5});
}

/*-------------------------------------
    3D Step
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::step(const vec3_t <num_t>& edge, const vec3_t <num_t>& v) noexcept
{
    return math::vec3_t<num_t>{
        v.v[0] < edge.v[0] ? num_t{0} : num_t{1},
        v.v[1] < edge.v[1] ? num_t{0} : num_t{1},
        v.v[2] < edge.v[2] ? num_t{0} : num_t{1}
    };
}

/*-------------------------------------
    3D Smoothstep
-------------------------------------*/
template<typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::smoothstep(const vec3_t<num_t>& a, const vec3_t<num_t>& b, const vec3_t<num_t>& x) noexcept
{
    return math::vec3_t<num_t>{
        math::smoothstep<num_t>(a.v[0], b.v[0], x.v[0]),
        math::smoothstep<num_t>(a.v[1], b.v[1], x.v[1]),
        math::smoothstep<num_t>(a.v[2], b.v[2], x.v[2])
    };
}

/*-------------------------------------
    3D RCP
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::rcp(const vec3_t <num_t>& v) noexcept
{
    return vec3_t < num_t > {
        ls::math::rcp(v.v[0]),
        ls::math::rcp(v.v[1]),
        ls::math::rcp(v.v[2])
    };
}

/*-------------------------------------
    3D Sign Bits
-------------------------------------*/
template <typename N> constexpr LS_INLINE
int math::sign_mask(const vec3_t <N>& x) noexcept
{
    return math::sign_mask(x.v[0]) | (math::sign_mask(x.v[1]) << 1) | (math::sign_mask(x.v[2]) << 2);
}

/*-------------------------------------
    3D Signs
-------------------------------------*/
template <typename N> constexpr LS_INLINE
math::vec3_t<N> math::sign(const vec3_t <N>& x) noexcept
{
    return vec3_t < N > {
        math::sign(x.v[0]),
        math::sign(x.v[1]),
        math::sign(x.v[2])
    };
}

/*-------------------------------------
    3D floor
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::floor(const vec3_t <num_t>& v) noexcept
{
    return vec3_t < num_t > {
        ls::math::floor(v.v[0]),
        ls::math::floor(v.v[1]),
        ls::math::floor(v.v[2])
    };
}

/*-------------------------------------
    3D ceil
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::ceil(const vec3_t <num_t>& v) noexcept
{
    return vec3_t < num_t > {
        ls::math::ceil(v.v[0]),
        ls::math::ceil(v.v[1]),
        ls::math::ceil(v.v[2])
    };
}

/*-------------------------------------
    3D round
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::round(const vec3_t <num_t>& v) noexcept
{
    return vec3_t < num_t > {
        ls::math::round(v.v[0]),
        ls::math::round(v.v[1]),
        ls::math::round(v.v[2])
    };
}

/*-------------------------------------
    3D abs
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::abs(const vec3_t <num_t>& v) noexcept
{
    return vec3_t < num_t > {
        ls::math::abs(v.v[0]),
        ls::math::abs(v.v[1]),
        ls::math::abs(v.v[2])
    };
}

/*-------------------------------------
    log2
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::log2(const math::vec3_t<num_t>& n) noexcept
{
    return math::vec3_t<num_t>{
        (num_t)math::log2<float>((float)n.v[0]),
        (num_t)math::log2<float>((float)n.v[1]),
        (num_t)math::log2<float>((float)n.v[2])
    };
}

/*-------------------------------------
    log
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::log(const math::vec3_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) * 0.693147181f; // ln( 2 )
}

/*-------------------------------------
    log10
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::log10(const math::vec3_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) * 0.3010299956639812f; // 1.0 / log2( 10 )
}

/*-------------------------------------
    logN
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::logN(const math::vec3_t<num_t>& baseN, const math::vec3_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) / log2<num_t>(baseN);
}

/*-------------------------------------
    pow
-------------------------------------*/
namespace math
{
namespace impl
{
template <typename num_t>
constexpr num_t powi_impl(const math::vec3_t<num_t>& p, const math::vec3_t<num_t>& y, const math::vec3_t<num_t>& result) noexcept
{
    return (y < math::vec3_t<num_t>{1}) ? result : math::impl::powi_impl<num_t>(p * p, y >> math::vec3_t<num_t>{2}, (y & math::vec3_t<num_t>{1}) ? (result * p) : result);
}
} // end impl namespace
} // end math namespace

template <typename num_t>
constexpr LS_INLINE math::vec3_t<num_t> math::pow(
    const typename setup::EnableIf<setup::IsIntegral<num_t>::value, math::vec3_t<num_t>>::type& x,
    const typename setup::EnableIf<setup::IsIntegral<num_t>::value, math::vec3_t<num_t>>::type& y) noexcept
{
    return math::impl::powi_impl<num_t>(x, y, math::vec3_t<num_t>{1});
}

template <typename num_t>
inline LS_INLINE math::vec3_t<num_t> math::pow(const math::vec3_t<num_t>& x, const math::vec3_t<num_t>& y) noexcept
{
    return math::exp<num_t>(math::log<num_t>(x) * y);
}

/*-------------------------------------
    exp
-------------------------------------*/
template <typename num_t>
inline LS_INLINE math::vec3_t<num_t> math::exp(math::vec3_t<num_t> x) noexcept
{
    x = math::vec3_t<num_t>{1.f} + x / math::vec3_t<num_t>{256.f};
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
}

/*-------------------------------------
    exp2
-------------------------------------*/
template <typename num_t>
inline LS_INLINE math::vec3_t<num_t> math::exp2(math::vec3_t<num_t> x) noexcept
{
    x = math::vec2_t<num_t>{1.f} + x * math::vec3_t<num_t>{num_t{0.002707606174}}; // ln(2)/256
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
}

/*-------------------------------------
    FMA
-------------------------------------*/
template <typename num_t>
constexpr LS_INLINE math::vec3_t<num_t> math::fmadd(const vec3_t <num_t>& x, const vec3_t <num_t>& m, const vec3_t <num_t>& a) noexcept
{
    return (x * m) + a;
}

/*-------------------------------------
    FMS
-------------------------------------*/
template <typename num_t>
constexpr LS_INLINE math::vec3_t<num_t> math::fmsub(const vec3_t <num_t>& x, const vec3_t <num_t>& m, const vec3_t <num_t>& a) noexcept
{
    return (x * m) - a;
}

/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Sum
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::sum(const vec4_t <num_t>& v) noexcept
{
    return v.v[0] + v.v[1] + v.v[2] + v.v[3];
}

/*-------------------------------------
    4D Reciprocal Sum
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::sum_inv(const vec4_t <num_t>& v) noexcept
{
    return math::rcp<num_t>(v.v[0] + v.v[1] + v.v[2] + v.v[3]);
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::dot(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2) noexcept
{
    return math::sum<num_t>(v1 * v2);
}

/*-------------------------------------
    4D Cross
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::cross(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2) noexcept
{
    return vec4_t < num_t > {
        (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]),
        (v1.v[2] * v2.v[0]) - (v1.v[0] * v2.v[2]),
        (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0]),
        num_t{0}
    };
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec4_t<num_t> math::normalize(const vec4_t <num_t>& v) noexcept
{
    //return v * inversesqrt(math::length_squared<num_t>(v));
    const math::vec4_t<num_t>&& temp = v * v;
    return v / std::sqrt(math::sum<num_t>(temp));
}

/*-------------------------------------
    4D Magnitude (squared)
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::length_squared(const vec4_t <num_t>& v) noexcept
{
    return math::sum<num_t>(v * v);
}

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::length(const vec4_t <num_t>& v) noexcept
{
    return std::sqrt(math::length_squared<num_t>(v));
}

/*-------------------------------------
    4D Angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::angle_between(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2) noexcept
{
    return (num_t)math::acos(
        math::dot(v1, v2) / (math::length<num_t>(v1) * math::length<num_t>(v2))
    );
}

/*-------------------------------------
    4D Angle (with origin)
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::angle_bewteen(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2, const vec4_t <num_t>& origin) noexcept
{
    return (num_t)math::acos(
        math::dot(v1 - origin, v2 - origin) / (math::length<num_t>(v1) * math::length<num_t>(v2))
    );
}

/*-------------------------------------
    4D Min
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::min(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2) noexcept
{
    //return math::length_squared<num_t>(v1) < math::length_squared<num_t>(v2) ? v1 : v2;
    return math::vec4_t<num_t>{
        math::min<num_t>(v1.v[0], v2.v[0]),
        math::min<num_t>(v1.v[1], v2.v[1]),
        math::min<num_t>(v1.v[2], v2.v[2]),
        math::min<num_t>(v1.v[3], v2.v[3])
    };
}

/*-------------------------------------
    4D Mix
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::mix(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2, num_t percent) noexcept
{
    return vec4_t < num_t > {v1 + ((v2 - v1) * percent)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::max(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2) noexcept
{
    //return math::length_squared<num_t>(v1) > math::length_squared<num_t>(v2) ? v1 : v2;
    return math::vec4_t<num_t>{
        math::max<num_t>(v1.v[0], v2.v[0]),
        math::max<num_t>(v1.v[1], v2.v[1]),
        math::max<num_t>(v1.v[2], v2.v[2]),
        math::max<num_t>(v1.v[3], v2.v[3])
    };
}

/*-------------------------------------
    4D Clamp
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::clamp(const vec4_t<num_t>& v, const vec4_t<num_t>& minVals, const vec4_t<num_t>& maxVals) noexcept
{
    return math::vec4_t<num_t>{
        math::clamp<num_t>(v.v[0], minVals.v[0], maxVals.v[0]),
        math::clamp<num_t>(v.v[1], minVals.v[1], maxVals.v[1]),
        math::clamp<num_t>(v.v[2], minVals.v[2], maxVals.v[2]),
        math::clamp<num_t>(v.v[3], minVals.v[3], maxVals.v[3])
    };
}

/*-------------------------------------
    4D Saturate
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::saturate(const vec4_t<num_t>& v) noexcept
{
    return math::vec4_t<num_t>{
        math::saturate<num_t>(v.v[0]),
        math::saturate<num_t>(v.v[1]),
        math::saturate<num_t>(v.v[2]),
        math::saturate<num_t>(v.v[2])
    };
}

/*-------------------------------------
    4D Projection
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec4_t<num_t> math::project(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2) noexcept
{
    const num_t v1Len = math::length<num_t>(v1);
    const num_t v2Len = math::length<num_t>(v2);

    const math::vec4_t<num_t>&& v1Norm = v1 / v1Len;
    const math::vec4_t<num_t>&& v2Norm = v2 / v2Len;

    const num_t cosTheta = math::dot(v1Norm, v2Norm);

    return v2Norm * cosTheta * v1Len;
}

/*-------------------------------------
    4D Reflect
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::reflect(const vec4_t <num_t>& v, const vec4_t <num_t>& norm) noexcept
{
    /*
    const math::vec4_t<num_t>&& nv = math::normalize(v);
    const math::vec4_t<num_t>&& bounce = norm * (math::dot(nv, norm) * num_t {2});
    return bounce - nv;
    */
    return v - math::vec4_t<num_t>{2} * math::dot(v, norm) * norm;
}

/*-------------------------------------
    4D Mid
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::mid(const vec4_t <num_t>& v1, const vec4_t <num_t>& v2) noexcept
{
    return std::is_integral<num_t>::value
           ? ((v1 + v2) / num_t{2})
           : ((v1 + v2) * num_t{0.5});
}

/*-------------------------------------
    4D Step
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::step(const vec4_t <num_t>& edge, const vec4_t <num_t>& v) noexcept
{
    return math::vec4_t<num_t>{
        v.v[0] < edge.v[0] ? num_t{0} : num_t{1},
        v.v[1] < edge.v[1] ? num_t{0} : num_t{1},
        v.v[2] < edge.v[2] ? num_t{0} : num_t{1},
        v.v[3] < edge.v[3] ? num_t{0} : num_t{1}
    };
}

/*-------------------------------------
    4D Smoothstep
-------------------------------------*/
template<typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::smoothstep(const vec4_t<num_t>& a, const vec4_t<num_t>& b, const vec4_t<num_t>& x) noexcept
{
    return math::vec4_t<num_t>{
        math::smoothstep<num_t>(a.v[0], b.v[0], x.v[0]),
        math::smoothstep<num_t>(a.v[1], b.v[1], x.v[1]),
        math::smoothstep<num_t>(a.v[2], b.v[2], x.v[2]),
        math::smoothstep<num_t>(a.v[3], b.v[3], x.v[3])
    };
}

/*-------------------------------------
    4D RCP
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::rcp(const vec4_t <num_t>& v) noexcept
{
    return vec4_t < num_t > {
        ls::math::rcp(v.v[0]),
        ls::math::rcp(v.v[1]),
        ls::math::rcp(v.v[2]),
        ls::math::rcp(v.v[3])
    };
}

/*-------------------------------------
    4D Sign Bits
-------------------------------------*/
template <typename N> constexpr LS_INLINE
int math::sign_mask(const vec4_t <N>& x) noexcept
{
    return math::sign_mask(x.v[0])
           | (math::sign_mask(x.v[1]) << 1)
           | (math::sign_mask(x.v[2]) << 2)
           | (math::sign_mask(x.v[3]) << 3);
}

/*-------------------------------------
    4D Signs
-------------------------------------*/
template <typename N> constexpr LS_INLINE
math::vec4_t<N> math::sign(const vec4_t <N>& x) noexcept
{
    return vec4_t < N > {
        math::sign(x.v[0]),
        math::sign(x.v[1]),
        math::sign(x.v[2]),
        math::sign(x.v[3])
    };
}

/*-------------------------------------
    4D floor
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::floor(const vec4_t <num_t>& v) noexcept
{
    return vec4_t < num_t > {
        ls::math::round(v.v[0]),
        ls::math::round(v.v[1]),
        ls::math::round(v.v[2]),
        ls::math::round(v.v[3])
    };
}

/*-------------------------------------
    4D ceil
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::ceil(const vec4_t <num_t>& v) noexcept
{
    return vec4_t < num_t > {
        ls::math::ceil(v.v[0]),
        ls::math::ceil(v.v[1]),
        ls::math::ceil(v.v[2]),
        ls::math::ceil(v.v[3])
    };
}

/*-------------------------------------
    4D round
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::round(const vec4_t <num_t>& v) noexcept
{
    return vec4_t < num_t > {
        ls::math::round(v.v[0]),
        ls::math::round(v.v[1]),
        ls::math::round(v.v[2]),
        ls::math::round(v.v[3])
    };
}

/*-------------------------------------
    4D abs
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec4_t<num_t> math::abs(const vec4_t <num_t>& v) noexcept
{
    return vec4_t < num_t > {
        ls::math::abs(v.v[0]),
        ls::math::abs(v.v[1]),
        ls::math::abs(v.v[2]),
        ls::math::abs(v.v[3])
    };
}

/*-------------------------------------
    log2
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec4_t<num_t> math::log2(const math::vec4_t<num_t>& n) noexcept
{
    return math::vec4_t<num_t>{
        (num_t)math::log2<float>((float)n.v[0]),
        (num_t)math::log2<float>((float)n.v[1]),
        (num_t)math::log2<float>((float)n.v[2]),
        (num_t)math::log2<float>((float)n.v[3])
    };
}

/*-------------------------------------
    log
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec4_t<num_t> math::log(const math::vec4_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) * 0.69314718056f; // ln( 2 )
}

/*-------------------------------------
    log10
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec4_t<num_t> math::log10(const math::vec4_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) * 0.3010299956639812f; // 1.0 / log2( 10 )
}

/*-------------------------------------
    logN
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec4_t<num_t> math::logN(const math::vec4_t<num_t>& baseN, const math::vec4_t<num_t>& n) noexcept
{
    return math::log2<num_t>(n) / log2<num_t>(baseN);
}

/*-------------------------------------
    pow
-------------------------------------*/
namespace math
{
namespace impl
{
template <typename num_t>
constexpr num_t powi_impl(const math::vec4_t<num_t>& p, const math::vec4_t<num_t>& y, const math::vec4_t<num_t>& result) noexcept
{
    return (y < math::vec4_t<num_t>{1}) ? result : math::impl::powi_impl<num_t>(p * p, y >> math::vec4_t<num_t>{2}, (y & math::vec4_t<num_t>{1}) ? (result * p) : result);
}
} // end impl namespace
} // end math namespace

template <typename num_t>
constexpr LS_INLINE math::vec4_t<num_t> math::pow(
    const typename setup::EnableIf<setup::IsIntegral<num_t>::value, math::vec4_t<num_t>>::type& x,
    const typename setup::EnableIf<setup::IsIntegral<num_t>::value, math::vec4_t<num_t>>::type& y) noexcept
{
    return math::impl::powi_impl<num_t>(x, y, math::vec4_t<num_t>{1});
}

template <typename num_t>
inline LS_INLINE math::vec4_t<num_t> math::pow(const math::vec4_t<num_t>& x, const math::vec4_t<num_t>& y) noexcept
{
    return math::exp<num_t>(math::log<num_t>(x) * y);
}

/*-------------------------------------
    exp
-------------------------------------*/
template <typename num_t>
inline LS_INLINE math::vec4_t<num_t> math::exp(math::vec4_t<num_t> x) noexcept
{
    x = math::vec4_t<num_t>{1.f} + x / math::vec4_t<num_t>{256.f};
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
}

/*-------------------------------------
    exp2
-------------------------------------*/
template <typename num_t>
inline LS_INLINE math::vec4_t<num_t> math::exp2(math::vec4_t<num_t> x) noexcept
{
    x = math::vec4_t<num_t>{1.f} + x * math::vec4_t<num_t>{num_t{0.002707606174}}; // ln(2)/256
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
}

/*-------------------------------------
    FMA
-------------------------------------*/
template <typename num_t>
constexpr LS_INLINE math::vec4_t<num_t> math::fmadd(const vec4_t <num_t>& x, const vec4_t <num_t>& m, const vec4_t <num_t>& a) noexcept
{
    return (x * m) + a;
}

/*-------------------------------------
    FMS
-------------------------------------*/
template <typename num_t>
constexpr LS_INLINE math::vec4_t<num_t> math::fmsub(const vec4_t <num_t>& x, const vec4_t <num_t>& m, const vec4_t <num_t>& a) noexcept
{
    return (x * m) - a;
}



/*-----------------------------------------------------------------------------
    Vector Casting
-----------------------------------------------------------------------------*/
/*-------------------------------------
    2D Vector from 3D
-------------------------------------*/
template <typename N>
constexpr math::vec2_t<N> math::vec2_cast(const math::vec3_t<N>& v) noexcept
{
    return math::vec2_t<N>{v.v[0], v.v[1]};
}



/*-------------------------------------
    2D Vector from 4D
-------------------------------------*/
template <typename N>
constexpr math::vec2_t<N> math::vec2_cast(const math::vec4_t<N>& v) noexcept
{
    return math::vec2_t<N>{v.v[0], v.v[1]};
}



/*-------------------------------------
    3D Vector from 2D & Scalar
-------------------------------------*/
template <typename N>
constexpr math::vec3_t<N> math::vec3_cast(const math::vec2_t<N>& v, const N& s) noexcept
{
    return math::vec3_t<N>{v.v[0], v.v[1], s};
}



/*-------------------------------------
    3D Vector from Scalar & 2D
-------------------------------------*/
template <typename N>
constexpr math::vec3_t<N> math::vec3_cast(const N& s, const math::vec2_t<N>& v) noexcept
{
    return math::vec3_t<N>{s, v.v[0], v.v[1]};
}



/*-------------------------------------
    3D Vector from 4D
-------------------------------------*/
template <typename N>
constexpr math::vec3_t<N> math::vec3_cast(const math::vec4_t<N>& v) noexcept
{
    return math::vec3_t<N>{v.v[0], v.v[1], v.v[2]};
}



/*-------------------------------------
    4D Vector from 2D & Scalars
-------------------------------------*/
template <typename N>
constexpr math::vec4_t<N> math::vec4_cast(const math::vec2_t<N>& v, const N& s0, const N& s1) noexcept
{
    return math::vec4_t<N>{v.v[0], v.v[1], s0, s1};
}



/*-------------------------------------
    4D Vector from Scalar, 2D, & Scalar
-------------------------------------*/
template <typename N>
constexpr math::vec4_t<N> math::vec4_cast(const N& s0, const math::vec2_t<N>& v, const N& s1) noexcept
{
    return math::vec4_t<N>{s0, v.v[0], v.v[1], s1};
}



/*-------------------------------------
    4D Vector from Scalars & 2D
-------------------------------------*/
template <typename N>
constexpr math::vec4_t<N> math::vec4_cast(const N& s0, const N& s1, const math::vec2_t<N>& v) noexcept
{
    return math::vec4_t<N>{s0, s1, v.v[0], v.v[1]};
}



/*-------------------------------------
    4D Vector from 2D Vectors
-------------------------------------*/
template <typename N>
constexpr math::vec4_t<N> math::vec4_cast(const math::vec2_t<N>& v0, const math::vec2_t<N>& v1) noexcept
{
    return math::vec4_t<N>{v0.v[0], v0.v[1], v1.v[0], v1.v[1]};
}



/*-------------------------------------
    4D Vector from 3D & Scalar
-------------------------------------*/
template <typename N>
constexpr math::vec4_t<N> math::vec4_cast(const math::vec3_t<N>& v, const N& s) noexcept
{
    return math::vec4_t<N>{v.v[0], v.v[1], v.v[2], s};
}



/*-------------------------------------
    4D Vector from Scalar & 3D
-------------------------------------*/
template <typename N>
constexpr math::vec4_t<N> math::vec4_cast(const N& s, const math::vec3_t<N>& v) noexcept
{
    return math::vec4_t<N>{s, v.v[0], v.v[1], v.v[2]};
}
} // end ls namespace

#endif /* LS_MATH_VEC_UTILS_IMPL_H */
