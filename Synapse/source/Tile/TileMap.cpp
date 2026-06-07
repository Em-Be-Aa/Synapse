#include "TileMap.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Managers/StatManager.h"
#include "../Shader/Renderer2D.h"

TileMap::TileMap()
{

    basicTile = new Sprite("Assets/Map/Tiles/Mixed_Tile.png");

    backgroundTiles = generatebackgroundTilePositions();
    patchTiles = generatepatchTilePositions();
}
    

void TileMap::Tick(double deltaTime)
{

    // use instanced draw for this....900 draw calls are too much..also state chages like binds should be outside the loop so they dont run in a for loop...read about frustum culling and batching

	for (glm::vec2 Translation : backgroundTiles)
	{ 

        // Submit tile to Renderer2D instead of issuing GL calls here
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(Translation, 0.0f));
        glm::vec4 uv = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
        Renderer2D::Submit(basicTile->DefaultImage->ID, model, uv);

	}
}
