#include "../Managers/CollisionManager.h"
#include "../Managers/StatManager.h"
#include "CollisionComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Add visible rectangle for owners....also i dont know but moving moves the boundary before actually moving so when colliding with someone...the boundary moves a bit...

CollisionComponent::CollisionComponent() : collisionSprite("Assets/Map/Tiles/Debugging_Boundary.png")
{
    CollisionManager::GetCollisionManager()->RegisterCollisionComponent(this);
}

CollisionComponent::CollisionComponent(bool isDamage) : collisionSprite("Assets/Map/Tiles/Debugging_Boundary.png")
{
	CollisionManager::GetCollisionManager()->RegisterCollisionComponent(this);

    isDamageCollidor = isDamage;
}

CollisionComponent::CollisionComponent(Actor* Owner, bool isDamage) : collisionSprite("Assets/Map/Tiles/Debugging_Boundary.png")
{
    CollisionManager::GetCollisionManager()->RegisterCollisionComponent(this);

    isDamageCollidor = isDamage;

    owner = Owner;
}

CollisionComponent::~CollisionComponent()
{
    CollisionManager::GetCollisionManager()->UnregisterCollisionComponent(this);
}

void CollisionComponent::Update(double deltaTime)
{
    glm::vec2 center = (Box.min + Box.max) * 0.5f;
    glm::vec3 modelPosition = glm::vec3(center, 0); 
    glm::mat4 model = glm::translate(glm::mat4(1.0f), modelPosition);
    model = glm::scale(model, glm::vec3(BoxSize.x, BoxSize.y, 1.0f));


    RenderComp.model = model;
    RenderComp.textureID = collisionSprite.DefaultImage->ID;
    RenderComp.uvScaleOffset = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

}