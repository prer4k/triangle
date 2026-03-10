#include "scene/Scene.h"

Scene::Scene()
{
    for (int i = 0; i < 20; i++)
    {
        float x = (rand() % 10) - 5;
        float y = (rand() % 10) - 5;
        float z = (rand() % 10) - 5;

        objects.emplace_back(glm::vec3(x,y,z));
    }
}

void Scene::update(float time)
{
    for (auto& obj : objects)
    {
        obj.update(time);
    }
}

std::vector<Object>& Scene::getObjects()
{
    return objects;
}
