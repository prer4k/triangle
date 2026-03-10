#pragma once

#include "math/Transform.h"
#include "animation/Animation.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"

class Object
{
public:

    Transform transform;
    Animation animation;
    Mesh mesh;
    Texture texture;

    Object(glm::vec3 pos);

    void update(float time);

    glm::mat4 getModel();
};
