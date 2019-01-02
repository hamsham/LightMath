
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{
    // transpose *this, then perform the multiplication
    const __m128 trn0 = _mm_unpacklo_ps(this->m[0].simd, this->m[1].simd);
    const __m128 trn1 = _mm_unpacklo_ps(this->m[2].simd, this->m[3].simd);
    const __m128 trn2 = _mm_unpackhi_ps(this->m[0].simd, this->m[1].simd);
    const __m128 trn3 = _mm_unpackhi_ps(this->m[2].simd, this->m[3].simd);
    const __m128 row0 = _mm_movelh_ps(trn0, trn1);
    const __m128 row1 = _mm_movehl_ps(trn1, trn0);
    const __m128 row2 = _mm_movelh_ps(trn2, trn3);
    const __m128 row3 = _mm_movehl_ps(trn3, trn2);

    mat4_t<float> ret;

    for (unsigned i = 0; i < 4; ++i)
    {
        // multiply all rows, then sum them
        const __m128 s = n.m[i].simd;

        const __m128 mul0 = _mm_mul_ps(s, row0);
        const __m128 mul1 = _mm_mul_ps(s, row1);
        const __m128 mul2 = _mm_mul_ps(s, row2);
        const __m128 mul3 = _mm_mul_ps(s, row3);

        // transpose the rows into columns
        const __m128 col0 = _mm_unpacklo_ps(mul0, mul1);
        const __m128 col1 = _mm_unpacklo_ps(mul2, mul3);
        const __m128 col2 = _mm_unpackhi_ps(mul0, mul1);
        const __m128 col3 = _mm_unpackhi_ps(mul2, mul3);

        // sum the columns
        const __m128 add0 = _mm_movelh_ps(col0, col1);
        const __m128 add1 = _mm_movehl_ps(col1, col0);
        const __m128 add2 = _mm_movelh_ps(col2, col3);
        const __m128 add3 = _mm_movehl_ps(col3, col2);

        ret[i].simd = _mm_add_ps(_mm_add_ps(_mm_add_ps(add0, add1), add2), add3);
    }

    return ret;
}



template <>
inline LS_INLINE mat4_t<float>& mat4_t<float>::operator*=(const mat4_t<float>& n)
{
    // transpose *this, then perform the multiplication
    const __m128 trn0 = _mm_unpacklo_ps(this->m[0].simd, this->m[1].simd);
    const __m128 trn1 = _mm_unpacklo_ps(this->m[2].simd, this->m[3].simd);
    const __m128 trn2 = _mm_unpackhi_ps(this->m[0].simd, this->m[1].simd);
    const __m128 trn3 = _mm_unpackhi_ps(this->m[2].simd, this->m[3].simd);
    const __m128 row0 = _mm_movelh_ps(trn0, trn1);
    const __m128 row1 = _mm_movehl_ps(trn1, trn0);
    const __m128 row2 = _mm_movelh_ps(trn2, trn3);
    const __m128 row3 = _mm_movehl_ps(trn3, trn2);

    for (unsigned i = 0; i < 4; ++i)
    {
        // multiply all rows, then sum them
        const __m128 s = n.m[i].simd;

        const __m128 mul0 = _mm_mul_ps(s, row0);
        const __m128 mul1 = _mm_mul_ps(s, row1);
        const __m128 mul2 = _mm_mul_ps(s, row2);
        const __m128 mul3 = _mm_mul_ps(s, row3);

        // transpose the rows into columns
        const __m128 col0 = _mm_unpacklo_ps(mul0, mul1);
        const __m128 col1 = _mm_unpacklo_ps(mul2, mul3);
        const __m128 col2 = _mm_unpackhi_ps(mul0, mul1);
        const __m128 col3 = _mm_unpackhi_ps(mul2, mul3);

        // sum the columns
        const __m128 add0 = _mm_movelh_ps(col0, col1);
        const __m128 add1 = _mm_movehl_ps(col1, col0);
        const __m128 add2 = _mm_movelh_ps(col2, col3);
        const __m128 add3 = _mm_movehl_ps(col3, col2);

        this->m[i].simd = _mm_add_ps(_mm_add_ps(_mm_add_ps(add0, add1), add2), add3);
    }

    return *this;
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
template <> inline LS_INLINE
vec4_t<float> mat4_t<float>::operator*(const vec4_t<float>& v) const
{
    const __m128 row0(_mm_mul_ps(m[0].simd, _mm_shuffle_ps(v.simd, v.simd, 0x00)));
    const __m128 row1(_mm_mul_ps(m[1].simd, _mm_shuffle_ps(v.simd, v.simd, 0x55)));
    const __m128 row2(_mm_mul_ps(m[2].simd, _mm_shuffle_ps(v.simd, v.simd, 0xAA)));
    const __m128 row3(_mm_mul_ps(m[3].simd, _mm_shuffle_ps(v.simd, v.simd, 0xFF)));

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
