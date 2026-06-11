cmake_minimum_required(VERSION 3.10)
project(procedural_terrian)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find system-installed GLFW first
find_package(glfw3 QUIET)

include(FetchContent)

if (NOT glfw3_FOUND)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8
    )
    FetchContent_MakeAvailable(glfw)
endif()

if (NOT glad_FOUND)
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(glad)
endif()

# Fetch GLM if not installed
find_package(glm QUIET)
if (NOT glm_FOUND)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
    )
    FetchContent_MakeAvailable(glm)
endif()

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE "GLVND")

# Find OpenGL and GLFW
find_package(OpenGL REQUIRED)

# Add executable
add_executable(procdural_terrain
    src/main.cpp
    src/glad.c
    src/IndexBuffer.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/Renderer.cpp
    src/shaders.cpp
    src/errors.cpp
    src/Texture.cpp
    src/stb_image.cpp
    src/Mesh.cpp
    src/PerlinNoise.cpp
    src/Camera.cpp
    src/Terrain.cpp
    src/utils.cpp
    src/Skybox.cpp
)

# Include directories
target_include_directories(procdural_terrain PRIVATE include)
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Link libraries
target_link_libraries(procdural_terrain glfw OpenGL::GL glm::glm)
