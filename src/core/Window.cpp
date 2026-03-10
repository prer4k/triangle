#include <glad/glad.h>
#include "core/Window.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window)
    {
        std::cout << "Window failed\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }    

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow* Window::get()
{
    return window;
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::setCursorDisabled(bool disabled)
{
    glfwSetInputMode(
        window,
        GLFW_CURSOR,
        disabled ? GLFW_CURSOR_DISABLED
                 : GLFW_CURSOR_NORMAL
    );
}
