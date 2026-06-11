#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "shaders.h"
#include "Renderer.h"
#include "errors.h"

#include "stb_image.h"


class Skybox
{
private:
    unsigned int m_ID;
    unsigned char* m_LocalBuffer;
    int m_Height, m_Width, m_BPP;

    Shader shader;
    VertexBuffer vb;
    VertexArray va;

    std::string faces1[6] =
    {
        "res/textures/skybox/1.png",
        "res/textures/skybox/2.png",
        "res/textures/skybox/3.png",
        "res/textures/skybox/4.png",
        "res/textures/skybox/5.png",
        "res/textures/skybox/6.png"
    };

    std::string faces2[6] =
    {
        "res/textures/skybox/px.png",
        "res/textures/skybox/nx.png",
        "res/textures/skybox/py.png",
        "res/textures/skybox/ny.png",
        "res/textures/skybox/pz.png",
        "res/textures/skybox/nz.png"
    };

    float vertices[108] = 
    {
        -1.0f,  1.0f, -1.0f,    // BACK FACE
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
    
        -1.0f, -1.0f,  1.0f,    // LEFT FACE
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
    
         1.0f, -1.0f, -1.0f,    // RIGHT FACE
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
    
        -1.0f, -1.0f,  1.0f,    // FRONT FACE
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
    
        -1.0f,  1.0f, -1.0f,    // TOP FACE
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
    
        -1.0f, -1.0f, -1.0f,    // BOTTOM FACE
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

public:
    Skybox();
    void loadToGPU();
    void render(glm::mat4& view, glm::mat4& projection);
};


#endif