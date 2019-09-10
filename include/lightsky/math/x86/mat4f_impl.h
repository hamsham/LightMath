
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{
    const float* const tm = reinterpret_cast<const float*>(this);
    const __m128 col0 = _mm_loadu_ps(tm+0);
    const __m128 col1 = _mm_loadu_ps(tm+4);
    const __m128 col2 = _mm_loadu_ps(tm+8);
    const __m128 col3 = _mm_loadu_ps(tm+12);

    const float* const nm = reinterpret_cast<const float*>(n.m);

    __m128 r0 = _mm_mul_ps(col0, _mm_broadcast_ss(nm+0));
    __m128 r1 = _mm_mul_ps(col0, _mm_broadcast_ss(nm+4));
    __m128 r2 = _mm_mul_ps(col0, _mm_broadcast_ss(nm+8));
    __m128 r3 = _mm_mul_ps(col0, _mm_broadcast_ss(nm+12));
    
    {
        r0 = _mm_fmadd_ps(col1, _mm_broadcast_ss(nm+1), r0);
        r0 = _mm_fmadd_ps(col2, _mm_broadcast_ss(nm+2), r0);
        r0 = _mm_fmadd_ps(col3, _mm_broadcast_ss(nm+3), r0);
    }

    {
        r1 = _mm_fmadd_ps(col1, _mm_broadcast_ss(nm+5), r1);
        r1 = _mm_fmadd_ps(col2, _mm_broadcast_ss(nm+6), r1);
        r1 = _mm_fmadd_ps(col3, _mm_broadcast_ss(nm+7), r1);
    }

    {
        r2 = _mm_fmadd_ps(col1, _mm_broadcast_ss(nm+9), r2);
        r2 = _mm_fmadd_ps(col2, _mm_broadcast_ss(nm+10), r2);
        r2 = _mm_fmadd_ps(col3, _mm_broadcast_ss(nm+11), r2);
    }

    {
        r3 = _mm_fmadd_ps(col1, _mm_broadcast_ss(nm+13), r3);
        r3 = _mm_fmadd_ps(col2, _mm_broadcast_ss(nm+14), r3);
        r3 = _mm_fmadd_ps(col3, _mm_broadcast_ss(nm+15), r3);
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
    const float* nm = reinterpret_cast<const float*>(&n);
    const __m128 s0 = _mm_loadu_ps(nm+0);
    const __m128 s1 = _mm_loadu_ps(nm+4);
    const __m128 s2 = _mm_loadu_ps(nm+8);
    const __m128 s3 = _mm_loadu_ps(nm+12);

    _mm_storeu_ps(reinterpret_cast<float*>(m+0), _mm_fmadd_ps(s0, row3, _mm_fmadd_ps(s0, row2, _mm_fmadd_ps(s0, row1, _mm_mul_ps(s0, row0)))));
    _mm_storeu_ps(reinterpret_cast<float*>(m+1), _mm_fmadd_ps(s1, row3, _mm_fmadd_ps(s1, row2, _mm_fmadd_ps(s1, row1, _mm_mul_ps(s1, row0)))));
    _mm_storeu_ps(reinterpret_cast<float*>(m+2), _mm_fmadd_ps(s2, row3, _mm_fmadd_ps(s2, row2, _mm_fmadd_ps(s2, row1, _mm_mul_ps(s2, row0)))));
    _mm_storeu_ps(reinterpret_cast<float*>(m+3), _mm_fmadd_ps(s3, row3, _mm_fmadd_ps(s3, row2, _mm_fmadd_ps(s3, row1, _mm_mul_ps(s3, row0)))));

    return *this;
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
template <> inline LS_INLINE
vec4_t<float> mat4_t<float>::operator*(const vec4_t<float>& v) const
{
    const float* x = &v;
    __m128 v0 = _mm_mul_ps(_mm_loadu_ps(&m[0]), _mm_broadcast_ss(x+0));
    __m128 v1 = _mm_fmadd_ps(_mm_loadu_ps(&m[1]), _mm_broadcast_ss(x+1), v0);
    __m128 v2 = _mm_fmadd_ps(_mm_loadu_ps(&m[2]), _mm_broadcast_ss(x+2), v1);
    __m128 v3 = _mm_fmadd_ps(_mm_loadu_ps(&m[3]), _mm_broadcast_ss(x+3), v2);

    return math::vec4_t<float>{v3};
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
inline LS_INLINE vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
    /*
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
    */

    /*
    const __m128 s = _mm_load_ps(v);

    __m128 row0 = _mm_mul_ps(s, _mm_load_ps(m.m[0].v));
    __m128 row1 = _mm_mul_ps(s, _mm_load_ps(m.m[1].v));
    __m128 row2 = _mm_mul_ps(s, _mm_load_ps(m.m[2].v));
    __m128 row3 = _mm_mul_ps(s, _mm_load_ps(m.m[3].v));
    */
    const __m128 s = this->simd;

    __m128 row0 = _mm_mul_ps(s, _mm_loadu_ps(&m[0]));
    __m128 row1 = _mm_mul_ps(s, _mm_loadu_ps(&m[1]));
    __m128 row2 = _mm_mul_ps(s, _mm_loadu_ps(&m[2]));
    __m128 row3 = _mm_mul_ps(s, _mm_loadu_ps(&m[3]));

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
