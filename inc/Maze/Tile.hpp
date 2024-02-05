// Tile class for spaces and walls on the map

#pragma once

#include "Entities/Entity.hpp"
#include "Util/Window.hpp"

class Tile : public Entity {
  private:
    // Boolean variable indicating whether the tile is a wall
    bool isWall;

  public:
    Tile(float x, float y, bool isWall, Window *window);
    bool getIsWall();
};

