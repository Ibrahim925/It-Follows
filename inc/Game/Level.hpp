// Represents a given level in the game, encapsulating all required elements for
// a level like the map, player, and keys

#pragma once

#include "Entities/Follower.hpp"
#include "Entities/Player.hpp"
#include "Maze/Key.hpp"
#include "Maze/Tile.hpp"
#include "Util/Constants.hpp"
#include "Util/Window.hpp"
#include <vector>

class Level {
  private:
    // 2D vector representing the Tile-based map of the level
    std::vector<std::vector<Tile>> map;

    // Number of keys within the level
    int numKeys;

    // Vector to store Key objects in the level
    std::vector<Key> keys;

    // Player object representing the player character in the level
    Player player;

    // Follower object representing an entity following the player in the level
    Follower follower;

    void render();

  public:
    Level(const char *filePath, Window *window);
    Player *getPlayer();
    Follower *getFollower();
    int getNumKeys();
    void update();
};
