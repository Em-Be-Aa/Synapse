#include "Renderer2D.h"
#include "Shader.h"
#include "../Managers/RenderManager.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>


// Simplify this
namespace
{
    struct Submission { unsigned int textureID; glm::mat4 model; glm::vec4 uv; glm::vec4 tint; int layer; };
    static std::vector<Submission> submissions;

    // GL resources
    static unsigned int quadVAO = 0, quadVBO = 0;
    static Shader* spriteShader = nullptr;
    static glm::mat4 viewProjMatrix = glm::mat4(1.0f);
    static glm::mat4 viewMatrix = glm::mat4(1.0f);
    static glm::mat4 projectionMatrix = glm::mat4(1.0f);
}

void Renderer2D::Init(const char* spriteVertexShaderPath, const char* spriteFragmentShaderPath)
{
    // create shared unit quad (positions + uv)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // create shader
    spriteShader = new Shader(spriteVertexShaderPath, spriteFragmentShaderPath);
}

void Renderer2D::Shutdown()
{
    if (spriteShader) { delete spriteShader; spriteShader = nullptr; }
    if (quadVBO) { glDeleteBuffers(1, &quadVBO); quadVBO = 0; }
    if (quadVAO) { glDeleteVertexArrays(1, &quadVAO); quadVAO = 0; }
}

void Renderer2D::BeginScene(const glm::mat4& view, const glm::mat4& projection)
{
    viewMatrix = view;
    projectionMatrix = projection;
    // store view in first matrix and projection in second via globals
    submissions.clear();
    // store view/projection in shader uniforms at Flush time
    // (we keep them as globals here for Flush)
    // Use static variables on top of file if needed; but we'll just set uniforms in Flush using passed matrices
}

void Renderer2D::Submit(const RenderComponent& rc)
{
    Submission s;
    s.textureID = rc.textureID;
    s.model = rc.model;
    s.uv = rc.uvScaleOffset;
    s.tint = glm::vec4(1.0f);
    s.layer = rc.layer;
    submissions.push_back(s);
}

void Renderer2D::Submit(unsigned int textureID, const glm::mat4& model, const glm::vec4& uvScaleOffset)
{
    Submission s;
    s.textureID = textureID;
    s.model = model;
    s.uv = uvScaleOffset;
    s.tint = glm::vec4(1.0f);
    s.layer = 0;
    submissions.push_back(s);
}

void Renderer2D::EndScene()
{
    Flush();
}

void Renderer2D::Flush()
{
    if (!spriteShader) return;

    // simple immediate-mode: bind shader and draw each submission (no batching yet)
    spriteShader->use();
    int viewLoc = glGetUniformLocation(spriteShader->ID, "view");
    if (viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    int projLoc = glGetUniformLocation(spriteShader->ID, "projection");
    if (projLoc != -1) glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(quadVAO);

    unsigned int currentTex = 0;
    for (const auto &s : submissions)
    {
        if (s.textureID != currentTex)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, s.textureID);
            int texLoc = glGetUniformLocation(spriteShader->ID, "texture1");
            if (texLoc != -1) glUniform1i(texLoc, 0);
            currentTex = s.textureID;
        }

        int modelLoc = glGetUniformLocation(spriteShader->ID, "model");
        if (modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(s.model));

        int uvLoc = glGetUniformLocation(spriteShader->ID, "uvScale");
        int uvOffLoc = glGetUniformLocation(spriteShader->ID, "uvOffset");
        if (uvLoc != -1) glUniform2f(uvLoc, s.uv.x, s.uv.y);
        if (uvOffLoc != -1) glUniform2f(uvOffLoc, s.uv.z, s.uv.w);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindVertexArray(0);
    submissions.clear();
}

