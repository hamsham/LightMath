
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
add_library("${OUTPUT_NAME}" STATIC "${LS_MATH_SOURCES}")

# Dependencies
target_link_libraries("${OUTPUT_NAME}" lssetup)



# -------------------------------------
# Library Installation Setup
# -------------------------------------
install(TARGETS "${OUTPUT_NAME}" ARCHIVE DESTINATION lib)
install(DIRECTORY include/lightsky/math DESTINATION include/lightsky)
