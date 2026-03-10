#include "renderer/Renderer.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,800,600);
}

void Renderer::beginFrame()
{
    glClearColor(0.1f,0.1f,0.15f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::endFrame()
{
}

void Renderer::setModel(Shader& shader,
                        const glm::mat4& model)
{
    int loc = glGetUniformLocation(
        shader.ID,
        "model"
    );

    glUniformMatrix4fv(
        loc,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );
}

void Renderer::draw(
    Scene& scene,
    Shader& shader,
    Camera& camera)
{
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = camera.getProjectionMatrix();

    int vLoc = glGetUniformLocation(shader.ID,"view");
    int pLoc = glGetUniformLocation(shader.ID,"projection");

    glUniformMatrix4fv(
        vLoc,1,GL_FALSE,
        glm::value_ptr(view));

    glUniformMatrix4fv(
        pLoc,1,GL_FALSE,
        glm::value_ptr(proj));

    for (auto& obj : scene.getObjects())
    {
        glm::mat4 model = obj.getModel();

        int mLoc = glGetUniformLocation(
            shader.ID,
            "model"
        );

        glUniformMatrix4fv(
            mLoc,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        // bind texture
        glActiveTexture(GL_TEXTURE0);
        obj.texture.bind();

        int texLoc =
            glGetUniformLocation(
                shader.ID,
                "tex"
            );

        glUniform1i(texLoc, 0);

        obj.mesh.draw();
    }
}
