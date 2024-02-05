// Code for Follower movement and actions

#pragma once

#include "Entities/Player.hpp"
#include "Entities/WallBoundEntity.hpp"

class Follower : public WallBoundEntity {
  private:
    // Pointer to the Player object that the Follower is following
    Player *player;

    void updateVelocity();

  public:
    Follower(Window *window);
    Follower(float posX, float posY, float velX, float velY,
             std::vector<std::vector<Tile>> *map, Player *player,
             Window *window);

    void update() override;
};
