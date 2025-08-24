#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Resources/ResourceManager.h"

// массив вершин
GLfloat points[] = {
    0.0f, 50.f, 0.0f,
    50.f, -50.f, 0.0f,
    -50.f, -50.f, 0.0f
};

// массив цветов вершин
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

// массив координат текстуры
GLfloat texCoords[] =
{
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};


// размеры окна
glm::ivec2 g_windowSize(640, 480);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;

    // определяет область окна, в которую будет выводиться изображение, отрендеренное графическим процессором
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    // если нажата клавиша esc, то выставляем флаг закрытия окна в true
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}


int main(int argc, char** argv)
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
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle city", nullptr, nullptr);
    
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
	
	if(!gladLoadGL())
	{
		std::cout << "Can't load GLAD" << std::endl;
		return -1;
	}

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;	
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(1,1,0,1);

    {
        CResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Cant create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }

        auto pTexture = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");

        GLuint points_vbo = 0; // ID буфера
        glGenBuffers(1, &points_vbo);  // создаёт 1 буферный объект, и его ID записывается в points_vbo
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo); // Привязывает созданный буфер как текущий буфер для вершинных данных
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); // Загружает данные из массива points в GPU.

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoords_vbo = 0;
        glGenBuffers(1, &texCoords_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCoords_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);


        GLuint vao = 0;
        glGenVertexArrays(1, &vao); //  Создаёт VAO и сохраняет его ID в переменную vao
        glBindVertexArray(vao); // Активирует VAO — теперь вся последующая настройка будет привязана к нему

        // Вершины
        glEnableVertexAttribArray(0); //  включает определённый входной атрибут (layout(location = 0) в шейдере).
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo); // Привязывает буфер вершин (VBO)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Описывает, как из буфера points_vbo читать данные для атрибута 0 // 3 компонента (x, y, z), тип float, без смещений

        // Цвета
        glEnableVertexAttribArray(1); // Включает использование атрибута с индексом 1 (обычно — цвет)
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo); // Привязывает буфер цветов
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // Координаты текстуры
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoords_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590, 50.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y),
                                    -100.f, 100.f);

        pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        // цикл отрисовки на экране
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            pTexture->bind();      

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
 

    glfwTerminate();
    return 0;
}