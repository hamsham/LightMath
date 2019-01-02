
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{
    const __m128 self[4] = {
        this->m[0].simd,
        this->m[1].simd,
        this->m[2].simd,
        this->m[3].simd
    };

    // transpose, then multiply the matrices
    const __m128 t0 = _mm_unpacklo_ps(n.m[0].simd, n.m[1].simd);
    const __m128 t1 = _mm_unpacklo_ps(n.m[2].simd, n.m[3].simd);
    const __m128 t2 = _mm_unpackhi_ps(n.m[0].simd, n.m[1].simd);
    const __m128 t3 = _mm_unpackhi_ps(n.m[2].simd, n.m[3].simd);

    const __m128 t[4] = {
        _mm_movelh_ps(t0, t1),
        _mm_movehl_ps(t1, t0),
        _mm_movelh_ps(t2, t3),
        _mm_movehl_ps(t3, t2)
    };

    mat4_t<float> ret;

    for (unsigned i = 0; i < 4; ++i)
    {
        const __m128 ti = t[i];
        const __m128 row0(_mm_mul_ps(self[0], _mm_shuffle_ps(ti, ti, 0x00)));
        const __m128 row1(_mm_mul_ps(self[1], _mm_shuffle_ps(ti, ti, 0x55)));
        const __m128 row2(_mm_mul_ps(self[2], _mm_shuffle_ps(ti, ti, 0xAA)));
        const __m128 row3(_mm_mul_ps(self[3], _mm_shuffle_ps(ti, ti, 0xFF)));

        ret.m[i].simd = _mm_add_ps(row0, _mm_add_ps(row1, _mm_add_ps(row2, row3)));
    }

    return ret;
}



template <>
inline LS_INLINE mat4_t<float>& mat4_t<float>::operator*=(const mat4_t<float>& n)
{
    const __m128 self[4] = {
        this->m[0].simd,
        this->m[1].simd,
        this->m[2].simd,
        this->m[3].simd
    };

    // transpose, then multiply the matrices
    const __m128 t0 = _mm_unpacklo_ps(n.m[0].simd, n.m[1].simd);
    const __m128 t1 = _mm_unpacklo_ps(n.m[2].simd, n.m[3].simd);
    const __m128 t2 = _mm_unpackhi_ps(n.m[0].simd, n.m[1].simd);
    const __m128 t3 = _mm_unpackhi_ps(n.m[2].simd, n.m[3].simd);

    const __m128 t[4] = {
        _mm_movelh_ps(t0, t1),
        _mm_movehl_ps(t1, t0),
        _mm_movelh_ps(t2, t3),
        _mm_movehl_ps(t3, t2)
    };

    for (unsigned i = 0; i < 4; ++i)
    {
        const __m128 ti = t[i];
        const __m128 row0(_mm_mul_ps(self[0], _mm_shuffle_ps(ti, ti, 0x00)));
        const __m128 row1(_mm_mul_ps(self[1], _mm_shuffle_ps(ti, ti, 0x55)));
        const __m128 row2(_mm_mul_ps(self[2], _mm_shuffle_ps(ti, ti, 0xAA)));
        const __m128 row3(_mm_mul_ps(self[3], _mm_shuffle_ps(ti, ti, 0xFF)));

        this->m[i].simd = _mm_add_ps(row0, _mm_add_ps(row1, _mm_add_ps(row2, row3)));
    }

    return *this;
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
template <> inline LS_INLINE
vec4_t<float> mat4_t<float>::operator*(const vec4_t<float>& v) const
{
    __m128 row0(_mm_mul_ps(m[0].simd, _mm_set1_ps(v.v[0])));
    __m128 row1(_mm_mul_ps(m[1].simd, _mm_set1_ps(v.v[1])));
    __m128 row2(_mm_mul_ps(m[2].simd, _mm_set1_ps(v.v[2])));
    __m128 row3(_mm_mul_ps(m[3].simd, _mm_set1_ps(v.v[3])));

    math::vec4_t<float> ret{row0};
    ret.simd = _mm_add_ps(ret.simd, row1);
    ret.simd = _mm_add_ps(ret.simd, row2);
    ret.simd = _mm_add_ps(ret.simd, row3);

    return ret;
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
inline LS_INLINE vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
    const __m128 s = this->simd;
    __m128 row0(_mm_mul_ps(s, m.m[0].simd));
    __m128 row1(_mm_mul_ps(s, m.m[1].simd));
    __m128 row2(_mm_mul_ps(s, m.m[2].simd));
    __m128 row3(_mm_mul_ps(s, m.m[3].simd));

    // transpose, then add
    //_MM_TRANSPOSE4_PS(row0, row1, row2, row3);

    const __m128 t0 = _mm_unpacklo_ps(row0, row1);
    const __m128 t1 = _mm_unpacklo_ps(row2, row3);
    const __m128 t2 = _mm_unpackhi_ps(row0, row1);
    const __m128 t3 = _mm_unpackhi_ps(row2, row3);

    row0 = _mm_movelh_ps(t0, t1);
    row1 = _mm_movehl_ps(t1, t0);
    row2 = _mm_movelh_ps(t2, t3);
    row3 = _mm_movehl_ps(t3, t2);

    return vec4_t<float>{_mm_add_ps(_mm_add_ps(_mm_add_ps(row0, row1), row2), row3)};
}



} //end math namespace
} //end ls namespace
