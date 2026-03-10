#include "animation/Animation.h"

#include <cmath>

Animation::Animation()
{
    radius = 0.5f;
    speed  = 2.0f;
}

void Animation::update(Transform& t, float time)
{
    t.rotation.y = time;
    t.rotation.x = time * speed;
}
