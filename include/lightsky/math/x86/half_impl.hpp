
#include "lightsky/setup/OS.h"

namespace ls
{
namespace math
{



/*-------------------------------------
 * Construct from a float
-------------------------------------*/
inline LS_IMPERATIVE Half::Half(const float f) noexcept :
    #ifdef LS_OS_OSX
        bits{(uint16_t)_mm_cvtsi128_si32(_mm_cvtps_ph(_mm_set1_ps(f), _MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC))}
    #else
        bits{_cvtss_sh(f, _MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC)}
    #endif
{}



/*-------------------------------------
 * Convert from a float
-------------------------------------*/
inline Half& LS_IMPERATIVE Half::operator=(const float f) noexcept
{
    #ifdef LS_OS_OSX
        bits = (uint16_t)_mm_cvtsi128_si32(_mm_cvtps_ph(_mm_set1_ps(f), _MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC));
    #else
        bits = _cvtss_sh(f, _MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC);
    #endif
    return *this;
}



/*-------------------------------------
 * Cast to a float
-------------------------------------*/
inline LS_IMPERATIVE Half::operator float() const noexcept
{
    return _cvtsh_ss(bits);
}



} // end math namespace
} // end ls namespace
