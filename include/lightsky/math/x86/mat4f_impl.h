
namespace ls {
namespace math {



/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
template <> inline
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
inline vec4_t<float> vec4_t<float>::operator*(const mat4_t<float>& m) const
{
    __m128 row0(_mm_mul_ps(this->simd, m.m[0].simd));
    __m128 row1(_mm_mul_ps(this->simd, m.m[1].simd));
    __m128 row2(_mm_mul_ps(this->simd, m.m[2].simd));
    __m128 row3(_mm_mul_ps(this->simd, m.m[3].simd));

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
