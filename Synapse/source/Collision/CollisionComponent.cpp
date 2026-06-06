#include "CollisionComponent.h"
#include "../Managers/CollisionManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Managers/StatManager.h"
#include <glm/gtc/type_ptr.hpp>

// Add visible rectangle for owners.
CollisionComponent::CollisionComponent(Shader* shader, const char* imagePath, Actor* ownerActor) : collisionSprite(imagePath)
{
	CollisionManager::GetCollisionManager()->RegisterCollisionComponent(this);
    collisionShader = shader;
    owner = ownerActor;
}

void CollisionComponent::Tick(double deltaTime)
{
    collisionShader->use();

    glm::mat4 model = glm::mat4(1.0f);
    // Position the collision sprite at the center of the collision box
    glm::vec2 center = (Box.min + Box.max) * 0.5f;
    model = glm::translate(model, glm::vec3(center, owner->Position.z));
    // Scale the sprite to match the collision box size
    model = glm::scale(model, glm::vec3(BoxSize.x, BoxSize.y, 1.0f));

    int modelLoc = glGetUniformLocation(collisionShader->ID, "model");
    int uvScaleLoc = glGetUniformLocation(collisionShader->ID, "uvScale");
    int uvOffsetLoc = glGetUniformLocation(collisionShader->ID, "uvOffset");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform2f(uvScaleLoc, 1.0f, 1.0f);
    glUniform2f(uvOffsetLoc, 0.0f, 0.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, collisionSprite.DefaultImage->ID);
    glBindVertexArray(collisionSprite.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    StatManager::Get().drawCalls++;

}