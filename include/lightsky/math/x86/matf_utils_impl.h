
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
