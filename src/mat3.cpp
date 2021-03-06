
#include "lightsky/math/half.h"
#include "lightsky/math/vec4.h"

#include "lightsky/math/mat3.h"
#include "lightsky/math/mat4.h"

namespace ls {
namespace math {

/*
 * 3x3 Matrix Specializations
 */
LS_DEFINE_STRUCT_TYPE(mat3_t, half);
LS_DEFINE_STRUCT_TYPE(mat3_t, float);
LS_DEFINE_STRUCT_TYPE(mat3_t, double);
LS_DEFINE_STRUCT_TYPE(mat3_t, int);
LS_DEFINE_STRUCT_TYPE(mat3_t, unsigned);
LS_DEFINE_STRUCT_TYPE(mat3_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
