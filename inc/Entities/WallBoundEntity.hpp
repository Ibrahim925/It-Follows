// Represents entities constrained by walls in a Tile-based map.

#pragma once

#include "Entities/Entity.hpp"
#include "Maze/Tile.hpp"
#include <vector>

class WallBoundEntity : public Entity {
  protected:
    // Pointer to the 2D vector representing the Tile-based map
    std::vector<std::vector<Tile>> *map;

    void move() override;

  public:
    WallBoundEntity(float posX, float posY, float width, float height,
                    float velX, float velY, std::vector<std::vector<Tile>> *map,
                    SDL_Texture *texture, Window *window);
};
