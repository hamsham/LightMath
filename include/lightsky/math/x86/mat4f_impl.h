
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{
    const __m128 col0 = this->m[0].simd;
    const __m128 col1 = this->m[1].simd;
    const __m128 col2 = this->m[2].simd;
    const __m128 col3 = this->m[3].simd;

    const __m128 row00 = _mm_shuffle_ps(n.m[0].simd, n.m[0].simd, 0x00);
    const __m128 row01 = _mm_shuffle_ps(n.m[0].simd, n.m[0].simd, 0x55);
    const __m128 row02 = _mm_shuffle_ps(n.m[0].simd, n.m[0].simd, 0xAA);
    const __m128 row03 = _mm_shuffle_ps(n.m[0].simd, n.m[0].simd, 0xFF);

    const __m128 row10 = _mm_shuffle_ps(n.m[1].simd, n.m[1].simd, 0x00);
    const __m128 row11 = _mm_shuffle_ps(n.m[1].simd, n.m[1].simd, 0x55);
    const __m128 row12 = _mm_shuffle_ps(n.m[1].simd, n.m[1].simd, 0xAA);
    const __m128 row13 = _mm_shuffle_ps(n.m[1].simd, n.m[1].simd, 0xFF);

    const __m128 row20 = _mm_shuffle_ps(n.m[2].simd, n.m[2].simd, 0x00);
    const __m128 row21 = _mm_shuffle_ps(n.m[2].simd, n.m[2].simd, 0x55);
    const __m128 row22 = _mm_shuffle_ps(n.m[2].simd, n.m[2].simd, 0xAA);
    const __m128 row23 = _mm_shuffle_ps(n.m[2].simd, n.m[2].simd, 0xFF);

    const __m128 row30 = _mm_shuffle_ps(n.m[3].simd, n.m[3].simd, 0x00);
    const __m128 row31 = _mm_shuffle_ps(n.m[3].simd, n.m[3].simd, 0x55);
    const __m128 row32 = _mm_shuffle_ps(n.m[3].simd, n.m[3].simd, 0xAA);
    const __m128 row33 = _mm_shuffle_ps(n.m[3].simd, n.m[3].simd, 0xFF);

    __m128 r0 = _mm_mul_ps(col0, row00);
    __m128 r1 = _mm_mul_ps(col0, row10);
    __m128 r2 = _mm_mul_ps(col0, row20);
    __m128 r3 = _mm_mul_ps(col0, row30);

    {
        r0 = _mm_fmadd_ps(col1, row01, r0);
        r0 = _mm_fmadd_ps(col2, row02, r0);
        r0 = _mm_fmadd_ps(col3, row03, r0);
    }
    {
        r1 = _mm_fmadd_ps(col1, row11, r1);
        r1 = _mm_fmadd_ps(col2, row12, r1);
        r1 = _mm_fmadd_ps(col3, row13, r1);
    }
    {
        r2 = _mm_fmadd_ps(col1, row21, r2);
        r2 = _mm_fmadd_ps(col2, row22, r2);
        r2 = _mm_fmadd_ps(col3, row23, r2);
    }
    {
        r3 = _mm_fmadd_ps(col1, row31, r3);
        r3 = _mm_fmadd_ps(col2, row32, r3);
        r3 = _mm_fmadd_ps(col3, row33, r3);
    }

    return mat4_t<float>{
        {r0},
        {r1},
        {r2},
        {r3},
    };
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

    // multiply all rows, then sum them
    const __m128 s0 = n.m[0].simd;
    const __m128 s1 = n.m[1].simd;
    const __m128 s2 = n.m[2].simd;
    const __m128 s3 = n.m[3].simd;

    this->m[0].simd = _mm_fmadd_ps(s0, row3, _mm_fmadd_ps(s0, row2, _mm_fmadd_ps(s0, row1, _mm_mul_ps(s0, row0))));
    this->m[1].simd = _mm_fmadd_ps(s1, row3, _mm_fmadd_ps(s1, row2, _mm_fmadd_ps(s1, row1, _mm_mul_ps(s1, row0))));
    this->m[2].simd = _mm_fmadd_ps(s2, row3, _mm_fmadd_ps(s2, row2, _mm_fmadd_ps(s2, row1, _mm_mul_ps(s2, row0))));
    this->m[3].simd = _mm_fmadd_ps(s3, row3, _mm_fmadd_ps(s3, row2, _mm_fmadd_ps(s3, row1, _mm_mul_ps(s3, row0))));

    return *this;
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
template <> inline LS_INLINE
vec4_t<float> mat4_t<float>::operator*(const vec4_t<float>& v) const
{
    math::vec4_t<float> ret{_mm_mul_ps(m[0].simd, _mm_shuffle_ps(v.simd, v.simd, 0x00))};
    ret.simd = _mm_fmadd_ps(m[1].simd, _mm_shuffle_ps(v.simd, v.simd, 0x55), ret.simd);
    ret.simd = _mm_fmadd_ps(m[2].simd, _mm_shuffle_ps(v.simd, v.simd, 0xAA), ret.simd);
    ret.simd = _mm_fmadd_ps(m[3].simd, _mm_shuffle_ps(v.simd, v.simd, 0xFF), ret.simd);

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

    // transpose the rows into columns
    const __m128 col0 = _mm_shuffle_ps(row0, row0, 0x00);
    const __m128 col1 = _mm_shuffle_ps(row1, row1, 0x55);
    const __m128 col2 = _mm_shuffle_ps(row2, row2, 0xAA);
    const __m128 col3 = _mm_shuffle_ps(row3, row3, 0xFF);

    return vec4_t<float>{_mm_add_ps(_mm_add_ps(_mm_add_ps(col0, col1), col2), col3)};
}



} //end math namespace
} //end ls namespace
