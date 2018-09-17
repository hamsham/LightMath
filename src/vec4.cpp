
#include "lightsky/math/Math.h"
#include "lightsky/math/mat4.h"
#include "lightsky/math/vec4.h"

namespace ls {
namespace math {

/*
 * 4D Vector Specializations
 */
#if !defined(LS_ARCH_X86) && !defined(LS_ARCH_ARM)
    LS_DEFINE_UNION_TYPE(vec4_t, float);

#endif

LS_DEFINE_UNION_TYPE(vec4_t, double);
LS_DEFINE_UNION_TYPE(vec4_t, int);
LS_DEFINE_UNION_TYPE(vec4_t, unsigned);
LS_DEFINE_UNION_TYPE(vec4_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
