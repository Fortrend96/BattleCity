#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer/ShaderProgram.h"

// массив вершин
GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

// массив цветов вершин
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

// шейдеры

// вертексный шейдер
const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

// фрагментный шейдер
const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

// размеры окна
int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;

    // определяет область окна, в которую будет выводиться изображение, отрендеренное графическим процессором
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    // если нажата клавиша esc, то выставляем флаг закрытия окна в true
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
    GLFWwindow* pWindow = glfwCreateWindow(640, 480, "Battle city", nullptr, nullptr);
    
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

    std::string strVertexShader(vertex_shader);
    std::string strFragmentShader(fragment_shader);

    Renderer::CShaderProgram shaderProgram(strVertexShader, strFragmentShader);

    if (!shaderProgram.isCompiled())
    {
        std::cerr << "Cant create shader program!" << std::endl;
        return -1;
    }


    GLuint points_vbo = 0; // ID буфера
    glGenBuffers(1, &points_vbo);  // создаёт 1 буферный объект, и его ID записывается в points_vbo
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo); // Привязывает созданный буфер как текущий буфер для вершинных данных
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); // Загружает данные из массива points в GPU.

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);  
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


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

    // цикл отрисовки на экране
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();

        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}