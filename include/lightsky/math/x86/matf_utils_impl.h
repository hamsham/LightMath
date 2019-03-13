
#include <xmmintrin.h>

namespace ls
{
namespace math
{



/*-----------------------------------------------------------------------------
    2x2 Matrices
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
    3x3 Matrices
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4x4 Determinant
-------------------------------------*/
inline LS_INLINE float determinant(const mat4_t<float>& m4x4) {
    const float* const m = &m4x4.m[0];
    __m128 a, b, c, d, e, f;

    {
        __m128 a0 = _mm_set_ps(m[1],  m[3],  m[2], m[3]);
        __m128 a1 = _mm_set_ps(m[7],  m[5],  m[7], m[6]);
        __m128 a2 = _mm_set_ps(m[10], m[10], m[9], m[9]);
        __m128 a3 = _mm_set1_ps(m[12]);
        a = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(a0, a1), a2), a3);
    }
    {
        __m128 b0 = _mm_set_ps(m[2],  m[3],  m[1],  m[2]);
        __m128 b1 = _mm_set_ps(m[7],  m[6],  m[6],  m[5]);
        __m128 b2 = _mm_set_ps(m[8],  m[8],  m[11], m[11]);
        __m128 b3 = _mm_set_ps(m[13], m[13], m[12], m[12]);
        b = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(b0, b1), b2), b3);
    }
    {
        __m128 c0 = _mm_set_ps(m[0],  m[2],  m[0],  m[3]);
        __m128 c1 = _mm_set_ps(m[6],  m[4],  m[7],  m[4]);
        __m128 c2 = _mm_set_ps(m[11], m[11], m[10], m[10]);
        __m128 c3 = _mm_set1_ps(m[13]);
        c = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(c0, c1), c2), c3);
    }
    {
        __m128 d0 = _mm_set_ps(m[0], m[3], m[1], m[3]);
        __m128 d1 = _mm_set_ps(m[7], m[4], m[7], m[5]);
        __m128 d2 = _mm_set_ps(m[9], m[9], m[8], m[8]);
        __m128 d3 = _mm_set1_ps(m[14]);
        d = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(d0, d1), d2), d3);
    }
    {
        __m128 e0 = _mm_set_ps(m[1],  m[2],  m[0],  m[1]);
        __m128 e1 = _mm_set_ps(m[6],  m[5],  m[5],  m[4]);
        __m128 e2 = _mm_set_ps(m[8],  m[8],  m[11], m[11]);
        __m128 e3 = _mm_set_ps(m[15], m[15], m[14], m[14]);
        e = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(e0, e1), e2), e3);
    }
    {
        __m128 f0 = _mm_set_ps(m[0], m[1], m[0], m[2]);
        __m128 f1 = _mm_set_ps(m[5], m[4], m[6], m[4]);
        __m128 f2 = _mm_set_ps(m[10], m[10], m[9], m[9]);
        __m128 f3 = _mm_set1_ps(m[15]);
        f = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(f0, f1), f2), f3);
    }

    a = _mm_xor_ps(_mm_set_ps(0.f, -0.f, -0.f, 0.f), a);
    b = _mm_xor_ps(_mm_set_ps(0.f, -0.f, -0.f, 0.f), b);
    c = _mm_xor_ps(_mm_set_ps(0.f, -0.f, -0.f, 0.f), c);
    d = _mm_xor_ps(_mm_set_ps(0.f, -0.f, -0.f, 0.f), d);
    e = _mm_xor_ps(_mm_set_ps(0.f, -0.f, -0.f, 0.f), e);
    f = _mm_xor_ps(_mm_set_ps(0.f, -0.f, -0.f, 0.f), f);

    const __m128 temp = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(a, b), c), d), e), f);

    // horizontal add: swap the words of each vector, add, then swap each
    // half of the vectors and perform a final add.
    const __m128 swap = _mm_add_ps(temp, _mm_shuffle_ps(temp, temp,  0xB1));
    const __m128 sum  = _mm_add_ps(swap, _mm_shuffle_ps(swap, swap, 0x0F));

    return _mm_cvtss_f32(sum);
}



/*-------------------------------------
    4x4 Transpose
-------------------------------------*/
inline LS_INLINE mat4_t<float> transpose(const mat4_t<float>& m)
{
    const __m128 t0 = _mm_unpacklo_ps(m.m[0].simd, m.m[1].simd);
    const __m128 t1 = _mm_unpacklo_ps(m.m[2].simd, m.m[3].simd);
    const __m128 t2 = _mm_unpackhi_ps(m.m[0].simd, m.m[1].simd);
    const __m128 t3 = _mm_unpackhi_ps(m.m[2].simd, m.m[3].simd);

    return mat4_t<float>{
        vec4_t<float>{_mm_movelh_ps(t0, t1)},
        vec4_t<float>{_mm_movehl_ps(t1, t0)},
        vec4_t<float>{_mm_movelh_ps(t2, t3)},
        vec4_t<float>{_mm_movehl_ps(t3, t2)}
    };
}



} // end math namespace
} // end ls namespace
