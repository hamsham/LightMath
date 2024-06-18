
#ifndef LS_MATH_QUAT_UTILS_IMPL_H
#define LS_MATH_QUAT_UTILS_IMPL_H

#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls
{



/*-----------------------------------------------------------------------------
    Quaternion Functions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    dot
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::dot(const quat_t<num_t>& q1, const quat_t<num_t>& q2)
{
    return (q1.q[0] * q2.q[0]) + (q1.q[1] * q2.q[1]) + (q1.q[2] * q2.q[2]) + (q1.q[3] * q2.q[3]);
}

/*-------------------------------------
    length_squared
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
num_t math::length_squared(const quat_t<num_t>& q)
{
    return (q.q[0] * q.q[0]) + (q.q[1] * q.q[1]) + (q.q[2] * q.q[2]) + (q.q[3] * q.q[3]);
}

/*-------------------------------------
    length
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::length(const quat_t<num_t>& q)
{
    return (num_t)std::sqrt(length_squared(q));
}

/*-------------------------------------
    inverse
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::inverse(const quat_t<num_t>& q)
{
    const num_t&& magInv = num_t{1.0} / length_squared(q);

    return quat_t<num_t>{
        -q.q[0] * magInv,
        -q.q[1] * magInv,
        -q.q[2] * magInv,
        q.q[3] * magInv
    };
}

/*-------------------------------------
    conjugate
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::quat_t<num_t> math::conjugate(const quat_t<num_t>& q)
{
    return quat_t<num_t>{-q.q[0], -q.q[1], -q.q[2], q.q[3]};
}

/*-------------------------------------
    normalize
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::normalize(const quat_t<num_t>& q)
{
    const num_t&& magInv = inversesqrt(length_squared(q));

    return quat_t<num_t>{
        q.q[0] * magInv,
        q.q[1] * magInv,
        q.q[2] * magInv,
        q.q[3] * magInv
    };
}

/*-------------------------------------
    lerp
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::quat_t<num_t> math::lerp(const quat_t<num_t>& q1, const quat_t<num_t>& q2, num_t percent)
{
    return quat_t<num_t>{q1 + ((q2 - q1) * percent)};
}

/*-------------------------------------
    nlerp
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::quat_t<num_t> math::nlerp(const quat_t<num_t>& q1, const quat_t<num_t>& q2, num_t percent)
{
    return normalize(lerp(q1, q2, percent));
}

/*-------------------------------------
    slerp
-------------------------------------*/
template <typename num_t>
math::quat_t<num_t> math::slerp(const quat_t<num_t>& q1, const quat_t<num_t>& q2, num_t t)
{
    num_t cosTheta = dot(q1, q2);
    quat_t<num_t> q = q2;

    if (cosTheta == num_t{1})
    {
        return q1;
    }
    else if (cosTheta < num_t{0})
    {
        cosTheta = -cosTheta;
        q[0] = -q[0];
        q[1] = -q[1];
        q[2] = -q[2];
        q[3] = -q[3];
    }

    // just return a regular lerp if there's too small of an angle to
    // interpolate between.
    if ((num_t{1} - cosTheta) < num_t{1e-9})
    {
        return lerp(q1, q2, t);
    }

    const num_t&&         theta = std::acos(cosTheta);
    const quat_t<num_t>&& sq1   = q1 * std::sin(theta * (num_t{1}-t));
    const quat_t<num_t>&& sq2   = q * std::sin(t * theta);
    const num_t sinTheta        = num_t{1} / std::sin(theta);

    return (sq1 + sq2) * sinTheta;
}

/*-------------------------------------
    look_at
-------------------------------------*/
template <typename num_t>
math::quat_t<num_t> math::look_at(const math::vec3_t<num_t>& target, const math::vec3_t<num_t>& dir)
{
    const vec3_t<num_t>&& a = normalize(target);
    const vec3_t<num_t>&& b = normalize(dir);
    const vec3_t<num_t>&& w = cross(a, b);
    const quat_t<num_t>&& q{w[0], w[1], w[2], num_t{1} + dot(a, b)};

    return normalize(q);
}



/*-----------------------------------------------------------------------------
    Quaternions & Vectors
-----------------------------------------------------------------------------*/
/*-------------------------------------
    reorient
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::reorient(const quat_t<num_t>& q, const vec3_t<num_t>& v)
{
    const math::vec3_t<num_t> p{q[0], q[1], q[2]};
    const math::vec3_t<num_t>&& pv = math::cross(p, v);
    const math::vec3_t<num_t>&& ppv = math::cross(p, pv);

    return v + ((pv * q[3]) + ppv) * num_t{2};
}

/*-------------------------------------
    quat_to_mat3
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::reorient(const vec3_t<num_t>& v, const quat_t<num_t>& q)
{
    return math::reorient(math::inverse(q), v);
}

/*-------------------------------------
    Vector rotation using a Quaternion
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::rotate(const vec3_t<num_t>& v, const quat_t<num_t>& q)
{
    const vec3_t<num_t> qVec{q[0], q[1], q[2]};
    const vec3_t<num_t>&& qCrossV = cross(qVec, v);
    const num_t&& qReal = q[3];
    const num_t&& qDotV = dot(qVec, v);
    const num_t&& qLenSq = length_squared(qVec);

    return vec3_t<num_t>{qDotV * qVec * num_t{2} + (qReal * qReal - qLenSq) * v + qReal * qCrossV * num_t{2}};
}



/*-----------------------------------------------------------------------------
    Quaternions & Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    quat_to_mat3
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::mat3_t<num_t> math::quat_to_mat3(const quat_t<num_t>& q)
{
    const num_t xx = q.q[0] * q.q[0] * num_t{2};
    const num_t yy = q.q[1] * q.q[1] * num_t{2};
    const num_t zz = q.q[2] * q.q[2] * num_t{2};
    const num_t xy = q.q[0] * q.q[1];
    const num_t xz = q.q[0] * q.q[2];
    const num_t xw = q.q[0] * q.q[3];
    const num_t yz = q.q[1] * q.q[2];
    const num_t yw = q.q[1] * q.q[3];
    const num_t zw = q.q[2] * q.q[3];

    return mat3_t<num_t>{
        num_t{1} - (yy + zz),   num_t{2} * (xy + zw),   num_t{2} * (xz - yw),
        num_t{2} * (xy - zw),   num_t{1} - (xx + zz),   num_t{2} * (yz + xw),
        num_t{2} * (xz + yw),   num_t{2} * (yz - xw),   num_t{1} - (xx + yy)
    };
}

/*-------------------------------------
    quat_to_mat4
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::mat4_t<num_t> math::quat_to_mat4(const quat_t<num_t>& q)
{
    const num_t xx = q.q[0] * q.q[0] * num_t{2};
    const num_t yy = q.q[1] * q.q[1] * num_t{2};
    const num_t zz = q.q[2] * q.q[2] * num_t{2};
    const num_t xy = q.q[0] * q.q[1];
    const num_t xz = q.q[0] * q.q[2];
    const num_t xw = q.q[0] * q.q[3];
    const num_t yz = q.q[1] * q.q[2];
    const num_t yw = q.q[1] * q.q[3];
    const num_t zw = q.q[2] * q.q[3];

    return mat4_t<num_t>{
        num_t{1} - (yy + zz),   num_t{2} * (xy + zw),   num_t{2} * (xz - yw),   num_t{0},
        num_t{2} * (xy - zw),   num_t{1} - (xx + zz),   num_t{2} * (yz + xw),   num_t{0},
        num_t{2} * (xz + yw),   num_t{2} * (yz - xw),   num_t{1} - (xx + yy),   num_t{0},
        num_t{0},               num_t{0},               num_t{0},               num_t{1}
    };
}

/*-------------------------------------
    mat_to_quat
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::mat_to_quat(const mat3_t<num_t>& m)
{
    num_t s(0);
    num_t trace(m.m[0][0] + m.m[1][1] + m.m[2][2]);
    quat_t<num_t> q;

    if (trace > num_t{0})
    {
        s = std::sqrt(trace + num_t{1});
        q.q[3] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q.q[0] = (m.m[1][2] - m.m[2][1]) * s;
        q.q[1] = (m.m[2][0] - m.m[0][2]) * s;
        q.q[2] = (m.m[0][1] - m.m[1][0]) * s;
    }
    else
    {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.m[1][1] > m.m[0][0])
        {
            i = 1;
        }

        if (m.m[2][2] > m.m[i][i])
        {
            i = 2;
        }

        j = nxt[i];
        k = nxt[j];

        s = std::sqrt((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + num_t{1});

        q[i] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q[3] = (m.m[j][k] - m.m[k][j]) * s;
        q[j] = (m.m[i][j] + m.m[j][i]) * s;
        q[k] = (m.m[i][k] + m.m[k][i]) * s;
    }

    return q;
}

/*-------------------------------------
    mat_to_quat
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::mat_to_quat(const mat4_t<num_t>& m)
{
    num_t s(0);
    num_t trace(m.m[0][0] + m.m[1][1] + m.m[2][2]);
    quat_t<num_t> q;

    if (trace > num_t{0})
    {
        s = std::sqrt(trace + num_t{1});
        q.q[3] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q.q[0] = (m.m[1][2] - m.m[2][1]) * s;
        q.q[1] = (m.m[2][0] - m.m[0][2]) * s;
        q.q[2] = (m.m[0][1] - m.m[1][0]) * s;
    }
    else
    {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.m[1][1] > m.m[0][0])
        {
            i = 1;
        }

        if (m.m[2][2] > m.m[i][i])
        {
            i = 2;
        }

        j = nxt[i];
        k = nxt[j];

        s = std::sqrt((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + num_t{1});

        q[i] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q[3] = (m.m[j][k] - m.m[k][j]) * s;
        q[j] = (m.m[i][j] + m.m[j][i]) * s;
        q[k] = (m.m[i][k] + m.m[k][i]) * s;
    }

    return q;
}

/*-----------------------------------------------------------------------------
    Quaternions & Euler Angles
-----------------------------------------------------------------------------*/
/*
 * Methods to extract quaternion components was found here:
 * http://nic-gamedev.blogspot.com/2011/11/quaternion-math-getting-local-axis.html
 *
 * The equations for these functions can also be found in the quatToMatN() functions.
 */

/*-------------------------------------
    get_x_axis
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::get_x_axis(const math::quat_t<num_t>& q)
{
    return math::vec3_t<num_t>{
        num_t{1} - num_t{2} * (q[1] * q[1] + q[2] * q[2]),
        num_t{2} * (q[0] * q[1] + q[3] * q[2]),
        num_t{2} * (q[0] * q[2] - q[3] * q[1])
    };
}

/*-------------------------------------
    get_y_axis
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::get_y_axis(const math::quat_t<num_t>& q)
{
    return math::vec3_t<num_t>{
        num_t{2} * (q[0] * q[1] - q[3] * q[2]),
        num_t{1} - num_t{2} * (q[0] * q[0] + q[2] * q[2]),
        num_t{2} * (q[1] * q[2] + q[3] * q[0])
    };
}

/*-------------------------------------
    get_z_axis
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
math::vec3_t<num_t> math::get_z_axis(const math::quat_t<num_t>& q)
{
    return math::vec3_t<num_t>{
        num_t{2} * (q[0] * q[2] + q[3] * q[1]),
        num_t{2} * (q[1] * q[2] - q[3] * q[0]),
        num_t{1} - num_t{2} * (q[0] * q[0] + q[1] * q[1])
    };
}

/*-------------------------------------
    get_angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
num_t math::get_angle(const quat_t<num_t>& q)
{
    return num_t{std::acos(q.q[3] * num_t{2})};
}

/*-------------------------------------
    to_euler
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec3_t<num_t> math::to_euler(const quat_t<num_t>& q)
{
    const num_t xx = q.q[0] * q.q[0];
    const num_t yy = q.q[1] * q.q[1];
    const num_t zz = q.q[2] * q.q[2];

    const num_t pitch = std::atan2(
        num_t{2} * ((q.q[3] * q.q[0]) * (q.q[1] * q.q[2])),
        num_t{1} - (num_t{2} * (xx + yy))
    );

    const num_t yaw = std::asin(
        num_t{2} * ((q.q[3] * q.q[1]) - (q.q[2] * q.q[0]))
    );

    const num_t roll = std::atan2(
        num_t{2} * ((q.q[3] * q.q[2]) + (q.q[0] * q.q[1])),
        num_t{1}-(num_t{2} * (yy + zz))
    );

    return vec3_t<num_t>{pitch, yaw, roll};
}

/*-------------------------------------
    from_euler
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::from_euler(const math::vec3_t<num_t>& angles)
{
    const math::vec3&& a = angles * num_t{0.5};

    const num_t cp = std::cos(a[0]);
    const num_t sp = std::sin(a[0]);

    const num_t cy = std::cos(a[1]);
    const num_t sy = std::sin(a[1]);

    const num_t cr = std::cos(a[2]);
    const num_t sr = std::sin(a[2]);

    return math::quat_t<num_t>{
        (sy * cp * cr) - (cy * sp * sr),
        (cy * sp * cr) + (sy * cp * sr),
        (cy * cp * sr) - (sy * sp * cr),
        (cy * cp * cr) + (sy * sp * sr)
    };
}

/*-------------------------------------
    from_euler
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::from_euler(num_t pitch, num_t yaw, num_t roll)
{
    return from_euler(math::vec3{pitch, yaw, roll});
}

/*-------------------------------------
    to_axis_angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
void math::to_axis_angle(const quat_t<num_t>& q, vec3_t<num_t>& outAxis, num_t& outAngle)
{
    num_t s = std::sqrt(num_t{1} - (q.q[3] * q.q[3]));

    if (math::abs(s) <= num_t{0})
    {
        s = num_t{1};
    }
    else
    {
        s = num_t{1} / s;
    }

    outAxis.v[0] = q.q[0] * s;
    outAxis.v[1] = q.q[1] * s;
    outAxis.v[2] = q.q[2] * s;
    outAngle = std::acos(q.q[3]) * num_t{2};
}

/*-------------------------------------
    to_axis_angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::vec4_t<num_t> math::to_axis_angle(const quat_t<num_t>& q)
{
    const num_t c = q.q[3];
    num_t s = std::sqrt(num_t{1}-c * c);

    if (math::abs(s) <= num_t{0})
    {
        s = num_t{1};
    }
    else
    {
        s = num_t{1} / s;
    }

    return vec4_t<num_t>{
        q.q[0] * s,
        q.q[1] * s,
        q.q[2] * s,
        std::acos(q.q[3]) * num_t{2}
    };
}

/*-------------------------------------
    from_axis_angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::from_axis_angle(const vec3_t<num_t>& axis, num_t angle)
{
    const num_t&& a = angle * num_t{0.5};
    const num_t&& s = std::sin(a);
    const num_t&& c = std::cos(a);

    return quat_t<num_t>{
        s * axis.v[0],
        s * axis.v[1],
        s * axis.v[2],
        c
    };
}

/*-------------------------------------
    from_axis_angle
-------------------------------------*/
template <typename num_t> inline LS_INLINE
math::quat_t<num_t> math::from_axis_angle(const vec4_t<num_t>& v)
{
    const num_t&& a = v.v[3] * num_t{0.5};
    const num_t&& s = std::sin(a);
    const num_t&& c = std::cos(a);

    return quat_t<num_t>{
        s * v.v[0],
        s * v.v[1],
        s * v.v[2],
        c
    };
}



} // end ls namespace

#endif /* LS_MATH_QUAT_UTILS_IMPL_H */
