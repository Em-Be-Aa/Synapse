#include "Character.h"
#include "glm/glm.hpp"
#include "../Shader/Shader.h"
#include "../Statistics/StatManager.h"

Character::Character(const char* imagePath, Shader* Shader) : characterSprite(imagePath)
{
    characterShader = Shader; 

    UpdateAnim(IDLE);
}

void Character::UpdateAnim(Anim_Mode Mode)
{
    currentAnim = Mode;

    auto It = animMontage.find(currentAnim);
    if (It != animMontage.end())
    {
        Anim_Clip& currentMontage = It->second;
        currentSpritesheet = currentMontage.spriteSheet;
        characterSprite.spriteAnimator.UpdateUV(currentMontage.imageTiles);
    }

    if (currentSpritesheet == nullptr)
    {
        std::cout << "Current Sprite Sheet is Null" << std::endl;
        return;
    }
}


void Character::Tick(double deltaTime)
{
    movementSpeed = 1.0 * deltaTime;

    if (deltaTime != 0)
    {
        Velocity = (Position - previousPosition) / glm::vec1(deltaTime);
        Speed = glm::length(Velocity);
        previousPosition = Position;

        if (Speed == 0 && currentAnim != IDLE)
        {
            UpdateAnim(IDLE);
        }
        else if(Speed != 0 && currentAnim != WALK)
        {
            UpdateAnim(WALK);
        }
    }

    characterShader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    int modelLoc = glGetUniformLocation(characterShader->ID, "model");
    int uvScaleLoc = glGetUniformLocation(characterShader->ID, "uvScale");
    int uvOffsetLoc = glGetUniformLocation(characterShader->ID, "uvOffset");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform2f(uvScaleLoc, characterSprite.spriteAnimator.uvScale.x, characterSprite.spriteAnimator.uvScale.y);
    glUniform2f(uvOffsetLoc, characterSprite.spriteAnimator.uvOffset.x, characterSprite.spriteAnimator.uvOffset.y);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentSpritesheet->ID);
    glBindVertexArray(characterSprite.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    StatManager::Get().drawCalls++;
}
