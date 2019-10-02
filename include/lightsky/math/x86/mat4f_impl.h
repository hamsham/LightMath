
#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{

    #if 1
        const __m128* const tm = reinterpret_cast<const __m128*>(this);
        const __m256 col0 = _mm256_broadcast_ps(tm+0);
        const __m256 col1 = _mm256_broadcast_ps(tm+1);
        const __m256 col2 = _mm256_broadcast_ps(tm+2);
        const __m256 col3 = _mm256_broadcast_ps(tm+3);

        const float* const nm = reinterpret_cast<const float*>(&n);
        __m256 r01;
        __m256 r23;
        __m256 temp;

        {
            temp = _mm256_loadu2_m128(nm+4, nm+0);
            r01 = _mm256_mul_ps(  col0, _mm256_permute_ps(temp, 0x00));
            r01 = _mm256_fmadd_ps(col1, _mm256_permute_ps(temp, 0x55), r01);
            r01 = _mm256_fmadd_ps(col2, _mm256_permute_ps(temp, 0xAA), r01);
            r01 = _mm256_fmadd_ps(col3, _mm256_permute_ps(temp, 0xFF), r01);
        }
        {
            temp = _mm256_loadu2_m128(nm+12, nm+8);
            r23 = _mm256_mul_ps(  col0, _mm256_permute_ps(temp, 0x00));
            r23 = _mm256_fmadd_ps(col1, _mm256_permute_ps(temp, 0x55), r23);
            r23 = _mm256_fmadd_ps(col2, _mm256_permute_ps(temp, 0xAA), r23);
            r23 = _mm256_fmadd_ps(col3, _mm256_permute_ps(temp, 0xFF), r23);
        }

        alignas(sizeof(__m256)) mat4_t<float> ret;

        _mm256_store_ps(reinterpret_cast<float*>(&ret),   r01);
        _mm256_store_ps(reinterpret_cast<float*>(&ret)+8, r23);

        return ret;
    #else
        const __m128 col0 = this->m[0].simd;
        const __m128 col1 = this->m[1].simd;
        const __m128 col2 = this->m[2].simd;
        const __m128 col3 = this->m[3].simd;

        __m128 r0;
        __m128 r1;
        __m128 r2;
        __m128 r3;

        {
            r0 = _mm_mul_ps(  col0, _mm_permute_ps(n[0].simd, 0x00));
            r0 = _mm_fmadd_ps(col1, _mm_permute_ps(n[0].simd, 0x55), r0);
            r0 = _mm_fmadd_ps(col2, _mm_permute_ps(n[0].simd, 0xAA), r0);
            r0 = _mm_fmadd_ps(col3, _mm_permute_ps(n[0].simd, 0xFF), r0);
        }
        {
            r1 = _mm_mul_ps(  col0, _mm_permute_ps(n[1].simd, 0x00));
            r1 = _mm_fmadd_ps(col1, _mm_permute_ps(n[1].simd, 0x55), r1);
            r1 = _mm_fmadd_ps(col2, _mm_permute_ps(n[1].simd, 0xAA), r1);
            r1 = _mm_fmadd_ps(col3, _mm_permute_ps(n[1].simd, 0xFF), r1);
        }
        {
            r2 = _mm_mul_ps(  col0, _mm_permute_ps(n[2].simd, 0x00));
            r2 = _mm_fmadd_ps(col1, _mm_permute_ps(n[2].simd, 0x55), r2);
            r2 = _mm_fmadd_ps(col2, _mm_permute_ps(n[2].simd, 0xAA), r2);
            r2 = _mm_fmadd_ps(col3, _mm_permute_ps(n[2].simd, 0xFF), r2);
        }
        {
            r3 = _mm_mul_ps(  col0, _mm_permute_ps(n[3].simd, 0x00));
            r3 = _mm_fmadd_ps(col1, _mm_permute_ps(n[3].simd, 0x55), r3);
            r3 = _mm_fmadd_ps(col2, _mm_permute_ps(n[3].simd, 0xAA), r3);
            r3 = _mm_fmadd_ps(col3, _mm_permute_ps(n[3].simd, 0xFF), r3);
        }

        alignas(sizeof(__m128)) mat4_t<float> ret;

        _mm_store_ps(reinterpret_cast<float*>(&ret)+0,  r0);
        _mm_store_ps(reinterpret_cast<float*>(&ret)+4,  r1);
        _mm_store_ps(reinterpret_cast<float*>(&ret)+8,  r2);
        _mm_store_ps(reinterpret_cast<float*>(&ret)+12, r3);

        return ret;
    #endif
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
    const __m128i* nm = reinterpret_cast<const __m128i*>(&n);
    const __m128 s0 = _mm_castsi128_ps(_mm_lddqu_si128(nm+0));
    const __m128 s1 = _mm_castsi128_ps(_mm_lddqu_si128(nm+1));
    const __m128 s2 = _mm_castsi128_ps(_mm_lddqu_si128(nm+2));
    const __m128 s3 = _mm_castsi128_ps(_mm_lddqu_si128(nm+3));

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
    const __m128i* pM = reinterpret_cast<const __m128i*>(this);
    const __m128 x = _mm_loadu_ps(&v);

    __m128 v0 = _mm_mul_ps(  _mm_castsi128_ps(_mm_lddqu_si128(pM+0)), _mm_permute_ps(x, 0x00));
    __m128 v1 = _mm_fmadd_ps(_mm_castsi128_ps(_mm_lddqu_si128(pM+1)), _mm_permute_ps(x, 0x55), v0);
    __m128 v2 = _mm_fmadd_ps(_mm_castsi128_ps(_mm_lddqu_si128(pM+2)), _mm_permute_ps(x, 0xAA), v1);
    __m128 v3 = _mm_fmadd_ps(_mm_castsi128_ps(_mm_lddqu_si128(pM+3)), _mm_permute_ps(x, 0xFF), v2);

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
