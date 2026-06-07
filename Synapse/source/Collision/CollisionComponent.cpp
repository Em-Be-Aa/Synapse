#include "CollisionComponent.h"
#include "../Managers/CollisionManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Managers/StatManager.h"
#include <glm/gtc/type_ptr.hpp>

// Add visible rectangle for owners.
CollisionComponent::CollisionComponent(Actor* ownerActor) : collisionSprite("Assets/Map/Tiles/Boundary.png")
{
	CollisionManager::GetCollisionManager()->RegisterCollisionComponent(this);
    owner = ownerActor;
}

void CollisionComponent::Tick(double deltaTime)
{
    glm::vec2 center = (Box.min + Box.max) * 0.5f;
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(center, owner->Position.z));
    model = glm::scale(model, glm::vec3(BoxSize.x, BoxSize.y, 1.0f));

    RenderComp.model = model;
    RenderComp.textureID = collisionSprite.DefaultImage->ID;
    RenderComp.uvScaleOffset = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

}