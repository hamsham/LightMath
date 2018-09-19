
#include <type_traits>

namespace ls {

/*-----------------------------------------------------------------------------
    2D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    2D Sum
-------------------------------------*/
template <typename num_t> constexpr
num_t math::sum(const vec2_t<num_t>& v) {
    return v.v[0] + v.v[1];
}

/*-------------------------------------
    2D Reciprocal Sum
-------------------------------------*/
template <typename num_t> constexpr
num_t math::sum_inv(const vec2_t<num_t>& v) {
    return math::rcp<num_t>(v.v[0] + v.v[1]);
}

/*-------------------------------------
    2D Dot
-------------------------------------*/
template <typename num_t> constexpr
num_t math::dot(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2) {
    return math::sum<num_t>(v1 * v2);
}

/*-------------------------------------
    2D Cross
-------------------------------------*/
template <typename num_t> constexpr
num_t math::cross(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2) {
    return (v1[0] * v2[1])-(v1[1] * v2[0]);
}

/*-------------------------------------
    2D Normalize
-------------------------------------*/
template <typename num_t> inline
math::vec2_t<num_t> math::normalize(const vec2_t<num_t>& v) {
    //return v * fast_inv_sqrt<num_t>(length_squared<num_t>(v));
    const math::vec2_t<num_t>&& temp = v * v;
    return v * fast_inv_sqrt<num_t>(math::sum<num_t>(temp));
}

/*-------------------------------------
    2D Magnitude (squared)
-------------------------------------*/
template <typename num_t> constexpr
num_t math::length_squared(const vec2_t<num_t>& v) {
    return math::sum<num_t>(v * v);
}

/*-------------------------------------
    2D Magnitude
-------------------------------------*/
template <typename num_t> inline
num_t math::length(const vec2_t<num_t>& v) {
    return fast_sqrt<num_t>(length_squared<num_t>(v));
}

/*-------------------------------------
    2D Rotate
-------------------------------------*/
template <typename num_t> inline
math::vec2_t<num_t> math::rotate(const vec2_t<num_t>& v, num_t angle) {
    const num_t s = LS_SIN(angle);
    const num_t c = LS_COS(angle);

    return vec2_t<num_t>((v.v[0] * c) - (v.v[1] * s), (v.v[0] * s) + (v.v[1] * c));
}

/*-------------------------------------
    2D Angle
-------------------------------------*/
template <typename num_t> inline
num_t math::angle_between(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2) {
    return (num_t) acos(
        dot<num_t>(v1, v2) / (length<num_t>(v1) * length<num_t>(v2))
    );
}

/*-------------------------------------
    2D Angle (with origin)
-------------------------------------*/
template <typename num_t> inline
num_t math::angle_between(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2, const vec2_t<num_t>& origin) {
    return (num_t) acos(
        dot<num_t>(v1 - origin, v2 - origin) / (length<num_t>(v1) * length<num_t>(v2))
    );
}

/*-------------------------------------
    2D Min
-------------------------------------*/
template <typename num_t> constexpr
math::vec2_t<num_t> math::min(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2) {
    //return length_squared<num_t>(v1) < length_squared<num_t>(v2) ? v1 : v2;
    return math::vec2_t<num_t>{
        math::min<num_t>(v1.v[0], v2.v[0]),
        math::min<num_t>(v1.v[1], v2.v[1])
    };
}

/*-------------------------------------
    2D Mix
-------------------------------------*/
template <typename num_t> constexpr
math::vec2_t<num_t> math::mix(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2, num_t percent) {
    return vec2_t<num_t>{v1 + ((v2 - v1) * percent)};
}

/*-------------------------------------
    2D Max
-------------------------------------*/
template <typename num_t> constexpr
math::vec2_t<num_t> math::max(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2) {
    //return length_squared<num_t>(v1) > length_squared<num_t>(v2) ? v1 : v2;
    return math::vec2_t<num_t>{
        math::max<num_t>(v1.v[0], v2.v[0]),
        math::max<num_t>(v1.v[1], v2.v[1])
    };
}

/*-------------------------------------
    2D Projection
-------------------------------------*/
template <typename num_t> inline
math::vec2_t<num_t> math::project(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2) {
    const num_t v1Len = math::length<num_t>(v1);
    const num_t v2Len = math::length<num_t>(v2);

    const math::vec2_t<num_t>&& v1Norm = v1 / v1Len;
    const math::vec2_t<num_t>&& v2Norm = v2 / v2Len;

    const num_t cosTheta = math::dot<num_t>(v1Norm, v2Norm);

    return v2Norm * cosTheta * v1Len;
}

/*-------------------------------------
    2D Reflection
-------------------------------------*/
template <typename num_t> inline
math::vec2_t<num_t> math::reflect(const vec2_t<num_t>& v, const vec2_t<num_t>& norm) {
    const math::vec2_t<num_t>&& nv = math::normalize<num_t>(v);

    const math::vec2_t<num_t>&& bounce = norm * (math::dot<num_t>(nv, norm) * num_t {2});
    return bounce - nv;
}

/*-------------------------------------
    2D Mid
-------------------------------------*/
template <typename num_t> constexpr
math::vec2_t<num_t> math::mid(const vec2_t<num_t>& v1, const vec2_t<num_t>& v2) {
    return std::is_integral<num_t>::value
        ? ((v1[0] + v2[0]) / num_t{2})
        : ((v1[0] + v2[0]) * num_t{0.5});
}

/*-------------------------------------
    2D RCP
-------------------------------------*/
template <typename num_t> constexpr
math::vec2_t<num_t> math::rcp(const vec2_t<num_t>& v) {
    return vec2_t<num_t>{1.0} / v;
}

/*-------------------------------------
    2D Sign Bits
-------------------------------------*/
template <typename N> constexpr
int math::sign_bits(const vec2_t<N>& x) noexcept
{
    return math::sign_bit<N>(x.v[0]) | (math::sign_bit<N>(x.v[1]) << 1);
}



/*-----------------------------------------------------------------------------
    3D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    3D Sum
-------------------------------------*/
template <typename num_t> constexpr
num_t math::sum(const vec3_t<num_t>& v) {
    return v.v[0] + v.v[1] + v.v[2];
}

/*-------------------------------------
    3D Reciprocal Sum
-------------------------------------*/
template <typename num_t> constexpr
num_t math::sum_inv(const vec3_t<num_t>& v) {
    return math::rcp<num_t>(v.v[0] + v.v[1] + v.v[2]);
}

/*-------------------------------------
    3D Dot
-------------------------------------*/
template <typename num_t> constexpr
num_t math::dot(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2) {
    return math::sum<num_t>(v1 * v2);
}

/*-------------------------------------
    3D Cross
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::cross(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2) {
    return vec3_t<num_t>{
        (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]),
        (v1.v[2] * v2.v[0]) - (v1.v[0] * v2.v[2]),
        (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0])
    };
}

/*-------------------------------------
    3D Normalize
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::normalize(const vec3_t<num_t>& v) {
    //return v * fast_inv_sqrt<num_t>(length_squared<num_t>(v));
    const math::vec3_t<num_t>&& temp = v * v;
    return v * fast_inv_sqrt<num_t>(math::sum<num_t>(temp));

}

/*-------------------------------------
    3D Magnitude (squared)
-------------------------------------*/
template <typename num_t> constexpr
num_t math::length_squared(const vec3_t<num_t>& v) {
    return math::sum<num_t>(v * v);
}

/*-------------------------------------
    3D Magnitude
-------------------------------------*/
template <typename num_t> inline
num_t math::length(const vec3_t<num_t>& v) {
    return fast_sqrt<num_t>(length_squared<num_t>(v));
}

/*-------------------------------------
    3D X-Rotation
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::x_rotation(num_t angle) {
    const num_t s = LS_SIN(angle);
    const num_t c = LS_COS(angle);

    return vec3_t<num_t>(num_t{1}, c + s, c - s);
}

/*-------------------------------------
    3D Y-Rotation
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::y_rotation(num_t angle) {
    const num_t s = LS_SIN(angle);
    const num_t c = LS_COS(angle);

    return vec3_t<num_t>(c - s, num_t{1}, s + c);
}

/*-------------------------------------
    3D Z-Rotation
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::z_rotation(num_t angle) {
    const num_t s = LS_SIN(angle);
    const num_t c = LS_COS(angle);

    return vec3_t<num_t>(c + s, c - s, num_t{1});
}

/*-------------------------------------
    3D Angle
-------------------------------------*/
template <typename num_t> inline
num_t math::angle_between(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2) {
    return (num_t) acos(
        dot<num_t>(v1, v2) / (length<num_t>(v1) * length<num_t>(v2))
    );
}

/*-------------------------------------
    3D Angle (with origin)
-------------------------------------*/
template <typename num_t> inline
num_t math::angle_between(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2, const vec3_t<num_t>& origin) {
    return (num_t) acos(
        dot<num_t>(v1 - origin, v2 - origin) / (length<num_t>(v1) * length<num_t>(v2))
    );
}

/*-------------------------------------
    3D Min
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::min(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2) {
    //return length_squared<num_t>(v1) < length_squared<num_t>(v2) ? v1 : v2;
    return math::vec3_t<num_t>{
        math::min<num_t>(v1.v[0], v2.v[0]),
        math::min<num_t>(v1.v[1], v2.v[1]),
        math::min<num_t>(v1.v[2], v2.v[2])
    };
}

/*-------------------------------------
    3D Mix
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::mix(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2, num_t percent) {
    return vec3_t<num_t>{v1 + ((v2 - v1) * percent)};
}

/*-------------------------------------
    3D Max
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::max(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2) {
    //return length_squared<num_t>(v1) > length_squared<num_t>(v2) ? v1 : v2;
    return math::vec3_t<num_t>{
        math::max<num_t>(v1.v[0], v2.v[0]),
        math::max<num_t>(v1.v[1], v2.v[1]),
        math::max<num_t>(v1.v[2], v2.v[2])
    };
}

/*-------------------------------------
    3D Projection
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::project(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2) {
    const num_t v1Len = math::length<num_t>(v1);
    const num_t v2Len = math::length<num_t>(v2);

    const math::vec3_t<num_t>&& v1Norm = v1 / v1Len;
    const math::vec3_t<num_t>&& v2Norm = v2 / v2Len;

    const num_t cosTheta = math::dot<num_t>(v1Norm, v2Norm);

    return v2Norm * cosTheta * v1Len;
}

/*-------------------------------------
    3D Reflect
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::reflect(const vec3_t<num_t>& v, const vec3_t<num_t>& norm) {
    const math::vec3_t<num_t>&& nv = math::normalize(v);

    const math::vec3_t<num_t>&& bounce = norm * (math::dot<num_t>(nv, norm) * num_t{2});

    return bounce - nv;
}

/*-------------------------------------
    3D Mid
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::mid(const vec3_t<num_t>& v1, const vec3_t<num_t>& v2) {
    return std::is_integral<num_t>::value
        ? ((v1[0] + v2[0]) / num_t{2})
        : ((v1[0] + v2[0]) * num_t{0.5});
}

/*-------------------------------------
    3D RCP
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::rcp(const vec3_t<num_t>& v) {
    return vec3_t<num_t>{1.0} / v;
}

/*-------------------------------------
    3D Sign Bits
-------------------------------------*/
template <typename N> constexpr
int math::sign_bits(const vec3_t<N>& x) noexcept
{
    return math::sign_bit<N>(x.v[0]) | (math::sign_bit<N>(x.v[1]) << 1) | (math::sign_bit<N>(x.v[2]) << 2);
}



/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4D Sum
-------------------------------------*/
template <typename num_t> constexpr
num_t math::sum(const vec4_t<num_t>& v) {
    return v.v[0] + v.v[1] + v.v[2] + v.v[3];
}

/*-------------------------------------
    4D Reciprocal Sum
-------------------------------------*/
template <typename num_t> constexpr
num_t math::sum_inv(const vec4_t<num_t>& v) {
    return math::rcp<num_t>(v.v[0] + v.v[1] + v.v[2] + v.v[3]);
}

/*-------------------------------------
    4D Dot
-------------------------------------*/
template <typename num_t> constexpr
num_t math::dot(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2) {
    return math::sum<num_t>(v1 * v2);
}

/*-------------------------------------
    4D Cross
-------------------------------------*/
template <typename num_t> constexpr
math::vec4_t<num_t> math::cross(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2) {
    return vec4_t<num_t>{
        (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]),
        (v1.v[2] * v2.v[0]) - (v1.v[0] * v2.v[2]),
        (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0]),
        num_t{0}
    };
}

/*-------------------------------------
    4D Normalize
-------------------------------------*/
template <typename num_t> inline
math::vec4_t<num_t> math::normalize(const vec4_t<num_t>& v) {
    //return v * fast_inv_sqrt<num_t>(length_squared<num_t>(v));
    const math::vec4_t<num_t>&& temp = v * v;
    return v * fast_inv_sqrt<num_t>(math::sum<num_t>(temp));
}

/*-------------------------------------
    4D Magnitude (squared)
-------------------------------------*/
template <typename num_t> constexpr
num_t math::length_squared(const vec4_t<num_t>& v) {
    return math::sum<num_t>(v * v);
}

/*-------------------------------------
    4D Magnitude
-------------------------------------*/
template <typename num_t> inline
num_t math::length(const vec4_t<num_t>& v) {
    return fast_sqrt<num_t>(length_squared<num_t>(v));
}

/*-------------------------------------
    4D Angle
-------------------------------------*/
template <typename num_t> inline
num_t math::angle_between(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2) {
    return (num_t) acos(
        dot<num_t>(v1, v2) / (length<num_t>(v1) * length<num_t>(v2))
    );
}

/*-------------------------------------
    4D Angle (with origin)
-------------------------------------*/
template <typename num_t> inline
num_t math::angle_bewteen(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2, const vec4_t<num_t>& origin) {
    return (num_t) acos(
        dot<num_t>(v1 - origin, v2 - origin) / (length<num_t>(v1) * length<num_t>(v2))
    );
}

/*-------------------------------------
    4D Min
-------------------------------------*/
template <typename num_t> constexpr
math::vec4_t<num_t> math::min(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2) {
    //return length_squared<num_t>(v1) < length_squared<num_t>(v2) ? v1 : v2;
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
template <typename num_t> constexpr
math::vec4_t<num_t> math::mix(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2, num_t percent) {
    return vec4_t<num_t>{v1 + ((v2 - v1) * percent)};
}

/*-------------------------------------
    4D Max
-------------------------------------*/
template <typename num_t> constexpr
math::vec4_t<num_t> math::max(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2) {
    //return length_squared<num_t>(v1) > length_squared<num_t>(v2) ? v1 : v2;
    return math::vec4_t<num_t>{
        math::max<num_t>(v1.v[0], v2.v[0]),
        math::max<num_t>(v1.v[1], v2.v[1]),
        math::max<num_t>(v1.v[2], v2.v[2]),
        math::max<num_t>(v1.v[3], v2.v[3])
    };
}

/*-------------------------------------
    4D Projection
-------------------------------------*/
template <typename num_t> inline
math::vec4_t<num_t> math::project(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2) {
    const num_t v1Len = math::length<num_t>(v1);
    const num_t v2Len = math::length<num_t>(v2);

    const math::vec4_t<num_t>&& v1Norm = v1 / v1Len;
    const math::vec4_t<num_t>&& v2Norm = v2 / v2Len;

    const num_t cosTheta = math::dot<num_t>(v1Norm, v2Norm);

    return v2Norm * cosTheta * v1Len;
}

/*-------------------------------------
    4D Reflect
-------------------------------------*/
template <typename num_t> inline
math::vec4_t<num_t> math::reflect(const vec4_t<num_t>& v, const vec4_t<num_t>& norm) {
    const math::vec4_t<num_t>&& nv = math::normalize(v);
    const math::vec4_t<num_t>&& bounce = norm * (math::dot<num_t>(nv, norm) * num_t {2});
    return bounce - nv;
}

/*-------------------------------------
    4D Mid
-------------------------------------*/
template <typename num_t> constexpr
math::vec4_t<num_t> math::mid(const vec4_t<num_t>& v1, const vec4_t<num_t>& v2) {
    return std::is_integral<num_t>::value
        ? ((v1[0] + v2[0]) / num_t{2})
        : ((v1[0] + v2[0]) * num_t{0.5});
}

/*-------------------------------------
    4D RCP
-------------------------------------*/
template <typename num_t> constexpr
math::vec4_t<num_t> math::rcp(const vec4_t<num_t>& v) {
    return vec4_t<num_t>{1.0} / v;
}

/*-------------------------------------
    4D Sign Bits
-------------------------------------*/
template <typename N> constexpr
int math::sign_bits(const vec4_t<N>& x) noexcept
{
    return math::sign_bit<N>(x.v[0])
        | (math::sign_bit<N>(x.v[1]) << 1)
        | (math::sign_bit<N>(x.v[2]) << 2)
        | (math::sign_bit<N>(x.v[3]) << 3);
}



} // end ls namespace
