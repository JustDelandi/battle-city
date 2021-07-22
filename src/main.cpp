#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer/shaderProgram.h"

GLfloat points[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
}; 

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertexShader =
"#version 460\n" // OpenGl version
"layout(location = 0) in vec3 vertexPosition;" //in - inputable, 3 - number in vector
"layout(location = 1) in vec3 vertexColor;"
"out vec3 color;"
"void main() {"
"   color = vertexColor;"
"   gl_Position = vec4(vertexPosition, 1.0);"
"}";

const char* fragmentShader =
"#version 460\n"
"in vec3 color;"
"out vec4 fragColor;"
"void main() {"
"   fragColor = vec4(color, 1.0);"
"}";

int g_WindowSizeX = 640;
int g_WindowSizeY = 480;// g - is global

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_WindowSizeX = width;
    g_WindowSizeY = height;
    glViewport(0, 0, g_WindowSizeX, g_WindowSizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(int argc, char* argv[])
{
    
    if (!glfwInit())
    {
        std::cout << "glfwInit error!!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//openGL minimum version for start program
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(g_WindowSizeX, g_WindowSizeY, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!\n";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);//all function on this window

    if (!gladLoadGL())
    {
        std::cout << "gladLoadGL failed!\n";
        return -1;
    }
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);

    std::string VertexShader(vertexShader);
    std::string FragmentShader(fragmentShader);
    Renderer::ShaderProgram shaderProgram(VertexShader, FragmentShader);
    
    if (!shaderProgram.isCompiled())
    {
        std::cerr << "Can't create shader program \n";
        return -1;
    }

    GLuint pointsVBO = 0;
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colorsVBO = 0;
    glGenBuffers(1, &colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;// vectors attribute(array) object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(pWindow))
    { 
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}