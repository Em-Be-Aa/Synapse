#include "../Enums&Structs/GameTypes.h"
#include "../Managers/RenderManager.h"
#include "Renderer2D.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>



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

    glGenTextures(1, &whiteTextureID);
    glBindTexture(GL_TEXTURE_2D, whiteTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);

    // create shader
    spriteShader = new Shader(spriteVertexShaderPath, spriteFragmentShaderPath);
}

void Renderer2D::Shutdown()
{
    if (spriteShader) { delete spriteShader; spriteShader = nullptr; }
    if (quadVBO) { glDeleteBuffers(1, &quadVBO); quadVBO = 0; }
    if (quadVAO) { glDeleteVertexArrays(1, &quadVAO); quadVAO = 0; }
}

void Renderer2D::BeginScene(const glm::mat4& worldView, const glm::mat4& worldProjection, const glm::mat4& screenView, const glm::mat4& screenProjection)
{
    worldViewMatrix = worldView;
    worldProjectionMatrix = worldProjection;
    screenViewMatrix = screenView;
    screenProjectionMatrix = screenProjection;

    worldSubmissions.clear();
    screenSubmissions.clear();
}

void Renderer2D::Submit(const RenderComponent& rc)
{
    Submission s;
    s.textureID = rc.textureID;
    s.model = rc.model;
    s.uv = rc.uvScaleOffset;
    s.tint = rc.tint;
    s.layer = rc.layer;
    s.textureXFlip = rc.textureXFlip;
    s.space = rc.space;

    if (s.space == RenderSpace::World)
    {
        worldSubmissions.push_back(s);
    }
    else
    {
        screenSubmissions.push_back(s);
    }
}

void Renderer2D::Submit(unsigned int textureID, const glm::mat4& model, const glm::vec4& uvScaleOffset, const RenderSpace space)
{
    Submission s;
    s.textureID = textureID;
    s.model = model;
    s.uv = uvScaleOffset;
    s.tint = glm::vec4(1.0f);
    s.layer = 0;
    s.space = space;

    if (s.space == RenderSpace::World)
    {
        worldSubmissions.push_back(s);
    }
    else
    {
        screenSubmissions.push_back(s);
    }
}

void Renderer2D::DrawSubmissions(const std::vector<Submission>& subs, unsigned int& currentTex)
{
    for (const auto& s : subs)
    {
        if (s.textureID != currentTex)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, s.textureID);
            int texLoc = glGetUniformLocation(spriteShader->ID, "texture1");
            if (texLoc != -1) glUniform1i(texLoc, 0);
            currentTex = s.textureID;
        }

        int tintLoc = glGetUniformLocation(spriteShader->ID, "tint");
        if (tintLoc != -1) glUniform4f(tintLoc, s.tint.x, s.tint.y, s.tint.z, s.tint.w);

        int modelLoc = glGetUniformLocation(spriteShader->ID, "model");
        if (modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(s.model));

        int uvLoc = glGetUniformLocation(spriteShader->ID, "uvScale");
        int uvOffLoc = glGetUniformLocation(spriteShader->ID, "uvOffset");
        int xFlip = glGetUniformLocation(spriteShader->ID, "xFlip");
        if (uvLoc != -1) glUniform2f(uvLoc, s.uv.x, s.uv.y);
        if (uvOffLoc != -1) glUniform2f(uvOffLoc, s.uv.z, s.uv.w);
        if (xFlip != -1) glUniform1i(xFlip, s.textureXFlip);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void Renderer2D::EndScene()
{
    Flush();
}

void Renderer2D::Flush()
{
    if (!spriteShader) return;

    spriteShader->use();
    glBindVertexArray(quadVAO);
    unsigned int currentTex = 0;

    int viewLoc = glGetUniformLocation(spriteShader->ID, "view");
    if (viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(worldViewMatrix));
    int projLoc = glGetUniformLocation(spriteShader->ID, "projection");
    if (projLoc != -1) glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(worldProjectionMatrix));

    DrawSubmissions(worldSubmissions, currentTex);


    viewLoc = glGetUniformLocation(spriteShader->ID, "view");
    if (viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(screenViewMatrix));
    projLoc = glGetUniformLocation(spriteShader->ID, "projection");
    if (projLoc != -1) glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(screenProjectionMatrix));

    DrawSubmissions(screenSubmissions, currentTex);

    glBindVertexArray(0);
    worldSubmissions.clear();
    screenSubmissions.clear();
}

