#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>


#include "Game/Game.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"

glm::ivec2 g_windowSize(13 * 16, 14 * 16);
std::unique_ptr<CGame> g_game = std::make_unique<CGame>(g_windowSize);





void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;

    const float fMapAspectRatio = 13.f / 14.f;

    unsigned int iViewPortWidth = g_windowSize.x;
    unsigned int iViewPortHeight = g_windowSize.y;

    unsigned int iViewPortLeftOffset = 0;
    unsigned int iViewPortBottomOffset = 0;

    if (static_cast<float>(g_windowSize.x) / g_windowSize.y > fMapAspectRatio)
    {
        iViewPortWidth = static_cast<unsigned int>(g_windowSize.y * fMapAspectRatio);
        iViewPortLeftOffset = (g_windowSize.x - iViewPortWidth) / 2;
    }
    else
    {
        iViewPortHeight = static_cast<unsigned int>(g_windowSize.x / fMapAspectRatio);
        iViewPortBottomOffset = (g_windowSize.y - iViewPortHeight) / 2;
    }

    RenderEngine::CRenderer::setViewport(iViewPortWidth, iViewPortHeight, 
        iViewPortLeftOffset, iViewPortBottomOffset);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    g_game->setKey(key, action);
}

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }
    // устанавливаем версию OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создаем окно OpenGL
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // регистрация коллбэков
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    // Делаем контекст окна OpenGL текущим
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << RenderEngine::CRenderer::getRendererString() << std::endl;
    std::cout << "OpenGL version: " << RenderEngine::CRenderer::getVersionString() << std::endl;

    RenderEngine::CRenderer::setClearColor(0, 0, 0, 1);
    RenderEngine::CRenderer::setDepthTest(true);

    {
        CResourceManager::setExecutablePath(argv[0]);

        g_game->init();

        auto lastTime = std::chrono::high_resolution_clock::now();        

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {    
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            g_game->update(duration);

            /* Render here */
            RenderEngine::CRenderer::clear();

            g_game->render();
            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
        g_game = nullptr;
        CResourceManager::unloadAllResources();
    }

    glfwTerminate();
    return 0;
}