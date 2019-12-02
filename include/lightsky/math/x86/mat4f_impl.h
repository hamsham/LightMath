
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

        //const float* const nm = reinterpret_cast<const float*>(&n);
        const __m256 temp0 = _mm256_insertf128_ps(_mm256_castps128_ps256(n[0].simd), n[1].simd, 1);
        const __m256 temp1 = _mm256_insertf128_ps(_mm256_castps128_ps256(n[2].simd), n[3].simd, 1);
        __m256 r01;
        __m256 r23;

        alignas(sizeof(__m256)) mat4_t<float> ret;

        r01 = _mm256_mul_ps(  col0, _mm256_permute_ps(temp0, 0x00));
        r01 = _mm256_fmadd_ps(col1, _mm256_permute_ps(temp0, 0x55), r01);
        r01 = _mm256_fmadd_ps(col2, _mm256_permute_ps(temp0, 0xAA), r01);
        r01 = _mm256_fmadd_ps(col3, _mm256_permute_ps(temp0, 0xFF), r01);
        _mm256_store_ps(reinterpret_cast<float*>(&ret), r01);

        r23 = _mm256_mul_ps(  col0, _mm256_permute_ps(temp1, 0x00));
        r23 = _mm256_fmadd_ps(col1, _mm256_permute_ps(temp1, 0x55), r23);
        r23 = _mm256_fmadd_ps(col2, _mm256_permute_ps(temp1, 0xAA), r23);
        r23 = _mm256_fmadd_ps(col3, _mm256_permute_ps(temp1, 0xFF), r23);
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
    __m128 v0 = _mm_mul_ps(  this->m[0].simd, _mm_permute_ps(v.simd, 0x00));
    __m128 v1 = _mm_fmadd_ps(this->m[1].simd, _mm_permute_ps(v.simd, 0x55), v0);
    __m128 v2 = _mm_fmadd_ps(this->m[2].simd, _mm_permute_ps(v.simd, 0xAA), v1);
    __m128 v3 = _mm_fmadd_ps(this->m[3].simd, _mm_permute_ps(v.simd, 0xFF), v2);

    return math::vec4_t<float>{v3};
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

        __m128 sum =          _mm_shuffle_ps(t0, t1, 0x44);
        sum = _mm_add_ps(sum, _mm_shuffle_ps(t0, t1, 0xEE));
        sum = _mm_add_ps(sum, _mm_shuffle_ps(t2, t3, 0x44));
        sum = _mm_add_ps(sum, _mm_shuffle_ps(t2, t3, 0xEE));

        return vec4_t<float>{sum};
    #else
        const __m256 s = _mm256_broadcast_ps(reinterpret_cast<const __m128*>(v));

        const __m256 m0 = _mm256_set_m128(m[1].simd, m[0].simd);
        const __m256 m1 = _mm256_set_m128(m[3].simd, m[2].simd);
        const __m256 row02 = _mm256_mul_ps(s, m0);
        const __m256 row13 = _mm256_mul_ps(s, m1);

        const __m256 ml = _mm256_unpacklo_ps(row02, row13);
        const __m256 mh = _mm256_unpackhi_ps(row02, row13);

        const __m256 nl = _mm256_shuffle_ps(ml, mh, 0x44);
        const __m256 nh = _mm256_shuffle_ps(ml, mh, 0xEE);

        const __m256d out01 = _mm256_castps_pd(_mm256_shuffle_ps(nl, nh, 0x44));
        const __m256d out23 = _mm256_castps_pd(_mm256_shuffle_ps(nl, nh, 0xEE));

        const __m256 temp0 = _mm256_castpd_ps(_mm256_permute4x64_pd(out01, 0xD8));
        const __m256 temp1 = _mm256_castpd_ps(_mm256_permute4x64_pd(out23, 0xD8));
        const __m256 temp2 = _mm256_add_ps(temp0, temp1);

        const __m128 t0 = _mm256_extractf128_ps(temp2, 0);
        const __m128 t1 = _mm256_extractf128_ps(temp2, 1);

        return vec4_t<float>{_mm_add_ps(t0, t1)};
    #endif
}



} //end math namespace
} //end ls namespace
