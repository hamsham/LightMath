/*
 * File:   glm_test.cpp
 * Author: miles
 *
 * Created on April 16, 2016, 2:46 PM
 */

#include <assert.h>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL 1
#define GLM_FORCE_XYZW_ONLY 1
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "lightsky/math/vec4.h"
#include "lightsky/math/mat4.h"
#include "lightsky/math/mat_utils.h"
#include "lightsky/math/quat.h"
#include "lightsky/math/quat_utils.h"



template<typename vec_t>
std::ostream& print_vec4_type(std::ostream& ostr, const vec_t& v)
{
    return ostr << "{ " << v[0] << ' ' << v[1] << ' ' << v[2] << ' ' << v[3] << " }";
}

template<typename vec_t>
std::ostream& print_vec3_type(std::ostream& ostr, const vec_t& v)
{
    return ostr << "{ " << v[0] << ' ' << v[1] << ' ' << v[2] << " }";
}


template<typename mat_t, unsigned r = 4, unsigned c = 4>
std::ostream& print_mat_type(std::ostream& ostr, const mat_t& m)
{
    ostr << '{';

    for (unsigned i = 0; i < r; ++i)
    {
        ostr << " {";
        for (unsigned j = 0; j < c; ++j)
        {
            ostr << ' ' << m[i][j] << ' ';
        }

        if (i == 3)
        {
            ostr << "} ";
        }
        else
        {
            ostr << "}, ";
        }
    }

    return ostr << "}";
}



std::ostream& operator<<(std::ostream& ostr, const glm::vec3& v)
{
    return print_vec3_type(ostr, v);
}

template<typename data_t>
std::ostream& operator<<(std::ostream& ostr, const ls::math::vec3_t<data_t>& v)
{
    return print_vec3_type(ostr, v);
}

std::ostream& operator<<(std::ostream& ostr, const glm::vec4& v)
{
    return print_vec4_type(ostr, v);
}

template<typename data_t>
std::ostream& operator<<(std::ostream& ostr, const ls::math::vec4_t<data_t>& v)
{
    return print_vec4_type(ostr, v);
}

std::ostream& operator<<(std::ostream& ostr, const glm::quat& q)
{
    return print_vec4_type(ostr, q);
}

template<typename data_t>
std::ostream& operator<<(std::ostream& ostr, const ls::math::quat_t<data_t>& q)
{
    return print_vec4_type(ostr, q);
}

std::ostream& operator<<(std::ostream& ostr, const glm::mat4x4& m)
{
    return print_mat_type(ostr, m);
}

std::ostream& operator<<(std::ostream& ostr, const glm::mat3x3& m)
{
    return print_mat_type<glm::mat3x3, 3, 3>(ostr, m);
}

template<typename data_t>
std::ostream& operator<<(std::ostream& ostr, const ls::math::mat4_t<data_t>& m)
{
    return print_mat_type(ostr, m);
}

template<typename data_t>
std::ostream& operator<<(std::ostream& ostr, const ls::math::mat3_t<data_t>& m)
{
    return print_mat_type<ls::math::mat3_t<data_t>, 3, 3>(ostr, m);
}



/*
 *
 */
int main()
{
    const float fov = 60.f;
    const float zNear = 0.1f;
    const float zFar = 100.f;
    const float camWidth = 4.f;
    const float camHeight = 3.f;
    const float aspect = camWidth / camHeight;

    std::cout << "STD sqrt(fov): " << std::sqrt(fov) << std::endl;
    std::cout << "LS sqrt(fov): " << ls::math::fast_sqrt(fov) << std::endl;

    std::cout << "STD rsqrt(aspect): " << (1.f/std::sqrt(aspect)) << std::endl;
    std::cout << "LS rsqrt(aspect): " << ls::math::inversesqrt(aspect) << std::endl;
    std::cout << std::endl;

    const glm::vec3 glmVec3{1.f, -2.f, -3.f};
    std::cout << "GLM cross(vec3): " << glm::cross(glmVec3, glm::vec3{2.f, -1.f, 3.f}) << std::endl;

    const ls::math::vec3 lsVec3{1.f, -2.f, -3.f};
    std::cout << "LS cross(vec3): " << ls::math::cross(lsVec3, ls::math::vec3{2.f, -1.f, 3.f}) << std::endl;

    const ls::math::vec4 lsVec4{1.f, -2.f, -3.f, 4.f};
    std::cout << "LS cross(vec4): " << ls::math::cross(lsVec4, ls::math::vec4{2.f, -1.f, 3.f, 1.f}) << std::endl;
    std::cout << "LS sign mask(vec4): " << ls::math::sign_mask(lsVec4) << std::endl;

    std::cout << std::endl;

    const glm::vec4 glmVec{1.f, 2.f, 3.f, 4.f};
    const glm::mat4 glmMat = glm::mat4{
        0.f,  1.f,  2.f,  3.f,
        4.f,  5.f,  6.f,  7.f,
        8.f,  9.f,  10.f, 11.f,
        12.f, 13.f, 14.f, 15.f
    };
    std::cout << "GLM Perspective: " << glm::perspective(ls::math::radians(fov), aspect, zNear, zFar) << std::endl;
    std::cout << "GLM Look At: " << glm::lookAt(glm::vec3{4.f, 2.f, 3.f}, glm::vec3{-1.f, 0.f, 1.f}, glm::vec3{0.f, 1.f, 0.f}) << std::endl;
    std::cout << "GLM mat4 * vec4: " << glmMat * glmVec << std::endl;
    std::cout << "GLM vec4 * mat4: " << glmVec * glm::outerProduct(glmVec, glmVec) << std::endl;
    std::cout << "GLM mat4 * mat4: " << glmMat * glmMat << std::endl;
    std::cout << "GLM transpose(mat4): " << glm::transpose(glmMat) << std::endl;
    std::cout << "GLM determinant(mat4): " << glm::determinant(glmMat) << std::endl;
    std::cout << "GLM inverse(mat4): " << glm::inverse(glmMat) << std::endl;
    std::cout << "GLM determinant(mat3): " << glm::determinant(glm::mat3{glmMat}) << std::endl;
    std::cout << "GLM inverse(mat3): " << glm::inverse(glm::mat3{glmMat}) << std::endl;
    std::cout << "GLM dot(vec4): " << glm::dot(glmVec, glmVec) << std::endl;
    std::cout << "GLM outer(vec4): " << glm::outerProduct(glmVec, glmVec) << std::endl;
    std::cout << "GLM normalize(vec4): " << glm::normalize(glmVec) << std::endl;
    std::cout << "GLM length(vec4): " << glm::length(glmVec) << std::endl;

    std::cout << std::endl;

    const ls::math::vec4 lsVec{1.f, 2.f, 3.f, 4.f};
    const ls::math::mat4 lsMat = ls::math::mat4{
        0.f,  1.f,  2.f,  3.f,
        4.f,  5.f,  6.f,  7.f,
        8.f,  9.f,  10.f, 11.f,
        12.f, 13.f, 14.f, 15.f
    };
    std::cout << "ls Perspective: " << ls::math::perspective(ls::math::radians(fov), aspect, zNear, zFar) << std::endl;
    std::cout << "LS Look At: " << ls::math::look_from(ls::math::vec3{4.f, 2.f, 3.f}, ls::math::vec3{-1.f, 0.f, 1.f}, ls::math::vec3{0.f, 1.f, 0.f}) << std::endl;
    std::cout << "ls mat4 * vec4: " << lsMat * lsVec << std::endl;
    std::cout << "ls vec4 * mat4: " << lsVec * ls::math::outer(lsVec, lsVec) << std::endl;
    std::cout << "ls mat4 * mat4: " << lsMat * lsMat << std::endl;
    std::cout << "ls transpose(mat4): " << ls::math::transpose(lsMat) << std::endl;
    std::cout << "ls determinant(mat4): " << ls::math::determinant(lsMat) << std::endl;
    std::cout << "ls inverse(mat4): " << ls::math::inverse(lsMat) << std::endl;
    std::cout << "ls determinant(mat3): " << ls::math::determinant(ls::math::mat3{lsMat}) << std::endl;
    std::cout << "ls inverse(mat3): " << ls::math::inverse(ls::math::mat3{lsMat}) << std::endl;
    std::cout << "ls dot(vec4): " << ls::math::dot(lsVec, lsVec) << std::endl;
    std::cout << "ls outer(vec4): " << ls::math::outer(lsVec, lsVec) << std::endl;
    std::cout << "LS normalize(vec4): " << ls::math::normalize(lsVec) << std::endl;
    std::cout << "LS length(vec4): " << ls::math::length(lsVec) << std::endl;

    std::cout << std::endl;

    const glm::quat glmQuat1{4.f, 1.f, 2.f, 3.f};
    const glm::quat glmQuat2{4.f, 3.f, 2.f, 1.f};
    std::cout << "GLM quat1 * quat2: " << glmQuat1 * glmQuat2 << std::endl;
    std::cout << "GLM quat2 * quat1: " << glmQuat2 * glmQuat1 << std::endl;
    std::cout << "GLM quat1 * inverse(quat1): " << glmQuat1 * glm::inverse(glmQuat1) << std::endl;
    std::cout << "GLM length(quat1): " << glm::length(glmQuat1) << std::endl;
    std::cout << "GLM normalize(quat1): " << glm::normalize(glmQuat1) << std::endl;

    std::cout << std::endl;

    const ls::math::quat lsQuat1{1.f, 2.f, 3.f, 4.f};
    const ls::math::quat lsQuat2{3.f, 2.f, 1.f, 4.f};
    std::cout << "ls quat1 * quat2: " << lsQuat1 * lsQuat2 << std::endl;
    std::cout << "ls quat2 * quat1: " << lsQuat2 * lsQuat1 << std::endl;
    std::cout << "ls quat1 * inverse(quat1): " << lsQuat1 * ls::math::inverse(lsQuat1) << std::endl;
    std::cout << "LS length(quat1): " << ls::math::length(lsQuat1) << std::endl;
    std::cout << "LS normalize(quat1): " << ls::math::normalize(lsQuat1) << std::endl;

    std::cout << std::endl;

    std::cout << "GLM quat1 * mat4: " << glm::mat4_cast(glmQuat1) * glmMat << std::endl;
    std::cout << "ls quat1 * mat4: " << ls::math::quat_to_mat4(lsQuat1) * lsMat << std::endl;

    std::cout << "GLM mat4 to quat1: " << glm::quat_cast(glmMat) << std::endl;
    std::cout << "ls mat4 to quat1: " << ls::math::mat_to_quat(lsMat) << std::endl;

    std::cout << std::endl;

    return 0;
}
