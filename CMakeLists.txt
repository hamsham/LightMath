
# -------------------------------------
# Project Setup
# -------------------------------------
project(LightMath CXX)
set(OUTPUT_NAME lsmath)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)



# -------------------------------------
# Source Paths
# -------------------------------------
set(LS_MATH_SOURCES
    src/fixed.cpp
    src/mat2.cpp
    src/mat3.cpp
    src/mat4.cpp
    src/mat_utils.cpp
    src/noise.cpp
    src/quat.cpp
    src/scalar_utils.cpp
    src/vec2.cpp
    src/vec3.cpp
    src/vec4.cpp
    src/vec_utils.cpp
)

set(LS_MATH_HEADERS
    include/lightsky/math/bits.h
    include/lightsky/math/constants.h
    include/lightsky/math/fixed.h
    include/lightsky/math/half.h
    include/lightsky/math/interpolate.h
    include/lightsky/math/mat2.h
    include/lightsky/math/mat3.h
    include/lightsky/math/mat4.h
    include/lightsky/math/mat_utils.h
    include/lightsky/math/noise.h
    include/lightsky/math/quat.h
    include/lightsky/math/quat_utils.h
    include/lightsky/math/scalar_utils.h
    include/lightsky/math/vec2.h
    include/lightsky/math/vec3.h
    include/lightsky/math/vec4.h
    include/lightsky/math/vec_swizzle.h
    include/lightsky/math/vec_utils.h

    include/lightsky/math/generic/fixed_impl.h
    include/lightsky/math/generic/Interpolate_impl.h
    include/lightsky/math/generic/mat2_impl.h
    include/lightsky/math/generic/mat3_impl.h
    include/lightsky/math/generic/mat4_impl.h
    include/lightsky/math/generic/mat_utils_impl.h
    include/lightsky/math/generic/noise_impl.h
    include/lightsky/math/generic/quat_impl.h
    include/lightsky/math/generic/quat_utils_impl.h
    include/lightsky/math/generic/scalar_utils_impl.h
    include/lightsky/math/generic/vec2_impl.h
    include/lightsky/math/generic/vec3_impl.h
    include/lightsky/math/generic/vec4_impl.h
    include/lightsky/math/generic/vec_swizzle_impl.h
    include/lightsky/math/generic/vec_utils_impl.h
)

set(LS_MATH_PLATFORM_HEADERS
    include/lightsky/math/generic/bits_impl.h
    include/lightsky/math/generic/half_impl.h

    include/lightsky/math/x86/bits_impl.h
    include/lightsky/math/x86/half_impl.h
    include/lightsky/math/x86/mat4f_impl.h
    include/lightsky/math/x86/matf_utils_impl.h
    include/lightsky/math/x86/quatf_utils_impl.h
    include/lightsky/math/x86/scalarf_utils_impl.h
    include/lightsky/math/x86/vec4f_impl.h
    include/lightsky/math/x86/vecf_swizzle_impl.h
    include/lightsky/math/x86/vecf_utils_impl.h

    include/lightsky/math/arm/half_impl.h
    include/lightsky/math/arm/mat4f_impl.h
    include/lightsky/math/arm/matf_utils_impl.h
    include/lightsky/math/arm/quatf_utils_impl.h
    include/lightsky/math/arm/scalarf_utils_impl.h
    include/lightsky/math/arm/vec4f_impl.h
    include/lightsky/math/arm/vecf_utils_impl.h
)



# -------------------------------------
# Library Setup
# -------------------------------------
add_library(${OUTPUT_NAME} ${LS_MATH_SOURCES} ${LS_MATH_HEADERS} ${LS_MATH_PLATFORM_HEADERS})

ls_configure_cxx_target(${OUTPUT_NAME})
target_include_directories(${OUTPUT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_link_libraries(${OUTPUT_NAME} LightSky::Utils LightSky::Setup)



# -------------------------------------
# Library Installation Setup
# -------------------------------------
install(TARGETS ${OUTPUT_NAME}
    EXPORT LightMath
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(DIRECTORY include/lightsky/math DESTINATION include/lightsky)

install(EXPORT LightMath
    FILE LightMath.cmake
    NAMESPACE LightSky::
    DESTINATION lib/cmake/LightSky
)

export(EXPORT LightMath NAMESPACE LightSky::)
add_library(LightSky::Math ALIAS lsmath)



# -------------------------------------
# Precompiled Headers
# -------------------------------------
if (LIGHTSKY_ENABLE_PCH)
    target_precompile_headers(
        lsmath
        PUBLIC
            ${LS_MATH_HEADERS}
    )
endif()



# -------------------------------------
# Unit Tests
# -------------------------------------
option(LS_MATH_BUILD_TESTS "Build tests for the LightMath library." ON)

if(LS_MATH_BUILD_TESTS)
    add_subdirectory(tests)
endif()

