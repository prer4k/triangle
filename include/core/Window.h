#pragma once
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* window;

public:
    Window(int width, int height, const char* title);

    GLFWwindow* get();

    bool shouldClose();

    void swapBuffers();

    void pollEvents();

    void setCursorDisabled(bool disabled);
};
