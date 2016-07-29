
# -------------------------------------
# Project Setup
# -------------------------------------
project(ls_math_tests CXX)



# -------------------------------------
# Include Paths
# -------------------------------------
include_directories(".")



# -------------------------------------
# Dependency Setup
# -------------------------------------
set(
    LS_MATH_INTERNAL_DEPS
    ls_utils
    ls_math
)



# -------------------------------------
# Source Paths
# -------------------------------------
set(LS_MATH_TEST_SOURCES
)

set(
    LS_MATH_TEST_SOURCES_HELLOWORLD
    "glm_test.cpp"
    ${LS_MATH_TEST_SOURCES}
    ${LS_MATH_TEST_HEADERS}
)



# -------------------------------------
# Building and Linking Targets
# -------------------------------------
function(LS_MATH_ADD_TARGET trg srcs)
    add_executable(${trg} ${srcs})
    add_dependencies(${trg} ${LS_MATH_INTERNAL_DEPS})
    target_link_libraries(${trg} ${LS_MATH_INTERNAL_DEPS} ${LS_MATH_EXTERNAL_DEPS})
endfunction(LS_MATH_ADD_TARGET)

LS_MATH_ADD_TARGET(ls_math_glm_test "${LS_MATH_TEST_SOURCES_HELLOWORLD}")

