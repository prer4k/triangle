#pragma once

#include <glm/glm.hpp>

class Camera
{
public:

    glm::vec3 position;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;

    float speed;

    float yaw;
    float pitch;

    float sensitivity;

    double lastX;
    double lastY;

    bool firstMouse;

    Camera(float aspect);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getFront();

    void update(float dt);
    void resetMouse();
};
