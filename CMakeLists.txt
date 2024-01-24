cmake_minimum_required(VERSION 3.27.6)
project(tengin VERSION 1.0)

#
# CMake setup
#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set (CMAKE_VERBOSE_MAKEFILE 0) # 1 should be used for debugging
set (CMAKE_SUPPRESS_REGENERATION TRUE) # Suppresses ZERO_CHECK

#
# GLFW options
#
find_package(glfw3 REQUIRED)

#
# Set include paths
#
include_directories (tengin/src/
                     tengin/vendor/glad/include
                     tengin/vendor/glfw/include
                     tengin/vendor/glm/include
                     tengin/vendor/stb/)

#
# Set relative directory
#
set(SOURCE_DIR ${CMAKE_CURRENT_DIR}/src)

#
# Add files
#
file (GLOB         VENDORS_SOURCES tengin/vendor/glad/src/glad.c
                                   tengin/vendor/glm/glm.hpp)
file (GLOB_RECURSE PROJECT_HEADERS tengin/src/*.hpp)
file (GLOB_RECURSE PROJECT_SOURCES tengin/src/*.cpp)
file (GLOB_RECURSE PROJECT_SHADERS tengin/shaders/*.glsl)
file (GLOB         PROJECT_CONFIGS CMakeLists.txt
                                  .gitignore)

#
# Organizing files
#
source_group ("headers" FILES ${PROJECT_HEADERS})
source_group ("shaders" FILES ${PROJECT_SHADERS})
source_group ("sources" FILES ${PROJECT_SOURCES})
source_group ("vendors" FILES ${VENDORS_SOURCES})

#
# Set executable and target link libraries
#
add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                                ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                                ${VENDORS_SOURCES})
target_link_libraries (${PROJECT_NAME}
                       glfw)
set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})