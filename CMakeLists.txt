cmake_minimum_required(VERSION 3.14)
project(procedural_terrain)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLVND preference is Linux-only; harmless but unnecessary on Windows
if (UNIX)
    cmake_policy(SET CMP0072 NEW)
    set(OpenGL_GL_PREFERENCE "GLVND")
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# --------------------------------------------------------------------------
# Dependencies: each one tries find_package first, falls back to FetchContent
# --------------------------------------------------------------------------

# -- OpenGL (system-only, no fallback) --
find_package(OpenGL REQUIRED)

# -- GLFW --
find_package(glfw3 QUIET)
if (NOT glfw3_FOUND)
    message(STATUS "[deps] glfw3 not found on system -- fetching from source")
    set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8
    )
    FetchContent_MakeAvailable(glfw)
else()
    message(STATUS "[deps] glfw3 found on system")
endif()

# -- GLAD --
find_package(glad QUIET)
if (NOT glad_FOUND)
    message(STATUS "[deps] glad not found on system -- fetching from source")
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        master
    )
    FetchContent_MakeAvailable(glad)
else()
    message(STATUS "[deps] glad found on system")
endif()

# -- GLM --
find_package(glm QUIET)
if (NOT glm_FOUND)
    message(STATUS "[deps] glm not found on system -- fetching from source")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        0.9.9.8
    )
    FetchContent_MakeAvailable(glm)
else()
    message(STATUS "[deps] glm found on system")
endif()

# --------------------------------------------------------------------------
# Target
# --------------------------------------------------------------------------

add_executable(procedural_terrain
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
target_include_directories(procedural_terrain PRIVATE include)
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Link libraries
target_link_libraries(procedural_terrain glfw OpenGL::GL glm::glm)

# --------------------------------------------------------------------------
# Copy resources next to the executable so paths work on every platform
# --------------------------------------------------------------------------
add_custom_command(TARGET procedural_terrain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res" "$<TARGET_FILE_DIR:procedural_terrain>/res"
    COMMENT "Copying res/ to output directory"
)

# Set Visual Studio debugger working directory to the exe location
set_target_properties(procedural_terrain PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:procedural_terrain>"
)
