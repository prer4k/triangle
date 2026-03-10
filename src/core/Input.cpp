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
