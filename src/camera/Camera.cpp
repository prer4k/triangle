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

    yaw = -90.0f;
    pitch = 0.0f;

    sensitivity = 0.1f;

    firstMouse = true;
}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 front;

    front.x =
        cos(glm::radians(yaw)) *
        cos(glm::radians(pitch));

    front.y =
        sin(glm::radians(pitch));

    front.z =
        sin(glm::radians(yaw)) *
        cos(glm::radians(pitch));

    glm::vec3 dir = glm::normalize(front);

    return glm::lookAt(
        position,
        position + dir,
        glm::vec3(0,1,0)
    );
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
    glm::vec3 front = getFront();

    glm::vec3 right =
        glm::normalize(
            glm::cross(
                front,
                glm::vec3(0,1,0)
            )
        );

    if (Input::isKeyPressed(GLFW_KEY_W))
        position += front * speed * dt;

    if (Input::isKeyPressed(GLFW_KEY_S))
        position -= front * speed * dt;

    if (Input::isKeyPressed(GLFW_KEY_A))
        position -= right * speed * dt;

    if (Input::isKeyPressed(GLFW_KEY_D))
        position += right * speed * dt;


    double x = Input::getMouseX();
    double y = Input::getMouseY();

    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    double dx = x - lastX;
    double dy = lastY - y;

    lastX = x;
    lastY = y;

    yaw += dx * sensitivity;
    pitch += dy * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

glm::vec3 Camera::getFront()
{
    glm::vec3 front;

    front.x =
        cos(glm::radians(yaw)) *
        cos(glm::radians(pitch));

    front.y =
        sin(glm::radians(pitch));

    front.z =
        sin(glm::radians(yaw)) *
        cos(glm::radians(pitch));

    return glm::normalize(front);
}

void Camera::resetMouse()
{
    firstMouse = true;
}
