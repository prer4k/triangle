#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:

    static void setWindow(GLFWwindow* window);

    static bool isKeyPressed(int key);

private:

    static GLFWwindow* window;
};
