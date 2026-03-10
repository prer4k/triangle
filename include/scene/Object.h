#pragma once

#include "math/Transform.h"
#include "animation/Animation.h"
#include "graphics/Mesh.h"

class Object
{
public:

    Transform transform;
    Animation animation;
    Mesh mesh;

    Object(glm::vec3 pos);

    void update(float time);

    glm::mat4 getModel();
};
