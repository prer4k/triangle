#include "core/Input.h"

GLFWwindow* Input::window = nullptr;

void Input::setWindow(GLFWwindow* w)
{
    window = w;
}

bool Input::isKeyPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::isMousePressed(int button)
{
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

double Input::getMouseX()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return x;
}

double Input::getMouseY()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return y;
}
