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

    Camera(float aspect);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void update(float dt);
};
