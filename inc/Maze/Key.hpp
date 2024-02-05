// Collectable keys scattered around the map

#pragma once

#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"

class Key : public Entity {
  private:
    // Index representing the key's position in the keys vector
    int index;

    // Pointer to the Player object associated with the key
    Player *player;

    // Pointer to the vector storing all keys in the game
    std::vector<Key> *keys;

  public:
    Key(int index, float posX, float posY, Player *player,
        std::vector<Key> *keys, Window *window);
    void update() override;
};
