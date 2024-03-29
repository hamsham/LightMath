
#ifndef LS_MATH_MAT4F_IMPL_H
#define LS_MATH_MAT4F_IMPL_H

#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {



/*-------------------------------------
    Matrix-Matrix Math Operations
-------------------------------------*/
template <>
inline LS_INLINE mat4_t<float> mat4_t<float>::operator*(const mat4_t<float>& n) const
{
    #ifdef LS_X86_AVX2
        alignas(sizeof(__m256)) mat4_t<float> ret;

        const __m256 col0 = _mm256_insertf128_ps(_mm256_castps128_ps256(m[0].simd), m[0].simd, 1);
        const __m256 col1 = _mm256_insertf128_ps(_mm256_castps128_ps256(m[1].simd), m[1].simd, 1);
        const __m256 col2 = _mm256_insertf128_ps(_mm256_castps128_ps256(m[2].simd), m[2].simd, 1);
        const __m256 col3 = _mm256_insertf128_ps(_mm256_castps128_ps256(m[3].simd), m[3].simd, 1);

        const __m256 temp0 = _mm256_insertf128_ps(_mm256_castps128_ps256(n[0].simd), n[1].simd, 1);
        const __m256 temp1 = _mm256_insertf128_ps(_mm256_castps128_ps256(n[2].simd), n[3].simd, 1);

        __m256 r01;
        __m256 r23;

        r01 = _mm256_mul_ps(  col0, _mm256_permute_ps(temp0, 0x00));
        r23 = _mm256_mul_ps(  col0, _mm256_permute_ps(temp1, 0x00));
        r01 = _mm256_fmadd_ps(col1, _mm256_permute_ps(temp0, 0x55), r01);
        r23 = _mm256_fmadd_ps(col1, _mm256_permute_ps(temp1, 0x55), r23);
        r01 = _mm256_fmadd_ps(col2, _mm256_permute_ps(temp0, 0xAA), r01);
        r23 = _mm256_fmadd_ps(col2, _mm256_permute_ps(temp1, 0xAA), r23);
        _mm256_store_ps(ret.m[0].v, _mm256_fmadd_ps(col3, _mm256_permute_ps(temp0, 0xFF), r01));
        _mm256_store_ps(ret.m[2].v, _mm256_fmadd_ps(col3, _mm256_permute_ps(temp1, 0xFF), r23));

        return ret;
    #else
        alignas(sizeof(__m128)) mat4_t<float> ret;
        const __m128 col0 = this->m[0].simd;
        const __m128 col1 = this->m[1].simd;
        const __m128 col2 = this->m[2].simd;
        const __m128 col3 = this->m[3].simd;

        __m128 r0;
        __m128 r1;
        __m128 r2;
        __m128 r3;

        {
            r0 = _mm_mul_ps(           col0, _mm_shuffle_ps(n[0].simd, n[0].simd, 0x00));
            r0 = _mm_add_ps(_mm_mul_ps(col1, _mm_shuffle_ps(n[0].simd, n[0].simd, 0x55)), r0);
            r0 = _mm_add_ps(_mm_mul_ps(col2, _mm_shuffle_ps(n[0].simd, n[0].simd, 0xAA)), r0);
            r0 = _mm_add_ps(_mm_mul_ps(col3, _mm_shuffle_ps(n[0].simd, n[0].simd, 0xFF)), r0);
            _mm_store_ps(reinterpret_cast<float*>(&ret)+0,  r0);
        }
        {
            r1 = _mm_mul_ps(           col0, _mm_shuffle_ps(n[1].simd, n[1].simd, 0x00));
            r1 = _mm_add_ps(_mm_mul_ps(col1, _mm_shuffle_ps(n[1].simd, n[1].simd, 0x55)), r1);
            r1 = _mm_add_ps(_mm_mul_ps(col2, _mm_shuffle_ps(n[1].simd, n[1].simd, 0xAA)), r1);
            r1 = _mm_add_ps(_mm_mul_ps(col3, _mm_shuffle_ps(n[1].simd, n[1].simd, 0xFF)), r1);
            _mm_store_ps(reinterpret_cast<float*>(&ret)+4,  r1);
        }
        {
            r2 = _mm_mul_ps(           col0, _mm_shuffle_ps(n[2].simd, n[2].simd, 0x00));
            r2 = _mm_add_ps(_mm_mul_ps(col1, _mm_shuffle_ps(n[2].simd, n[2].simd, 0x55)), r2);
            r2 = _mm_add_ps(_mm_mul_ps(col2, _mm_shuffle_ps(n[2].simd, n[2].simd, 0xAA)), r2);
            r2 = _mm_add_ps(_mm_mul_ps(col3, _mm_shuffle_ps(n[2].simd, n[2].simd, 0xFF)), r2);
            _mm_store_ps(reinterpret_cast<float*>(&ret)+8,  r2);
        }
        {
            r3 = _mm_mul_ps(           col0, _mm_shuffle_ps(n[3].simd, n[3].simd, 0x00));
            r3 = _mm_add_ps(_mm_mul_ps(col1, _mm_shuffle_ps(n[3].simd, n[3].simd, 0x55)), r3);
            r3 = _mm_add_ps(_mm_mul_ps(col2, _mm_shuffle_ps(n[3].simd, n[3].simd, 0xAA)), r3);
            r3 = _mm_add_ps(_mm_mul_ps(col3, _mm_shuffle_ps(n[3].simd, n[3].simd, 0xFF)), r3);
            _mm_store_ps(reinterpret_cast<float*>(&ret)+12, r3);
        }

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
    const __m128 s = _mm_loadu_ps(v.v);
    const __m128 a = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(s), 0x00));
    const __m128 b = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(s), 0x55));
    const __m128 c = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(s), 0xAA));
    const __m128 d = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(s), 0xFF));

    #ifdef LS_X86_FMA
        const __m128 v0 = _mm_mul_ps(  this->m[0].simd, a);
        const __m128 v1 = _mm_fmadd_ps(this->m[1].simd, b, v0);
        const __m128 v2 = _mm_mul_ps(  this->m[2].simd, c);
        const __m128 v3 = _mm_fmadd_ps(this->m[3].simd, d, v2);
    #else
        const __m128 v0 = _mm_mul_ps(this->m[0].simd, a);
        const __m128 v1 = _mm_add_ps(_mm_mul_ps(this->m[1].simd, b), v0);
        const __m128 v2 = _mm_mul_ps(this->m[2].simd, c);
        const __m128 v3 = _mm_add_ps(_mm_mul_ps(this->m[3].simd, d), v2);
    #endif

    return math::vec4_t<float>{_mm_add_ps(v1, v3)};
}



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
inline LS_INLINE vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
    #if 1
        __m128 row0 = _mm_mul_ps(this->simd, m[0].simd);
        __m128 row1 = _mm_mul_ps(this->simd, m[1].simd);
        __m128 row2 = _mm_mul_ps(this->simd, m[2].simd);
        __m128 row3 = _mm_mul_ps(this->simd, m[3].simd);

        // transpose, then add
        const __m128 t0 = _mm_unpacklo_ps(row0, row1);
        const __m128 t1 = _mm_unpacklo_ps(row2, row3);
        const __m128 t2 = _mm_unpackhi_ps(row0, row1);
        const __m128 t3 = _mm_unpackhi_ps(row2, row3);

        __m128 sum0 = _mm_add_ps(_mm_movehl_ps(t1, t0), _mm_movelh_ps(t0, t1));
        __m128 sum1 = _mm_add_ps(_mm_movehl_ps(t3, t2), _mm_movelh_ps(t2, t3));

        return vec4_t<float>{_mm_add_ps(sum1, sum0)};
    #else

        alignas(sizeof(__m256)) float         temp[16];
        alignas(sizeof(__m256)) mat4_t<float> ret;

        _mm_store_ps(temp+0,  _mm_mul_ps(this->simd, m.m[0].simd));
        _mm_store_ps(temp+4,  _mm_mul_ps(this->simd, m.m[1].simd));
        _mm_store_ps(temp+8,  _mm_mul_ps(this->simd, m.m[2].simd));
        _mm_store_ps(temp+12, _mm_mul_ps(this->simd, m.m[3].simd));

        const __m256i indices0 = _mm256_set_epi32(13, 9,  5, 1, 12,  8, 4, 0);
        const __m256i indices1 = _mm256_set_epi32(15, 11, 7, 3, 14, 10, 6, 2);

        _mm256_store_ps(ret.m[0].v, _mm256_i32gather_ps(temp, indices0, sizeof(float)));
        _mm256_store_ps(ret.m[2].v, _mm256_i32gather_ps(temp, indices1, sizeof(float)));
        _mm256_zeroupper();

        __m128 sum0 = _mm_add_ps(ret[1].simd, ret[0].simd);
        __m128 sum1 = _mm_add_ps(ret[3].simd, ret[2].simd);
        return vec4_t<float>{_mm_add_ps(sum1, sum0)};
    #endif
}



} //end math namespace
} //end ls namespace

#endif /* LS_MATH_MAT4F_IMPL_H */
