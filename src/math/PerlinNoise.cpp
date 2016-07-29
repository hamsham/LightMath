
#include "ls/math/Math.h"
#include "ls/math/PerlinNoise.h"

namespace ls {
namespace math {

/*-------------------------------------
    Perlin Noise Specializations
-------------------------------------*/
LS_DEFINE_CLASS_TYPE(PerlinNoise, float);
LS_DEFINE_CLASS_TYPE(PerlinNoise, double);
LS_DEFINE_CLASS_TYPE(PerlinNoise, int);
LS_DEFINE_CLASS_TYPE(PerlinNoise, unsigned);
LS_DEFINE_CLASS_TYPE(PerlinNoise, medp_t);

} /* End math namespace */
} /* End ls namespace */
