
# #####################################
# External Project Setup
# #####################################
# Include the CMake module to support the builds of 3rd-party dependencies
include(ExternalProject)

# Sub-directories within the build folder (not installation folder).
set(EXTERNAL_PROJECT_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/external" CACHE STRING "Build prefix for 3rd-party libraries.")
mark_as_advanced(EXTERNAL_PROJECT_PREFIX)

# Include directory for 3rd-party libraries
#include_directories(BEFORE SYSTEM ${EXTERNAL_PROJECT_PREFIX}/include)



# #####################################
# Folders for the external data
# #####################################
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX})
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/include)
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/lib)
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/bin)



# #####################################
# Version Control Tools
# #####################################
find_package(Git REQUIRED)



# #####################################
# External build for GLM (for testing only)
# #####################################
message("-- Building GLM from source")

set(GLM_BRANCH "master" CACHE STRING "Git branch or tag for checking out GLM.")
#set(GLM_BRANCH "0.9.9.2" CACHE STRING "Git branch or tag for checking out GLM.")
mark_as_advanced(GLM_BRANCH)

# Configure build options
set(GLM_BUILD_FLAGS
    -DBUILD_SHARED_LIBS:BOOL=FALSE
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_INSTALL_PREFIX:FILEPATH=${EXTERNAL_PROJECT_PREFIX}
    -DCMAKE_SYSTEM_NAME:STRING=${CMAKE_SYSTEM_NAME}
    -DGLM_TEST_ENABLE:BOOL=OFF
    -DGLM_TEST_ENABLE_CXX_11:BOOL=ON
    -DGLM_TEST_ENABLE_CXX_14:BOOL=OFF
    -DGLM_TEST_ENABLE_CXX_17:BOOL=OFF
    -DGLM_TEST_ENABLE_CXX_20:BOOL=OFF
    -DGLM_TEST_ENABLE_LANG_EXTENSIONS:BOOL=OFF
    -DGLM_TEST_ENABLE_FAST_MATH:BOOL=OFF)
mark_as_advanced(GLM_BUILD_FLAGS)

# Compiler settings for GLM
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

# Build GLM
ExternalProject_Add(
    Glm
    PREFIX
        ${EXTERNAL_PROJECT_PREFIX}
    GIT_REPOSITORY
        "https://github.com/g-truc/glm.git"
    GIT_TAG
        "${GLM_BRANCH}"
    UPDATE_COMMAND
        ${GIT_EXECUTABLE} fetch
    CMAKE_COMMAND
        #${CMAKE_COMMAND}
        ""
    CMAKE_CACHE_ARGS
        #${GLM_BUILD_FLAGS}
        ""
    CMAKE_ARGS
        #${GLM_BUILD_FLAGS}
        ""
    BUILD_COMMAND
        #${CMAKE_COMMAND} --build . --config ${CMAKE_CFG_INTDIR}
        ""
    INSTALL_DIR
        #${EXTERNAL_PROJECT_PREFIX}
        ""
    INSTALL_COMMAND
        #${CMAKE_COMMAND} --build . --config ${CMAKE_CFG_INTDIR} --target install
        ${CMAKE_COMMAND} -E copy_directory ${EXTERNAL_PROJECT_PREFIX}/src/Glm/glm ${EXTERNAL_PROJECT_PREFIX}/include/glm
)

set_target_properties(Glm PROPERTIES EXCLUDE_FROM_ALL TRUE)
