
#include "ls/math/Math.h"
#include "ls/math/mat4.h"
#include "ls/math/vec4.h"

namespace ls {
namespace math {

/*
 * 4D Vector Specializations
 */
LS_DEFINE_STRUCT_TYPE(vec4_t, float);
LS_DEFINE_STRUCT_TYPE(vec4_t, double);
LS_DEFINE_STRUCT_TYPE(vec4_t, int);
LS_DEFINE_STRUCT_TYPE(vec4_t, unsigned);
LS_DEFINE_STRUCT_TYPE(vec4_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
