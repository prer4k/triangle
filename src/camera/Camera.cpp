#include "camera/Camera.h"
#include "core/Input.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspect)
{
    position = {0.0f, 0.0f, 5.0f};

    this->aspect = aspect;

    fov = 45.0f;
    nearPlane = 0.1f;
    farPlane = 100.0f;
    speed = 2.5f;
}

glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 view(1.0f);

    view = glm::translate(
        view,
        -position
    );

    return view;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(
        glm::radians(fov),
        aspect,
        nearPlane,
        farPlane
    );
}

void Camera::update(float dt)
{
    if (Input::isKeyPressed(GLFW_KEY_W))
        position.z -= speed * dt;

    if (Input::isKeyPressed(GLFW_KEY_S))
        position.z += speed * dt;

    if (Input::isKeyPressed(GLFW_KEY_A))
        position.x -= speed * dt;

    if (Input::isKeyPressed(GLFW_KEY_D))
        position.x += speed * dt;
}
