#include "../Enums&Structs/GameTypes.h"
#include "../Managers/StatManager.h"
#include "../Shader/Renderer2D.h"
#include "TileMap.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TileMap::TileMap()
{

    basicTile = new Sprite("Assets/Map/Tiles/Test.png");

    backgroundTiles = generatebackgroundTilePositions();
    patchTiles = generatepatchTilePositions();
}
    

void TileMap::Update(double deltaTime)
{

 //   // use instanced draw for this....900 draw calls are too much..also state chages like binds should be outside the loop so they dont run in a for loop...read about frustum culling and batching

	//for (glm::vec2 Translation : backgroundTiles)
	//{ 

 //       glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(Translation, 0.0f));
 //       glm::vec4 uv = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
 //       Renderer2D::GetRenderer()->Submit(basicTile->DefaultImage->ID, model, uv, RenderSpace::World);

	//}

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(
        model,
        glm::vec3(10.0f, 5.0f, 1.0f)
    );

    glm::vec4 uv = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

    Renderer2D::GetRenderer()->Submit(
        basicTile->DefaultImage->ID,
        model,
        uv,
        RenderSpace::World
    );
}
