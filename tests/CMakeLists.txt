
# -------------------------------------
# Project Setup
# -------------------------------------
project(ls_math_tests CXX)



# -------------------------------------
# 3rd-party libraries
# -------------------------------------
include(glmConfig.cmake)



# -------------------------------------
# Building and Linking Targets
# -------------------------------------
function(LS_MATH_ADD_TARGET target sources)
    add_executable(${target} ${sources} ${ARGN})
    target_link_libraries(${target} LightSky::Math LightSky::Utils LightSky::Setup)
endfunction(LS_MATH_ADD_TARGET)

LS_MATH_ADD_TARGET(lsmath_test_atan2    lsmath_test_atan2.cpp)
LS_MATH_ADD_TARGET(lsmath_test_bits     lsmath_test_bits.cpp)
LS_MATH_ADD_TARGET(lsmath_test_exp      lsmath_test_exp.cpp)
LS_MATH_ADD_TARGET(lsmath_test_exp2     lsmath_test_exp2.cpp)
LS_MATH_ADD_TARGET(lsmath_test_fixed    lsmath_test_fixed.cpp)
LS_MATH_ADD_TARGET(lsmath_test_half     lsmath_test_half.cpp)
LS_MATH_ADD_TARGET(lsmath_test_log      lsmath_test_log.cpp)
LS_MATH_ADD_TARGET(lsmath_test_pow2     lsmath_test_pow2.cpp)
LS_MATH_ADD_TARGET(lsmath_test_rcp_sqrt lsmath_test_rcp_sqrt.cpp)
LS_MATH_ADD_TARGET(lsmath_test_signbit  lsmath_test_signbit.cpp)
LS_MATH_ADD_TARGET(lsmath_test_step     lsmath_test_step.cpp)
LS_MATH_ADD_TARGET(lsmath_test_trig     lsmath_test_trig.cpp)
LS_MATH_ADD_TARGET(lsmath_test_vs_glm   lsmath_test_vs_glm.cpp)

if (NOT BUILD_GLM)
    add_dependencies(lsmath_test_vs_glm Glm)
endif()

target_include_directories(lsmath_test_vs_glm PRIVATE ${GLM_INCLUDE_DIR})

