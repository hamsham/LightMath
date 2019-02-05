/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   glm_test.cpp
 * Author: miles
 *
 * Created on April 16, 2016, 2:46 PM
 */

#include <iostream>

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

template<typename data_t>
std::ostream& operator<<(std::ostream& ostr, const ls::math::mat4_t<data_t>& m)
{
    return print_mat_type(ostr, m);
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

    const glm::vec3 glmVec3{1.f, 2.f, 3.f};
    std::cout << "GLM cross(vec3): " << glm::cross(glmVec3, glm::vec3{2.f, -1.f, 3.f}) << std::endl;

    const ls::math::vec3 lsVec3{1.f, 2.f, 3.f};
    std::cout << "LS cross(vec3): " << ls::math::cross(lsVec3, ls::math::vec3{2.f, -1.f, 3.f}) << std::endl;

    std::cout << std::endl;

    const glm::vec4 glmVec{1.f, 2.f, 3.f, 4.f};
    const glm::mat4 glmMat = glm::perspective(ls::math::deg_to_rad(fov), aspect, zNear, zFar); // GLM uses degrees
    std::cout << "GLM Perspective: " << glmMat << std::endl;
    std::cout << "GLM mat4 * vec4: " << glmMat * glmVec << std::endl;
    std::cout << "GLM vec4 * mat4: " << glmVec * glmMat << std::endl;
    std::cout << "GLM mat4 * mat4: " << glmMat * glmMat << std::endl;
    std::cout << "GLM transpose(mat4): " << glm::transpose(glmMat) << std::endl;
    std::cout << "GLM dot(vec4): " << glm::dot(glmVec, glmVec) << std::endl;

    std::cout << std::endl;

    const ls::math::vec4 lsVec{1.f, 2.f, 3.f, 4.f};
    const ls::math::mat4 lsMat = ls::math::perspective(ls::math::deg_to_rad(fov), aspect, zNear, zFar);
    std::cout << "ls Perspective: " << lsMat << std::endl;
    std::cout << "ls mat4 * vec4: " << lsMat * lsVec << std::endl;
    std::cout << "ls vec4 * mat4: " << lsVec * lsMat << std::endl;
    std::cout << "ls mat4 * mat4: " << lsMat * lsMat << std::endl;
    std::cout << "ls transpose(mat4): " << ls::math::transpose(lsMat) << std::endl;
    std::cout << "ls dot(vec4): " << ls::math::dot(lsVec, lsVec) << std::endl;

    std::cout << std::endl;

    const glm::quat glmQuat1{4.f, 1.f, 2.f, 3.f};
    const glm::quat glmQuat2{4.f, 3.f, 2.f, 1.f};
    std::cout << "GLM quat1 * quat2: " << glmQuat1 * glmQuat2 << std::endl;
    std::cout << "GLM quat2 * quat1: " << glmQuat2 * glmQuat1 << std::endl;
    std::cout << "GLM quat1 * inverse(quat1): " << glmQuat1 * glm::inverse(glmQuat1) << std::endl;

    std::cout << std::endl;

    const ls::math::quat lsQuat1{1.f, 2.f, 3.f, 4.f};
    const ls::math::quat lsQuat2{3.f, 2.f, 1.f, 4.f};
    std::cout << "ls quat1 * quat2: " << lsQuat1 * lsQuat2 << std::endl;
    std::cout << "ls quat2 * quat1: " << lsQuat2 * lsQuat1 << std::endl;
    std::cout << "ls quat1 * inverse(quat1): " << lsQuat1 * ls::math::inverse(lsQuat1) << std::endl;

    std::cout << std::endl;

    std::cout << "GLM quat1 * mat4: " << glm::mat4_cast(glmQuat1) * glmMat << std::endl;
    std::cout << "ls quat1 * mat4: " << ls::math::quat_to_mat4(lsQuat1) * lsMat << std::endl;

    std::cout << std::endl;

    return 0;
}
