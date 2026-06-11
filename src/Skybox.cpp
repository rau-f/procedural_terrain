#include "include/Skybox.hpp"



Skybox::Skybox()
    : m_ID(0), m_LocalBuffer(0),
    m_Width(0), m_Height(0), m_BPP(0)
{
    GLCall(glGenTextures(1, &m_ID));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);)

    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    
    for (int i = 0; i < 6; i++)
    {
        m_LocalBuffer = stbi_load(faces2[i].c_str(), &m_Width, &m_Height, &m_BPP, 3);

        if (m_LocalBuffer)
        {
            GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
            stbi_image_free(m_LocalBuffer);
        }
        else
        {
            std::cerr << "Failed to load texture file!" << std::endl;
            stbi_image_free(m_LocalBuffer);
        }
    }
}


void Skybox::loadToGPU()
{
    shader.CreateShader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
    shader.Bind();
    shader.SetInt("skybox", 0);

    va.Bind();

    vb.setBufferData(vertices, sizeof(vertices));
    va.LinkAttrib(0, 3, GL_FLOAT, sizeof(float) * 3, (void*) 0);
    
    va.Unbind();
    vb.Unbind();
    shader.Unbind();
}


void Skybox::render(glm::mat4& view, glm::mat4& projection)
{
    shader.Bind();
    va.Bind();

    shader.SetMat4("u_View", glm::value_ptr(view));
    shader.SetMat4("u_Projection", glm::value_ptr(projection));

    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));

    GLCall(glDepthFunc(GL_LEQUAL));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (sizeof(float) * 3)));
    GLCall(glDepthFunc(GL_LESS));
}