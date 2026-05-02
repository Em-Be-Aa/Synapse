#include "Player.h"
#include "glm/glm.hpp"
#include "../Shader/Shader.h"

Player::Player(const char* imagePath, Shader* Shader, Camera* Camera) : Sprite(imagePath)
{
    defaultShader = Shader;
    playerCamera = Camera;
}


void Player::Tick()
{
    playerPosition = { playerCamera->cameraPosition.x, playerCamera->cameraPosition.y , 0.0003 };

    defaultShader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, playerPosition);
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));

    int modelLoc = glGetUniformLocation(defaultShader->ID, "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, DefaultImage->ID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
