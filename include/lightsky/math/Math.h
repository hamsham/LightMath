/*
 * File:   math/math.h
 * Author: Miles Lacey
 *
 * This file contains all includes for the math module of LightSky.
 */

#ifndef __LS_MATH_H__
#define __LS_MATH_H__

/*
 * NOTES:
 * All angle measurements used by this library are in radians unless specified
 * otherwise.
 * I also use constructors rather than assignments when creating objects and
 * variables, so this might make readability slightly difficult at first.
 */

#include "ls/math/Setup.h"
#include "ls/math/Types.h"

#include "ls/math/fixed.h"
#include "ls/math/mat2.h"
#include "ls/math/mat3.h"
#include "ls/math/mat4.h"
#include "ls/math/quat.h"
#include "ls/math/vec2.h"
#include "ls/math/vec3.h"
#include "ls/math/vec4.h"

#include "ls/math/scalar_utils.h"
#include "ls/math/quat_utils.h"
#include "ls/math/vec_utils.h"
#include "ls/math/mat_utils.h"

#include "ls/math/PerlinNoise.h"

#endif /* __LS_MATH_H__ */
