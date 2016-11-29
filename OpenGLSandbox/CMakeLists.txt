cmake_minimum_required(VERSION 3.6)
project(OpenGLSandbox)

# External projects (GLFW and GLAD)
include(ExternalProject)
externalproject_add(glfw-download
        PREFIX GLFW
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.2
        INSTALL_DIR "${PROJECT_BINARY_DIR}/GLFW"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/GLFW"
        )
externalproject_add(glad-download
        PREFIX GLAD
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.11a
        INSTALL_COMMAND   ""
        )
externalproject_add(glm-download
        PREFIX GLM
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.7.5
        INSTALL_DIR "${PROJECT_BINARY_DIR}/GLM"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/GLM"
        )
add_library(glfw STATIC IMPORTED GLOBAL)
add_library(glad STATIC IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/GLFW/lib/libglfw3.a)
set_target_properties(glad PROPERTIES IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/GLAD/src/glad-download-build/libglad.a)

# OpenGL sandbox app
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
add_executable(OpenGLSandbox ${SOURCE_FILES})
# Include locations
target_include_directories(OpenGLSandbox PUBLIC ${PROJECT_BINARY_DIR}/GLFW/include)
target_include_directories(OpenGLSandbox PUBLIC ${PROJECT_BINARY_DIR}/GLAD/src/glad-download-build/include)
target_include_directories(OpenGLSandbox PUBLIC ${PROJECT_BINARY_DIR}/GLM/include)
# Link against GLFW and GLAD
target_link_libraries(OpenGLSandbox glfw glad)


