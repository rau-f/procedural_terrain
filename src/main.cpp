#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "include/utils.hpp"
#include "include/VertexArray.h"
#include "include/VertexBuffer.h"
#include "include/IndexBuffer.h"
#include "include/shaders.h"
#include "include/errors.h"
#include "include/Texture.h"
#include "include/Mesh.h"
#include "include/Camera.hpp"
#include "include/Terrain.hpp"
#include "include/Skybox.hpp"


int main()
{
    if(!glfwInit())
    {
        std::cout << "Failed to initialize glfwInit()..." << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // const int screenHeight = 600, screenWidth = 800;
    // GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Practice", NULL, NULL);
    
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Procedural Terrain", primary, nullptr);
    
    if (window == NULL)
    {
        std::cout << "Failed to initialize window!" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    // GLCall(glViewport(0, 0, screenWidth, screenHeight));
    GLCall(glViewport(0, 0, mode->width, mode->height));
    glfwSwapInterval(1);

    Terrain terrain(1200, 1200);
    terrain.getShader().CreateShader("res/shaders/default.vert", "res/shaders/default.frag");
    terrain.sendToGPU();

    Skybox skybox;
    skybox.loadToGPU();

    float aspectRatio = (float)mode->width / (float)mode->height;
    // float aspectRatio = screenWidth / screenHeight;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    Renderer renderer;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 10000.0f);

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        process_input(window, deltaTime, lastFrame);
        glm::mat4 view = camera.GetViewMatrix();

        skybox.render(view, projection);
        terrain.render(view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
