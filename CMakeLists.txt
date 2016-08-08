
# -------------------------------------
# Project Setup
# -------------------------------------
project(LightMath CXX)
set(OUTPUT_NAME lsmath)



# -------------------------------------
# Source Paths
# -------------------------------------
include_directories("include")

set(LS_MATH_SOURCES
    "src/math/fixed.cpp"
    "src/math/mat2.cpp"
    "src/math/mat3.cpp"
    "src/math/mat4.cpp"
    "src/math/mat_utils.cpp"
    "src/math/PerlinNoise.cpp"
    "src/math/quat.cpp"
    "src/math/scalar_utils.cpp"
    "src/math/vec2.cpp"
    "src/math/vec3.cpp"
    "src/math/vec4.cpp"
    "src/math/vec_utils.cpp"
)



# -------------------------------------
# Library Setup
# -------------------------------------
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

if (BUILD_SHARED_LIB)
    add_definitions(-DLS_BUILD_SHARED -DLS_SHARED)
    set(LS_LIB_TYPE SHARED)
else()
    set(LS_LIB_TYPE STATIC)
endif()

add_library("${OUTPUT_NAME}" ${LS_LIB_TYPE} "${LS_MATH_SOURCES}")

# Dependencies
target_link_libraries("${OUTPUT_NAME}" lssetup)



# -------------------------------------
# Library Installation Setup
# -------------------------------------
install(TARGETS "${OUTPUT_NAME}"
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(DIRECTORY include/lightsky/math DESTINATION include/lightsky)
