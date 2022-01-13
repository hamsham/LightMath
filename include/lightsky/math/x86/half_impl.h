
#ifndef LS_MATH_HALFF_IMPL_H
#define LS_MATH_HALFF_IMPL_H

#include "lightsky/setup/Compiler.h"

// Clang seems to import the _cvtss_sh() function as a C-extension, rather
// than ignoring system header code.
#if defined(LS_COMPILER_CLANG)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wc99-extensions"
#endif

namespace ls
{
namespace math
{



/*-------------------------------------
 * Construct from a float
-------------------------------------*/
inline LS_INLINE half::half(const float f) noexcept :
    #if defined(LS_COMPILER_MSC)
        bits{(uint16_t)_mm_cvtsi128_si32(_mm_cvtps_ph(_mm_set_ss(f), (_MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) & 0x07U))}
    #else
        bits{_cvtss_sh(f, _MM_FROUND_TO_ZERO|_MM_FROUND_NO_EXC)}
    #endif
{}



/*-------------------------------------
 * Convert from a float
-------------------------------------*/
inline LS_INLINE half& half::operator=(const float f) noexcept
{
    #if defined(LS_COMPILER_MSC)
        bits = (uint16_t)_mm_cvtsi128_si32(_mm_cvtps_ph(_mm_set_ss(f), (_MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) & 0x07U));
    #else
        bits = _cvtss_sh(f, _MM_FROUND_TO_ZERO|_MM_FROUND_NO_EXC);
    #endif

    return *this;
}



/*-------------------------------------
 * Cast to a float
-------------------------------------*/
inline LS_INLINE half::operator float() const noexcept
{
    #if defined(LS_COMPILER_MSC)
        return _mm_cvtss_f32(_mm_cvtph_ps(_mm_cvtsi32_si128((int)bits)));
    #else
        return _cvtsh_ss(bits);
    #endif
}



} // end math namespace
} // end ls namespace

#if defined(LS_COMPILER_CLANG)
    #pragma clang diagnostic pop
#endif

#endif /* LS_MATH_HALFF_IMPL_H */
