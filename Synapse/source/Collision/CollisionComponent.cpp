#include "../Managers/CollisionManager.h"
#include "../Managers/StatManager.h"
#include "../Templates/Templates.h"
#include "CollisionComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

// Add visible rectangle for owners....also i dont know but moving moves the boundary before actually moving so when colliding with someone...the boundary moves a bit...

CollisionComponent::CollisionComponent(std::weak_ptr<Actor> Owner) : collisionSprite(std::make_shared<Sprite>("Assets/Map/Tiles/Debugging_Boundary.png"))
{
    owner = Owner;
}

CollisionComponent::CollisionComponent(bool isDamage, float damageAmount) : collisionSprite(std::make_shared<Sprite>("Assets/Map/Tiles/Debugging_Boundary.png"))
{
    isDamageCollidor = isDamage;
    damageCount = damageAmount;
}

CollisionComponent::CollisionComponent(std::weak_ptr<Actor> Owner, bool isDamage, float damageAmount) : collisionSprite(std::make_shared<Sprite>("Assets/Map/Tiles/Debugging_Boundary.png"))
{
    isDamageCollidor = isDamage;
    damageCount = damageAmount;
    owner = Owner;
}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::Init()
{
    RenderComp = SpawnActor<RenderComponent>();

    RenderComp->SetOwner(shared_from_this());
    CollisionManager::GetCollisionManager()->RegisterCollisionComponent(std::static_pointer_cast<CollisionComponent>(shared_from_this()));
}

void CollisionComponent::Update(double deltaTime)
{

    RenderComp->SetIsDisabled(!enableDebug);


    glm::vec2 center = (Box.min + Box.max) * 0.5f;
    glm::vec3 modelPosition = glm::vec3(center, 0); 
    glm::mat4 model = glm::translate(glm::mat4(1.0f), modelPosition);
    model = glm::scale(model, glm::vec3(BoxSize.x, BoxSize.y, 1.0f));


    RenderComp->defaultQuad.model = model;
    RenderComp->defaultQuad.textureID = collisionSprite->GetDefaultImage().lock()->ID;
    RenderComp->defaultQuad.uvScaleOffset = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

}