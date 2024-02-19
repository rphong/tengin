cmake_minimum_required(VERSION 3.27.6)
project(tengin VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

link_directories(tengin/vendor/lib)

find_package(GLM REQUIRED)
find_package(GLFW3 REQUIRED)


file (GLOB         VENDORS_SOURCES tengin/vendor/glad/glad.c)
file (GLOB_RECURSE PROJECT_HEADERS tengin/src/*.hpp)
file (GLOB_RECURSE PROJECT_SOURCES tengin/src/*.cpp)
file (GLOB_RECURSE PROJECT_SHADERS tengin/shaders/*.glsl)
file (GLOB         PROJECT_CONFIGS CMakeLists.txt
                                  .gitignore)

add_definitions (-DGLFW_INCLUDE_NONE)
add_executable (${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
    ${PROJECT_CONFIGS}
    ${VENDORS_SOURCES}
)
                                
target_include_directories (${PROJECT_NAME} 
    PRIVATE
        tengin/vendor/include
        tengin/vendor/include/glad
        tengin/vendor/include/freetype2
)                        

target_link_libraries (${PROJECT_NAME} 
    glm
    glfw3
    freetype
)


set_target_properties (${PROJECT_NAME} 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)