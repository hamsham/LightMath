
#ifndef LS_MATH_MAT_UTILS_H
#define LS_MATH_MAT_UTILS_H

#include "lightsky/setup/Arch.h"

#include "lightsky/math/vec_utils.h"
#include "lightsky/math/mat2.h"
#include "lightsky/math/mat3.h"
#include "lightsky/math/mat4.h"

namespace ls {
namespace math {

/*-----------------------------------------------------------------------------
    2x2 Matrices
-----------------------------------------------------------------------------*/
/**
 *  @brief Compute the outer-product of two vectors.
 *
 *  @param v1
 *  A constant reference to a vector.
 *
 *  @param v2
 *  A constant reference to a vector.
 *
 *  @return A matrix containing the outer-product of v1 & v2.
 */
template <typename N> constexpr
mat2_t<N> outer(const vec2_t<N>& v1, const vec2_t<N>& v2) noexcept;

/**
 *  @brief determinant
 *  Retrieve the determinate for a 2x2 matrix.
 *
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *
 *  @return A scalar of type N, which contains the determinate of a 2x2 matrix.
 */
template <typename N> constexpr
N determinant(const mat2_t<N>& m) noexcept;

/**
 *  @brief transpose
 *  Flip the values of a matrix around its main diagonal.
 *
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *
 *  @return the transposition of a matrix.
 */
template <typename N> constexpr
mat2_t<N> transpose(const mat2_t<N>& m) noexcept;

/**
 *  @brief inverse
 *  Invert a matrix m so that m * m^i = I
 *
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *
 *  @return
 *  The inverse of matrix m.
 */
template <typename N> constexpr
mat2_t<N> inverse(const mat2_t<N>& m) noexcept;

/**
 *  @brief Component-wise multiplication of two matrices
 *
 *  mat_comp_mul() performs a component-wise multiplication of two matrices,
 *  yielding a result matrix where each component, result[i][j] is computed as
 *  the scalar product of x[i][j] and y[i][j].
 *
 *  @param m1
 *  A constant reference to a matrix.
 *
 *  @param m2
 *  A constant reference to a matrix.
 *
 *  @return a matrix containing the component-wise multiplication of m1 and m2.
 */
template <typename N> constexpr
mat2_t<N> mat_comp_mul(const mat2_t<N>& m1, const mat2_t<N>& m2) noexcept;

/**
 *  @brief Row-by-row multiplication of a matrix and vector
 *
 *  mat_row_mul() will multiply each row of a matrix by a each component of a
 *  vector.
 *
 *  @param m
 *  A constant reference to a matrix.
 *
 *  @param v
 *  A constant reference to a vector.
 *
 *  @return a matrix containing the row-based multiplication of each component
 *  in the input vector.
 */
template <typename N> constexpr
mat2_t<N> mat_row_mul(const mat2_t<N>& m, const vec2_t<N>& v) noexcept;

/**
 *  @brief rotate
 *  Rotate a 2x2 matrix by a number of radians.
 *
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *
 *  @param radians
 *  The number of radians to rotate a matrix by.
 *
 *  @return
 *  A the rotation of m by a number of radians.
 */
template <typename N> inline
mat2_t<N> rotate(const mat2_t<N>& m, N radians) noexcept;

/**
 *  @brief scale
 *  Scale a matrix by modifying the components of its main diagonal. This
 *  method uses additive scaling rather than multiplicative scaling.
 *
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *
 *  @param amount
 *  the amount of scaling along each axis of matrix m.
 */
template <typename N> constexpr
mat2_t<N> scale(const mat2_t<N>& m, const vec2_t<N>& amount) noexcept;

/*-----------------------------------------------------------------------------
    3x3 Matrices
-----------------------------------------------------------------------------*/
/**
 *  @brief Compute the outer-product of two vectors.
 *
 *  @param v1
 *  A constant reference to a vector.
 *
 *  @param v2
 *  A constant reference to a vector.
 *
 *  @return A matrix containing the outer-product of v1 & v2.
 */
template <typename N> constexpr
mat3_t<N> outer(const vec3_t<N>& v1, const vec3_t<N>& v2) noexcept;

/**
 *  @brief determinant
 *  Retrieve the determinate for a 3x3 matrix.
 *
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *
 *  @return A scalar of type N, which contains the determinate of a 3x3 matrix.
 */
template <typename N> constexpr
N determinant(const mat3_t<N>& m) noexcept;

/**
 *  @brief transpose
 *  Flip the values of a matrix around its main diagonal.
 *
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *
 *  @return the transposition of a matrix.
 */
template <typename N> constexpr
mat3_t<N> transpose(const mat3_t<N>& m) noexcept;

/**
 *  @brief inverse
 */
template <typename N> constexpr
mat3_t<N> inverse(const mat3_t<N>& m) noexcept;

/**
 *  @brief Component-wise multiplication of two matrices
 *
 *  mat_comp_mul() performs a component-wise multiplication of two matrices,
 *  yielding a result matrix where each component, result[i][j] is computed as
 *  the scalar product of x[i][j] and y[i][j].
 *
 *  @param m1
 *  A constant reference to a matrix.
 *
 *  @param m2
 *  A constant reference to a matrix.
 *
 *  @return a matrix containing the component-wise multiplication of m1 and m2.
 */
template <typename N> constexpr
mat3_t<N> mat_comp_mul(const mat3_t<N>& m1, const mat3_t<N>& m2) noexcept;

/**
 *  @brief Row-by-row multiplication of a matrix and vector
 *
 *  mat_row_mul() will multiply each row of a matrix by a each component of a
 *  vector.
 *
 *  @param m
 *  A constant reference to a matrix.
 *
 *  @param v
 *  A constant reference to a vector.
 *
 *  @return a matrix containing the row-based multiplication of each component
 *  in the input vector.
 */
template <typename N> constexpr
mat3_t<N> mat_row_mul(const mat3_t<N>& m, const vec3_t<N>& v) noexcept;

/**
 *  @brief rotate
 *  Rotate a 3x3 matrix by a number of radians.
 *
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *
 *  @param axis
 *  The axis in 3D space around which the matrix will be rotated.
 *
 *  @param radians
 *  The number of radians to rotate a matrix by.
 *
 *  @return
 *  A the rotation of m by a number of radians.
 */
template <typename N> inline
mat3_t<N> rotate(const mat3_t<N>& m, const vec3_t<N>& axis, N radians) noexcept;

/**
 *  @brief scale
 *  Scale a matrix by modifying the components of its main diagonal. This
 *  method uses additive scaling rather than multiplicative scaling.
 *
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *
 *  @param amount
 *  the amount of scaling along each axis of matrix m.
 */
template <typename N> constexpr
mat3_t<N> scale(const mat3_t<N>& m, const vec3_t<N>& amount) noexcept;

/**
 *  @brief translate
 *  Translate a 3x3 matrix along a 2D plane.
 *
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *
 *  @param amount
 *  A constant reference to a constant 2D vector, indicating how much to move
 *  the matrix by.
 *
 *  @return a 3x3 matrix that has been translated.
 */
template <typename N> constexpr
mat3_t<N> translate(const mat3_t<N>& m, const vec2_t<N>& amount) noexcept;

/**
 *  @brief Look at a position in 3D space, but only return a pure rotation
 *  matrix with no positioning.
 *
 *  @param pos
 *  The position, in 3D space, at which the projection matrix will be placed.
 *
 *  @param target
 *  The position of the target point, in 3D space, that the projection matrix
 *  will face.
 *
 *  @param up
 *  The direction of the top of the projection matrix.
 *
 *  @return A rotation matrix that represents a camera's orientation towards a
 *  target in 3D space.
 */
template <typename N> inline
mat3_t<N> pure_look_at(const vec3_t<N>& pos, const vec3_t<N>& target, const vec3_t<N>& up) noexcept;

/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/**
 *  @brief Compute the outer-product of two vectors.
 *
 *  @param v1
 *  A constant reference to a vector.
 *
 *  @param v2
 *  A constant reference to a vector.
 *
 *  @return A matrix containing the outer-product of v1 & v2.
 */
template <typename N> constexpr
mat4_t<N> outer(const vec4_t<N>& v1, const vec4_t<N>& v2) noexcept;

/**
 *  @brief determinant
 *  Retrieve the determinate for a 4x4 matrix.
 *
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *
 *  @return A scalar of type N, which contains the determinate of a 4x4 matrix.
 */
template <typename N> constexpr
N determinant(const mat4_t<N>& m) noexcept;

/**
 *  @brief transpose
 *  Flip the values of a matrix around its main diagonal.
 *
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *
 *  @return the transposition of a matrix.
 */
template <typename N> inline
mat4_t<N> transpose(const mat4_t<N>& m) noexcept;

/**
 *  @brief inverse
 */
template <typename N> inline
mat4_t<N> inverse(const mat4_t<N>& m) noexcept;

/**
 *  @brief Component-wise multiplication of two matrices
 *
 *  mat_comp_mul() performs a component-wise multiplication of two matrices,
 *  yielding a result matrix where each component, result[i][j] is computed as
 *  the scalar product of x[i][j] and y[i][j].
 *
 *  @param m1
 *  A constant reference to a matrix.
 *
 *  @param m2
 *  A constant reference to a matrix.
 *
 *  @return a matrix containing the component-wise multiplication of m1 and m2.
 */
template <typename N> constexpr
mat4_t<N> mat_comp_mul(const mat4_t<N>& m1, const mat4_t<N>& m2) noexcept;

/**
 *  @brief Row-by-row multiplication of a matrix and vector
 *
 *  mat_row_mul() will multiply each row of a matrix by a each component of a
 *  vector.
 *
 *  @param m
 *  A constant reference to a matrix.
 *
 *  @param v
 *  A constant reference to a vector.
 *
 *  @return a matrix containing the row-based multiplication of each component
 *  in the input vector.
 */
template <typename N> constexpr
mat4_t<N> mat_row_mul(const mat4_t<N>& m, const vec4_t<N>& v) noexcept;

/**
 *  @brief rotate
 *  Rotate a 4x4 matrix by a number of radians.
 *
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *
 *  @param axis
 *  The axis in 3D space around which the matrix will be rotated.
 *
 *  @param radians
 *  The number of radians to rotate a matrix by.
 *
 *  @return
 *  A the rotation of m by a number of radians.
 */
template <typename N> inline
mat4_t<N> rotate(const mat4_t<N>& m, const vec3_t<N>& axis, N radians) noexcept;

/**
 *  @brief scale
 *  Scale a matrix by modifying the components of its main diagonal. This
 *  method uses additive scaling rather than multiplicative scaling.
 *
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *
 *  @param amount
 *  the amount of scaling along each axis of matrix m.
 */
template <typename N> constexpr
mat4_t<N> scale(const mat4_t<N>& m, const vec3_t<N>& amount) noexcept;

/**
 *  @brief translate
 *  Translate a 4x4 matrix along a 3D plane.
 *
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *
 *  @param amount
 *  A constant reference to a constant 3D vector, indicating how much to move
 *  the matrix by.
 *
 *  @return a 4x4 matrix that has been translated.
 */
template <typename N> constexpr
mat4_t<N> translate(const mat4_t<N>& m, const vec3_t<N>& amount) noexcept;

/**
 *  @brief perspective
 *  Create a 2D perspective projection matrix in 3D space.
 *
 *  @param fov
 *  The angle, in radians, representing the field of view of the projection
 *  matrix.
 *
 *  @param aspect
 *  A scalar which represents the aspect ratio of the projection.
 *
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *
 *  @param zFar
 *  The distance which represents the point at which far away points in 3D
 *  space will be discarded from the projection.
 *
 *  @return
 *  A 4x4 matrix which allows 3D points to be perspective-projected into a 2D
 *  plane through multiplication.
 */
template <typename N> inline
mat4_t<N> perspective(N fov, N aspect, N zNear, N zFar) noexcept;

/**
 *  @brief infinitePerspective
 *  Create a 2D perspective projection matrix in 3D space with no far-clipping
 *  plane. This is useful in applications which do not care about the precision
 *  of floating-point values far from the projection matrix.
 *
 *  @param fov
 *  The angle, in radians, representing the field of view of the projection
 *  matrix.
 *
 *  @param aspect
 *  A scalar which represents the aspect ratio of the projection.
 *
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *
 *  @return
 *  A 4x4 perspective-projection matrix with no far plane.
 */
template <typename N> inline
mat4_t<N> infinite_perspective(N fov, N aspect, N zNear) noexcept;

/**
 *  @brief ortho
 *  Create an orthographic-projection matrix in order to project 3D points
 *  onto a 2D plane. This method will project points without factoring in
 *  distance-scaling.
 *
 *  @param left
 *  the leftmost clipping point of the projection.
 *
 *  @param right
 *  the rightmost clipping point of the projection.
 *
 *  @param top
 *  the topmost clipping point of the projection.
 *
 *  @param bottom
 *  the bottommost clipping point of the projection.
 *
 *  @return a 4x4 ortho-projection matrix which allows 3D points to be
 *  projected into a 2D representation without distance-scaling.
 */
template <typename N> inline
mat4_t<N> ortho(N left, N right, N top, N bottom) noexcept;

/**
 *  @brief ortho
 *  Create an orthographic-projection matrix in order to project 3D points
 *  onto a 2D plane. This method will project points without factoring in
 *  distance-scaling.
 *
 *  @param left
 *  the leftmost clipping point of the projection.
 *
 *  @param right
 *  the rightmost clipping point of the projection.
 *
 *  @param top
 *  the topmost clipping point of the projection.
 *
 *  @param bottom
 *  the bottommost clipping point of the projection.
 *
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *
 *  @param zFar
 *  The distance which represents the point at which far away points in 3D
 *  space will be discarded from the projection.
 *
 *  @return a 4x4 orthographic-projection matrix which allows 3D points to be
 *  projected into a 2D representation without distance-scaling.
 */
template <typename N> inline
mat4_t<N> ortho(N left, N right, N top, N bottom, N zNear, N zFar) noexcept;

/**
 *  @brief frustum
 *  Create a viewing frustum in order to project 3D points into 2D space.
 *
 *  @param left
 *  the leftmost clipping point of the projection.
 *
 *  @param right
 *  the rightmost clipping point of the projection.
 *
 *  @param top
 *  the topmost clipping point of the projection.
 *
 *  @param bottom
 *  the bottommost clipping point of the projection.
 *
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *
 *  @param zFar
 *  The distance which represents the point at which far away points in 3D
 *  space will be discarded from the projection.
 *
 *  @return a 4x4 frustum which allows 3D points to be projected onto a 2D
 *  plane.
 */
template <typename N> inline
mat4_t<N> frustum(N left, N right, N top, N bottom, N zNear, N zFar) noexcept;

/**
 * @brief Create a scissor rectangle which can be applied to a transform just
 * before projection multiplication to "cut out" a specific region of a
 * projection matrix.
 *
 * @param x
 * The x-coordinate to begin the cut-out, in percentage between [0 - 1].
 *
 * @param y
 * The y-coordinate to begin the cut-out, in percentage between [0 - 1].
 *
 * @param w
 * The width of the region to cut, in percentage between [0 - 1].
 * @param h
 * The width of the region to cut, in percentage between [0 - 1].
 *
 * @return A scissor rectangle which can be pre-multiplied against a
 * projection matrix to define a viewport rectangle.
 */
template <typename N> inline
mat4_t<N> scissor(N x, N y, N w, N h) noexcept;

/**
 *  @brief lookAt
 *  Direct the far-plane of a projection matrix towards a point in 3D space.
 *
 *  @param pos
 *  The position, in 3D space, at which the projection matrix will be placed.
 *
 *  @param target
 *  The position of the target point, in 3D space, that the projection matrix
 *  will face.
 *
 *  @param up
 *  The direction of the top of the projection matrix.
 *
 *  @return A rotation matrix that represents a camera's orientation towards a
 *  target in 3D space.
 */
template <typename N> inline
mat4_t<N> look_at(const vec3_t<N>& pos, const vec3_t<N>& target, const vec3_t<N>& up) noexcept;

/**
 *  @brief Look at a target from a specific position in 3D space.
 *
 *  @param pos
 *  The position, in 3D space, at which the projection matrix will be placed.
 *
 *  @param target
 *  The position of the target point, in 3D space, that the projection matrix
 *  will face.
 *
 *  @param up
 *  The direction of the top of the projection matrix.
 *
 *  @return A rotation matrix that represents a camera's orientation towards a
 *  target in 3D space.
 */
template <typename N> inline
mat4_t<N> look_from(const vec3_t<N>& pos, const vec3_t<N>& target, const vec3_t<N>& up) noexcept;

/**
 *  @brief billboard
 *  Retrieve a model matrix in 3D space so that it is oriented towards a
 *  Rotation/View matrix from a certain position.
 *
 *  @param pos
 *  The position in 3D space that the billboard should be placed at.
 *
 *  @param viewMatrix
 *  A camera's view matrix which represents both the the position and
 *  orientation that a billboard should rotate towards.
 *
 *  @return A model matrix at a specified position, which is oriented towards a
 *  camera's view matrix in 3D space.
 */
template <typename N> inline
mat4_t<N> billboard(const vec3_t<N>& pos, const mat4_t<N>& viewMatrix) noexcept;

} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/mat_utils_impl.h"

#ifdef LS_ARCH_X86
    #include "lightsky/math/x86/matf_utils_impl.h"
#elif defined(LS_ARCH_ARM)
    #include "lightsky/math/arm/matf_utils_impl.h"
#endif

#endif    /* LS_MATH_MAT_UTILS_H */
