// Code for Player movement and actions

#pragma once

#include "Entities/Entity.hpp"
#include "Entities/WallBoundEntity.hpp"
#include <vector>

class Player : public WallBoundEntity {
  private:
    // Member variable to store the number of keys the player has
    int numKeys;

  public:
    Player(Window *window);
    Player(float posX, float posY, float velX, float velY,
           std::vector<std::vector<Tile>> *map, Window *window);

    void update() override;

    int getNumKeys();

    void setNumKeys(int numKeys);
};
