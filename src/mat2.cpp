
#include "lightsky/math/half.h"
#include "lightsky/math/mat2.h"

namespace ls {
namespace math {

/*
 * 2x2 Matrix Specializations
 */
LS_DEFINE_STRUCT_TYPE(mat2_t, half);
LS_DEFINE_STRUCT_TYPE(mat2_t, float);
LS_DEFINE_STRUCT_TYPE(mat2_t, double);
LS_DEFINE_STRUCT_TYPE(mat2_t, int);
LS_DEFINE_STRUCT_TYPE(mat2_t, unsigned);
LS_DEFINE_STRUCT_TYPE(mat2_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
