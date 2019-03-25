
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
    add_dependencies(${target} Glm)
endfunction(LS_MATH_ADD_TARGET)

LS_MATH_ADD_TARGET(fixed_test fixed_test.cpp)
LS_MATH_ADD_TARGET(glm_test glm_test.cpp)
LS_MATH_ADD_TARGET(logarithm_test logarithm_test.cpp)
LS_MATH_ADD_TARGET(rcp_sqrt_test rcp_sqrt_test.cpp)
LS_MATH_ADD_TARGET(sign_test sign_test.cpp)

