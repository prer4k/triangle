#include "core/Window.h"
#include "core/Shader.h"
#include "core/Input.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"

int main()
{
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

        if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            window.setCursorDisabled(false);
        }
        window.swapBuffers();
        window.pollEvents();
    }
}
