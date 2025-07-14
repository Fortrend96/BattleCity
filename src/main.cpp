#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


// размеры окна
int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfwWindowZieCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;

    // определяет область окна, в которую будет выводиться изображение, отрендеренное графическим процессором
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}


int main(void)
{
    if (!glfwInit())
    {
        std::cout << "glfw init failed!" << std::endl;
        return -1;
    }

    // устанавливаем версию OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   // Создаем окно OpenGL
    GLFWwindow* pWindow = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // регистрация коллбэков
    glfwSetWindowSizeCallback(pWindow, glfwWindowZieCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    // Делаем контекст окна OpenGL текущим
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL())
	{
		std::cout << "Can't load GLAD" << std::endl;
		return -1;
	}

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;	
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(1,1,0,1);

   // цикл отрисовки на экране
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}