
#include "lightsky/math/fixed.h"

namespace ls
{
namespace math
{

/*-------------------------------------
    Fixed-Point Template Specializations
-------------------------------------*/
LS_DEFINE_CLASS_TYPE(fixed_t, int32_t, 8); // 23.8 (-1 for the sign)
LS_DEFINE_CLASS_TYPE(fixed_t, int32_t, 12); // 19.12
LS_DEFINE_CLASS_TYPE(fixed_t, int32_t, 16); // 15.16

LS_DEFINE_CLASS_TYPE(fixed_t, int64_t, 16); // 47.16
LS_DEFINE_CLASS_TYPE(fixed_t, int64_t, 20); // 43.20
LS_DEFINE_CLASS_TYPE(fixed_t, int64_t, 24); // 39.24

LS_DEFINE_CLASS_TYPE(fixed_t, uint32_t, 8); // 24.8
LS_DEFINE_CLASS_TYPE(fixed_t, uint32_t, 12); // 20.12
LS_DEFINE_CLASS_TYPE(fixed_t, uint32_t, 16); // 16.16

LS_DEFINE_CLASS_TYPE(fixed_t, uint64_t, 16); // 48.16
LS_DEFINE_CLASS_TYPE(fixed_t, uint64_t, 20); // 44.20
LS_DEFINE_CLASS_TYPE(fixed_t, uint64_t, 24); // 40.24

} /* End math namespace */
} /* End ls namespace */
