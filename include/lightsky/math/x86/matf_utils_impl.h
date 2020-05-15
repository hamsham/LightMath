
#include <xmmintrin.h>

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    2x2 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    2x2 Inverse
-------------------------------------*/
inline LS_INLINE mat2_t<float> inverse(const mat2_t<float>& m2x2) noexcept
{
    const float* const m = &m2x2.m[0];

    const float  det    = determinant<float>(m2x2);
    const __m128 detInv = _mm_set1_ps(1.f / det);

    const __m128 input    = _mm_load_ps(m);
    const __m128 swapped  = _mm_shuffle_ps(input, input, 0xD8);
    const __m128 signMask = _mm_set_ps(0.f, -0.f, -0.f, 0.f);
    const __m128 negated  = _mm_xor_ps(signMask, swapped);
    const __m128 inverted = _mm_mul_ps(negated, detInv);

    mat2_t<float> out;
    float* const pOut = &out.m[0];

    _mm_storeu_ps(pOut, inverted);

    return out;
}


/*-----------------------------------------------------------------------------
    3x3 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    3x3 Determinant
-------------------------------------*/
inline LS_INLINE float determinant(const mat3_t<float>& m3x3) noexcept
{
    const float* const m = reinterpret_cast<const float*>(&m3x3);

    #if 1 // Load-city, but works if m3x3 is currently in registers
        const __m128 col0 = _mm_set_ps(0.f, m[4], m[5], m[3]);
        const __m128 col1 = _mm_set_ps(0.f, m[8], m[6], m[7]);
        const __m128 col2 = _mm_set_ps(0.f, m[5], m[3], m[4]);
        const __m128 col3 = _mm_set_ps(0.f, m[7], m[8], m[6]);
        const __m128 col4 = _mm_set_ps(0.f, m[0], m[1], m[2]);

    #elif 0 // 5 gathered loads, not great
        const __m128i mask = _mm_set_epi32(0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
        const __m128 col0 = _mm_mask_i32gather_ps(_mm_setzero_ps(), m, _mm_set_epi32(0, 4, 5, 3), mask, 4);
        const __m128 col1 = _mm_mask_i32gather_ps(_mm_setzero_ps(), m, _mm_set_epi32(0, 8, 6, 7), mask, 4);
        const __m128 col2 = _mm_mask_i32gather_ps(_mm_setzero_ps(), m, _mm_set_epi32(0, 5, 3, 4), mask, 4);
        const __m128 col3 = _mm_mask_i32gather_ps(_mm_setzero_ps(), m, _mm_set_epi32(0, 7, 8, 6), mask, 4);
        const __m128 col4 = _mm_mask_i32gather_ps(_mm_setzero_ps(), m, _mm_set_epi32(0, 0, 1, 2), mask, 4);

    #else // 3 loads, 4 shuffles
        constexpr int shuffleMask120 = 0xC9; // indices: <base> + (3, 0, 2, 1): 11001001
        constexpr int shuffleMask201 = 0xD2; // indices: <base> + (3, 1, 0, 2): 11010010
        const __m128i loadMask = _mm_set_epi32(0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);

        const __m128 col4 = _mm_maskload_ps(m,   loadMask);
        const __m128 row1 = _mm_maskload_ps(m+3, loadMask);
        const __m128 row2 = _mm_maskload_ps(m+6, loadMask);

        const __m128 col0 = _mm_permute_ps(row1, shuffleMask120);
        const __m128 col2 = _mm_permute_ps(row1, shuffleMask201);
        const __m128 col1 = _mm_permute_ps(row2, shuffleMask201);
        const __m128 col3 = _mm_permute_ps(row2, shuffleMask120);
    #endif

    const __m128 sub0 = _mm_fmsub_ps(col0, col1, _mm_mul_ps(col2, col3));
    const __m128 mul2 = _mm_mul_ps(sub0, col4);

    // horizontal add: swap the words of each vector, add, then swap each
    // half of the vectors and perform a final add.
    const __m128 swap = _mm_add_ps(mul2, _mm_permute_ps(mul2, 0xB1));
    const __m128 sum  = _mm_add_ps(swap, _mm_permute_ps(swap, 0x0F));

    return _mm_cvtss_f32(sum);
}



/*-------------------------------------
    3x3 Inverse
-------------------------------------*/
inline LS_INLINE mat3_t<float> inverse(const mat3_t<float>& m3x3) noexcept
{
    const float* const m = &m3x3.m[0];

    const __m128 detInv = _mm_set1_ps(1.f / determinant(m3x3));

    const __m128 col00  = _mm_set_ps(0.f, m[1], m[2], m[4]);
    const __m128 col10  = _mm_set_ps(0.f, m[2], m[0], m[5]);
    const __m128 col20  = _mm_set_ps(0.f, m[0], m[1], m[3]);
    const __m128 col01  = _mm_set_ps(0.f, m[5], m[7], m[8]);
    const __m128 col11  = _mm_set_ps(0.f, m[3], m[8], m[6]);
    const __m128 col21  = _mm_set_ps(0.f, m[4], m[6], m[7]);
    const __m128 col02  = _mm_set_ps(0.f, m[2], m[1], m[5]);
    const __m128 col12  = _mm_set_ps(0.f, m[0], m[2], m[3]);
    const __m128 col22  = _mm_set_ps(0.f, m[1], m[0], m[4]);
    const __m128 col03  = _mm_set_ps(0.f, m[4], m[8], m[7]);
    const __m128 col13  = _mm_set_ps(0.f, m[5], m[6], m[8]);
    const __m128 col23  = _mm_set_ps(0.f, m[3], m[7], m[6]);

    const __m128 mul00  = _mm_mul_ps(col00, col01);
    const __m128 mul01  = _mm_mul_ps(col10, col11);
    const __m128 mul02  = _mm_mul_ps(col20, col21);

    const __m128 mul10  = _mm_mul_ps(col02, col03);
    const __m128 mul11  = _mm_mul_ps(col12, col13);
    const __m128 mul12  = _mm_mul_ps(col22, col23);

    const __m128 sub0   = _mm_mul_ps(_mm_sub_ps(mul00, mul10), detInv);
    const __m128 sub1   = _mm_mul_ps(_mm_sub_ps(mul01, mul11), detInv);
    const __m128 sub2   = _mm_mul_ps(_mm_sub_ps(mul02, mul12), detInv);

    mat3_t<float> out;
    float* const pOut = &out.m[0];

    const __m128i storeMask = _mm_set_epi32(0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    _mm_storeu_ps(pOut+0, sub0);
    _mm_storeu_ps(pOut+3, sub1);
    _mm_maskstore_ps(pOut+6, storeMask, sub2);

    return out;
}



/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4x4 Outer Product
-------------------------------------*/
inline LS_INLINE mat4_t<float> outer(const vec4_t<float>& v1, const vec4_t<float>& v2) noexcept
{
    #if 0
        const __m256 s0 = _mm256_set_m128(v1.simd, v1.simd);
        const __m256 s1 = _mm256_set_m128(v2.simd, v2.simd);

        const __m256 s001 = _mm256_permutevar_ps(s0, _mm256_set_epi64x(0x0000000100000001, 0x0000000100000001, 0x0000000000000000, 0x0000000000000000));
        const __m256 s023 = _mm256_permutevar_ps(s0, _mm256_set_epi64x(0x0000000300000003, 0x0000000300000003, 0x0000000200000002, 0x0000000200000002));

        union
        {
            __m256 v[2];
            mat4_t<float> m;
        } ret;
        ret.v[0] = _mm256_mul_ps(s1, s001);
        ret.v[1] = _mm256_mul_ps(s1, s023);

        return ret.m;
    #else
        return mat4_t<float>{
            _mm_mul_ps(_mm_permute_ps(v1.simd, 0x00), v2.simd),
            _mm_mul_ps(_mm_permute_ps(v1.simd, 0x55), v2.simd),
            _mm_mul_ps(_mm_permute_ps(v1.simd, 0xAA), v2.simd),
            _mm_mul_ps(_mm_permute_ps(v1.simd, 0xFF), v2.simd)
        };
    #endif
}

/*-------------------------------------
    4x4 Determinant
-------------------------------------*/
inline LS_INLINE float determinant(const mat4_t<float>& m4x4) noexcept
{
    const float* const m = &m4x4.m[0];

    const __m128 m0 = _mm_loadu_ps(m+0);
    const __m128 m1 = _mm_loadu_ps(m+4);
    const __m128 m2 = _mm_loadu_ps(m+8);
    const __m128 m3 = _mm_loadu_ps(m+12);

    const __m128 a0 = _mm_permute_ps(m0, _MM_SHUFFLE(1, 3, 2, 3));
    const __m128 a1 = _mm_permute_ps(m1, _MM_SHUFFLE(3, 1, 3, 2));
    const __m128 a2 = _mm_permute_ps(m2, _MM_SHUFFLE(2, 2, 1, 1));
    const __m128 a3 = _mm_permute_ps(m3, _MM_SHUFFLE(0, 0, 0, 0));
    const __m128 b0 = _mm_permute_ps(m0, _MM_SHUFFLE(2, 3, 1, 2));
    const __m128 b1 = _mm_permute_ps(m1, _MM_SHUFFLE(3, 2, 2, 1));
    const __m128 b2 = _mm_permute_ps(m2, _MM_SHUFFLE(0, 0, 3, 3));
    const __m128 b3 = _mm_permute_ps(m3, _MM_SHUFFLE(1, 1, 0, 0));
    const __m128 c0 = _mm_permute_ps(m0, _MM_SHUFFLE(0, 2, 0, 3));
    const __m128 c1 = _mm_permute_ps(m1, _MM_SHUFFLE(2, 0, 3, 0));
    const __m128 c2 = _mm_permute_ps(m2, _MM_SHUFFLE(3, 3, 2, 2));
    const __m128 c3 = _mm_permute_ps(m3, _MM_SHUFFLE(1, 1, 1, 1));
    const __m128 d0 = _mm_permute_ps(m0, _MM_SHUFFLE(0, 3, 1, 3));
    const __m128 d1 = _mm_permute_ps(m1, _MM_SHUFFLE(3, 0, 3, 1));
    const __m128 d2 = _mm_permute_ps(m2, _MM_SHUFFLE(1, 1, 0, 0));
    const __m128 d3 = _mm_permute_ps(m3, _MM_SHUFFLE(2, 2, 2, 2));
    const __m128 e0 = _mm_permute_ps(m0, _MM_SHUFFLE(1, 2, 0, 1));
    const __m128 e1 = _mm_permute_ps(m1, _MM_SHUFFLE(2, 1, 1, 0));
    const __m128 e2 = _mm_permute_ps(m2, _MM_SHUFFLE(0, 0, 3, 3));
    const __m128 e3 = _mm_permute_ps(m3, _MM_SHUFFLE(3, 3, 2, 2));
    const __m128 f0 = _mm_permute_ps(m0, _MM_SHUFFLE(0, 1, 0, 2));
    const __m128 f1 = _mm_permute_ps(m1, _MM_SHUFFLE(1, 0, 2, 0));
    const __m128 f2 = _mm_permute_ps(m2, _MM_SHUFFLE(2, 2, 1, 1));
    const __m128 f3 = _mm_permute_ps(m3, _MM_SHUFFLE(3, 3, 3, 3));

    __m128 a = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(a0, a1), a2), a3);
    __m128 b = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(b0, b1), b2), b3);
    __m128 c = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(c0, c1), c2), c3);
    __m128 d = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(d0, d1), d2), d3);
    __m128 e = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(e0, e1), e2), e3);
    __m128 f = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(f0, f1), f2), f3);

    const __m128 signMask = _mm_set_ps(0.f, -0.f, -0.f, 0.f);
    a = _mm_xor_ps(signMask, a);
    b = _mm_xor_ps(signMask, b);
    c = _mm_xor_ps(signMask, c);
    d = _mm_xor_ps(signMask, d);
    e = _mm_xor_ps(signMask, e);
    f = _mm_xor_ps(signMask, f);

    const __m128 temp = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(a, b), c), d), e), f);

    // horizontal add: swap the words of each vector, add, then swap each
    // half of the vectors and perform a final add.
    const __m128 swap = _mm_add_ps(temp, _mm_permute_ps(temp,  0xB1));
    const __m128 sum  = _mm_add_ps(swap, _mm_permute_ps(swap, 0x0F));
    return _mm_cvtss_f32(sum);
}



/*-------------------------------------
    4x4 Component-wise multiplication
-------------------------------------*/
inline LS_INLINE mat4_t<float> mat_comp_mul(const mat4_t<float>& m1, const mat4_t<float>& m2) noexcept
{
    mat4_t<float> result;

    result.m[0].simd = _mm_mul_ps(m1.m[0].simd, m2.m[0].simd);
    result.m[1].simd = _mm_mul_ps(m1.m[1].simd, m2.m[1].simd);
    result.m[2].simd = _mm_mul_ps(m1.m[2].simd, m2.m[2].simd);
    result.m[3].simd = _mm_mul_ps(m1.m[3].simd, m2.m[3].simd);

    return result;
}



/*-------------------------------------
    4x4 Transpose
-------------------------------------*/
inline LS_INLINE mat4_t<float> transpose(const mat4_t<float>& m)
{

    #if 1
        const __m128 m0 = _mm_loadu_ps(&m[0]);
        const __m128 m1 = _mm_loadu_ps(&m[1]);
        const __m128 m2 = _mm_loadu_ps(&m[2]);
        const __m128 m3 = _mm_loadu_ps(&m[3]);

        const __m128 t0 = _mm_unpacklo_ps(m0, m1);
        const __m128 t1 = _mm_unpacklo_ps(m2, m3);
        const __m128 t2 = _mm_unpackhi_ps(m0, m1);
        const __m128 t3 = _mm_unpackhi_ps(m2, m3);

        return mat4_t<float>{
            vec4_t<float>{_mm_shuffle_ps(t0, t1, 0x44)},
            vec4_t<float>{_mm_shuffle_ps(t0, t1, 0xEE)},
            vec4_t<float>{_mm_shuffle_ps(t2, t3, 0x44)},
            vec4_t<float>{_mm_shuffle_ps(t2, t3, 0xEE)}
        };
    #else
        alignas(sizeof(__m256)) mat4_t<float> ret;
        const __m256i indices0 = _mm256_set_epi32(13, 9,  5, 1, 12,  8, 4, 0);
        const __m256i indices1 = _mm256_set_epi32(15, 11, 7, 3, 14, 10, 6, 2);
        _mm256_store_ps(ret.m[0].v, _mm256_i32gather_ps(m.m[0].v, indices0, sizeof(float)));
        _mm256_store_ps(ret.m[2].v, _mm256_i32gather_ps(m.m[0].v, indices1, sizeof(float)));
        return ret;
    #endif
}



} // end math namespace
} // end ls namespace
