#include "TileManager.h"
#include <glm/ext/matrix_transform.hpp>
#include "Tile.h"
#include <glm/gtc/type_ptr.hpp>

TileManager::TileManager(Shader* Shader)
{
    defaultShader = Shader;

    basicTile = new Tile("Assets/Map/Tiles/Ground_Tile_01_B.png");
    patch1Tile = new Tile("Assets/Map/Blocks/Block_A_02.png");
    //patch2Tile = new Tile("Assets/Map/Blocks/Block_B_02.png");

    backgroundTiles = generatebackgroundTilePositions();
    patchTiles = generatepatchTilePositions();


}
    

void TileManager::Tick()
{


	for (glm::vec2 Translation : backgroundTiles)
	{ 

        defaultShader->use();

        glm::mat4 model = glm::mat4(1.0f)
            ;
        model = glm::translate(model, glm::vec3(Translation, 0.0f));

        int modelLoc = glGetUniformLocation(defaultShader->ID, "model");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, basicTile->DefaultImage->ID);
       
        glBindVertexArray(basicTile->VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);
	}


    for (glm::vec2 Translation : patchTiles)
    {

        defaultShader->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(Translation, 0.0002f));

        int modelLoc = glGetUniformLocation(defaultShader->ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, patch1Tile->DefaultImage->ID);

        glBindVertexArray(patch1Tile->VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }


}
