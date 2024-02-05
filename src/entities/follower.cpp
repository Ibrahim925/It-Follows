// Code for Follower movement and actions

#include "Entities/Follower.hpp"
#include "Entities/WallBoundEntity.hpp"
#include "Util/Constants.hpp"
#include "Util/Pathfinding.hpp"
#include <iostream>

/**
 * Constructor for Follower class with a Window pointer.
 *
 * @param window Pointer to the game window.
 */
Follower::Follower(Window *window)
    : WallBoundEntity(0, 0, 0, 0, 0, 0, NULL, NULL, window) {
    // Load follower texture
    this->texture = window->loadTexture("res/img/Steven.png");
}

/**
 * Constructor for Follower class with specific parameters.
 *
 * @param posX Initial X-coordinate.
 * @param posY Initial Y-coordinate.
 * @param velX Initial X velocity.
 * @param velY Initial Y velocity.
 * @param map Pointer to the game map.
 * @param player Pointer to the player object.
 * @param window Pointer to the game window.
 */
Follower::Follower(float posX, float posY, float velX, float velY,
                   std::vector<std::vector<Tile>> *map, Player *player,
                   Window *window)
    : WallBoundEntity(posX, posY, 16, 16, velX, velY, map, NULL, window),
      player(player) {
    // Load follower texture
    this->texture = window->loadTexture("res/img/Steven.png");
}

/**
 * Update the follower's velocity based on player's position using
 * pathfinding.
 */
void Follower::updateVelocity() {
    this->velocity.x = 0;
    this->velocity.y = 0;

    // Calculate current follower position on the map. Get the tile it is
    // currently on
    int followerX = round(this->position.x / TILE_SIZE);
    int followerY = round(this->position.y / TILE_SIZE);
    Tile *followerTile = &(*this->map)[followerY][followerX];

    // Calculate current follower position on the map. Get the tile it is
    // currently on
    int playerX = round(this->player->getPosition()->x / TILE_SIZE);
    int playerY = round(this->player->getPosition()->y / TILE_SIZE);
    Tile *playerTile = &(*this->map)[playerY][playerX];

    // Handle the case where rounding errors cause the playerTile to be an
    // adjacent wall
    if (playerTile->getIsWall()) {
        int directionsX[] = {0, 0, -1, 1};
        int directionsY[] = {-1, 1, 0, 0};

        // Search adjacent cells
        for (int i = 0; i < 4; ++i) {
            // Move one space either up, down, left, or right
            int newX = playerX + directionsX[i];
            int newY = playerY + directionsY[i];

            // Check if the new coordinates are within the map boundaries
            if (newX >= 0 && newX < MAP_SIZE && newY >= 0 && newY < MAP_SIZE) {
                Tile *adjacentTile = &(*this->map)[newY][newX];

                // Check if the adjacent tile is not a wall
                if (!adjacentTile->getIsWall()) {
                    playerTile = adjacentTile;
                }
            }
        }
    }

    // Find the next tile in the path using pathfinding
    Tile *nextTile =
        findPath(followerTile, playerTile, this->map)[followerTile];

    if (nextTile == nullptr)
        return;

    // Update follower velocity to be in the direction of the next tile
    if (nextTile->getPosition()->x / 16 > this->position.x / 16) {
        this->velocity.x = FOLLOWER_BASE_VELOCITY;
    } else if (nextTile->getPosition()->x / 16 < this->position.x / 16) {
        this->velocity.x = -FOLLOWER_BASE_VELOCITY;
    }

    if (nextTile->getPosition()->y / 16 > this->position.y / 16) {
        this->velocity.y = FOLLOWER_BASE_VELOCITY;
    } else if (nextTile->getPosition()->y / 16 < this->position.y / 16) {
        this->velocity.y = -FOLLOWER_BASE_VELOCITY;
    }
}

/**
 * Update the follower's position and render it.
 */
void Follower::update() {
    // Update follower velocity based on player's position
    this->updateVelocity();

    // Move the follower
    this->move();

    // Render the follower
    this->render();
}
