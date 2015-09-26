cmake_minimum_required(VERSION 2.8)

# -------------------------------------
# Project Setup
# -------------------------------------
project(LightMath CXX)
set(OUTPUT_NAME lsmath)



# -------------------------------------
# Compiler Options
# -------------------------------------
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"
    OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"
)
    set(warnings "-Wall -Werror -Wextra -pedantic -pedantic-errors")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 ${warnings}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${warnings}")

    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG} -std=c99 ${warnings}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 ${warnings}")

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -std=c99 ${warnings}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 ${warnings}")
else()
    message(FATAL_ERROR "Your compiler is currently unsupported.")
endif()



# -------------------------------------
# Source Paths
# -------------------------------------
include_directories("include")



# -------------------------------------
# Library Setup
# -------------------------------------
add_library("${OUTPUT_NAME}" STATIC
            "src/math/fixed.cpp"
            "src/math/mat2.cpp"
            "src/math/mat3.cpp"
            "src/math/mat4.cpp"
            "src/math/mat_utils.cpp"
            "src/math/perlinNoise.cpp"
            "src/math/quat.cpp"
            "src/math/scalar_utils.cpp"
            "src/math/vec2.cpp"
            "src/math/vec3.cpp"
            "src/math/vec4.cpp"
            "src/math/vec_utils.cpp"
)

# Dependencies
target_link_libraries("${OUTPUT_NAME}" liblssetup)



# -------------------------------------
# Library Installation Setup
# -------------------------------------
install(TARGETS "${OUTPUT_NAME}" ARCHIVE DESTINATION lib)
install(DIRECTORY include/lightsky/math DESTINATION include/lightsky)
