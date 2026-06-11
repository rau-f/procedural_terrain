# Procedural Terrain Generation

A real-time procedural terrain generator built with C++ and OpenGL. The terrain is produced using Perlin noise with fractal Brownian motion (fBm) and rendered with height-based biome coloring and directional lighting. The project is a work in progress.

## Overview

The application generates a heightmap mesh at startup using layered Perlin noise, assigns per-vertex normals for smooth shading, and renders the result in a fullscreen OpenGL window. A cubemap skybox provides the backdrop. The fragment shader colors the terrain based on elevation, producing distinct water, sand, grass, rock, and snow biomes.

## Tech Stack

| Component       | Technology                     |
|-----------------|--------------------------------|
| Language        | C++17                          |
| Graphics API    | OpenGL 3.3 Core Profile       |
| Windowing       | GLFW 3.3                      |
| GL Loader       | GLAD                          |
| Math            | GLM                           |
| Image Loading   | stb_image                     |
| Build System    | CMake 3.10+                   |

## Project Structure

```
procedural_terrain/
├── CMakeLists.txt
├── src/
│   ├── main.cpp              # Entry point, window and render loop
│   ├── Terrain.cpp           # Mesh generation from Perlin noise heightmap
│   ├── PerlinNoise.cpp       # Improved Perlin noise implementation
│   ├── Camera.cpp            # First-person camera with mouse and keyboard input
│   ├── Skybox.cpp            # Cubemap skybox loader and renderer
│   ├── shaders.cpp           # Shader compilation and uniform management
│   ├── Renderer.cpp          # Draw call abstraction
│   ├── Mesh.cpp              # Abstract base mesh class
│   ├── VertexArray.cpp       # VAO wrapper
│   ├── VertexBuffer.cpp      # VBO wrapper
│   ├── IndexBuffer.cpp       # EBO wrapper
│   ├── Texture.cpp           # 2D texture loader
│   ├── utils.cpp             # Input handling and global camera
│   ├── errors.cpp            # OpenGL error checking
│   ├── glad.c                # GLAD loader source
│   ├── stb_image.cpp         # stb_image implementation
│   └── include/              # Header files
├── res/
│   ├── shaders/
│   │   ├── default.vert      # Terrain vertex shader
│   │   ├── default.frag      # Terrain fragment shader (biome coloring + lighting)
│   │   ├── skybox.vert       # Skybox vertex shader
│   │   └── skybox.frag       # Skybox fragment shader
│   └── textures/
│       └── skybox/           # Cubemap face textures
└── include/
    ├── glad/                 # GLAD headers
    └── KHR/                  # Khronos platform headers
```

## Building

### Prerequisites

- A C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.10 or later
- OpenGL drivers
- GLFW 3 (installed system-wide, or fetched automatically by CMake)
- GLM (header-only math library)

### Build Steps

```bash
mkdir build && cd build
cmake ..
make
```

The executable `procdural_terrain` will be created in the build directory.

### Running

Run from the build directory so that shader and texture paths resolve correctly:

```bash
cd build
./procdural_terrain
```

The application launches in fullscreen.

## Controls

| Key             | Action            |
|-----------------|--------------------|
| W / S           | Move forward / back |
| A / D           | Strafe left / right |
| E / Q           | Move up / down      |
| Arrow Keys      | Look around         |
| Mouse           | Free look           |

## How It Works

1. **Noise Generation** -- A Perlin noise function (based on Ken Perlin's improved reference implementation) produces coherent gradient noise. The terrain samples this noise with 12 octaves of fBm to create natural-looking elevation.

2. **Mesh Construction** -- A grid of 1200x1200 vertices is generated. Each vertex height is derived from the noise function. Vertices below a threshold are clamped to a flat water level. Per-vertex normals are computed from face normals for smooth shading.

3. **Biome Coloring** -- The fragment shader maps vertex height to five biome zones: water, sand, grass, rock, and snow. A directional light provides diffuse and ambient shading.

4. **Skybox** -- A cubemap texture is loaded and rendered behind the scene using a dedicated shader that strips the translation component from the view matrix.

## Status

This project is not fully completed. Planned or incomplete features include:

- Texture mapping for terrain surfaces
- Chunk-based terrain for infinite generation
- Level of detail (LOD) system
- Improved biome blending between elevation zones
