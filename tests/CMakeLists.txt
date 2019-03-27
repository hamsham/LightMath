
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
    target_link_libraries(${target} lsmath lsutils)
endfunction(LS_MATH_ADD_TARGET)

LS_MATH_ADD_TARGET(lsmath_test_exp      lsmath_test_exp.cpp)
LS_MATH_ADD_TARGET(lsmath_test_exp2     lsmath_test_exp2.cpp)
LS_MATH_ADD_TARGET(lsmath_test_fixed    lsmath_test_fixed.cpp)
LS_MATH_ADD_TARGET(lsmath_test_log      lsmath_test_log.cpp)
LS_MATH_ADD_TARGET(lsmath_test_rcp_sqrt lsmath_test_rcp_sqrt.cpp)
LS_MATH_ADD_TARGET(lsmath_test_signbit  lsmath_test_signbit.cpp)
LS_MATH_ADD_TARGET(lsmath_test_trig     lsmath_test_trig.cpp)
LS_MATH_ADD_TARGET(lsmath_test_vs_glm   lsmath_test_vs_glm.cpp)

add_dependencies(lsmath_test_vs_glm Glm)

