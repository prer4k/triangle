#include "core/Window.h"
#include "core/Shader.h"
#include "core/Input.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"

int main()
{
    bool mouseLocked = false;

    Window window(800,600,"engine");
    Input::setWindow(window.get());

    Renderer renderer;

    Shader shader(
        "./shaders/basic.vert",
        "./shaders/basic.frag"
    );
    Scene scene;

    Camera camera(800.0f/600.0f);

    float lastTime = glfwGetTime();

    while (!window.shouldClose())
    {
        renderer.beginFrame();

        float time = glfwGetTime();
        float dt = time - lastTime;
        lastTime = time;

        scene.update(time);
        camera.update(dt);

        shader.use();

        renderer.draw(
            scene,
            shader,
            camera
        );

        if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) { window.setCursorDisabled(false); mouseLocked = false; }
        if (!mouseLocked && Input::isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) { window.setCursorDisabled(true); mouseLocked = true; }
        if (!mouseLocked &&
            Input::isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            window.setCursorDisabled(true);
            camera.resetMouse();
            mouseLocked = true;
        }
        window.swapBuffers();
        window.pollEvents();
    }
}
