
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
    bits{_cvtss_sh(f, _MM_FROUND_TO_ZERO|_MM_FROUND_NO_EXC)}
{}



/*-------------------------------------
 * Convert from a float
-------------------------------------*/
inline LS_INLINE half& half::operator=(const float f) noexcept
{
    bits = _cvtss_sh(f, _MM_FROUND_TO_ZERO|_MM_FROUND_NO_EXC);
    return *this;
}



/*-------------------------------------
 * Cast to a float
-------------------------------------*/
inline LS_INLINE half::operator float() const noexcept
{
    return _cvtsh_ss(bits);
}



} // end math namespace
} // end ls namespace

#if defined(LS_COMPILER_CLANG)
    #pragma clang diagnostic pop
#endif
