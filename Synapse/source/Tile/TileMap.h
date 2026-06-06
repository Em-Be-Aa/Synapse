#pragma once

#include "../Actor/Actor.h"
#include "glm/glm.hpp"
#include "../Shader/Shader.h"
#include "Tile.h"

class TileMap : public Actor
{

public:

    TileMap(Shader* Shader);
	void Tick(double deltaTime);



    std::vector<glm::vec2> backgroundTiles;
    std::vector<glm::vec2> patchTiles;


private:

    Shader* defaultShader;
    Tile* basicTile;
    Tile* patch1Tile;
    Tile* patch2Tile;

    std::vector<glm::vec2> generatebackgroundTilePositions()
    {

        std::vector<glm::vec2> translations;

        // Grid dimensions
        int columns = 30;
        int rows = 30;

        // Size of the tile in your OpenGL world space (e.g., if your quad is 1.0 x 1.0)
        float tileSize = 1.0f;

        // Optional: Add a tiny gap to visually see individual tiles during testing
        float padding = 0.0f;

        for (int y = -rows / 2; y < rows / 2; y++) {
            for (int x = -columns / 2; x < columns / 2; x++) {

                glm::vec2 pos;

                // Calculate the world position based on grid index
                pos.x = (float)x * (tileSize + padding);

                // OpenGL's Y-axis usually points UP. 
                // If you want top-down drawing starting from top-left, you might need a negative Y.
                pos.y = -(float)y * (tileSize + padding);

                translations.push_back(pos);
            }
        }

        return translations;
    }
    std::vector<glm::vec2> generatepatchTilePositions()
    {

        std::vector<glm::vec2> translations;

        // Grid dimensions
        int columns = 30;
        int rows = 30;

        // Size of the tile in your OpenGL world space (e.g., if your quad is 1.0 x 1.0)
        float tileSize = 1.0f;

        // Optional: Add a tiny gap to visually see individual tiles during testing
        float padding = 0.0f;

        int patches = (rows * columns) / 50;

        for (int patch = 0; patch < patches; patch++)
        {

            int randomRow = rand() % rows / 2;
            if (rand() % 2 == 0) randomRow = -randomRow;
            int randomColumn = rand() % columns / 2;
            if (rand() % 2 == 0) randomColumn = -randomColumn;
            glm::vec2 pos = { randomRow, randomColumn };

            translations.push_back(pos);

        }

        return translations;
    }


};

