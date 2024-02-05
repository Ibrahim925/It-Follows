// Represents entities constrained by walls in a Tile-based map.

#include "Entities/WallBoundEntity.hpp"
#include "Maze/Tile.hpp"
#include <cstdio>
#include <vector>

/**
 * Constructs a WallBoundEntity with the specified parameters.
 *
 * @param posX      The initial x-coordinate of the entity.
 * @param posY      The initial y-coordinate of the entity.
 * @param width     The width of the entity.
 * @param height    The height of the entity.
 * @param velX      The initial velocity along the x-axis.
 * @param velY      The initial velocity along the y-axis.
 * @param map       A pointer to the Tile-based map.
 * @param texture   The SDL texture for rendering.
 * @param window    The window in which the entity exists.
 */
WallBoundEntity::WallBoundEntity(float posX, float posY, float width,
                                 float height, float velX, float velY,
                                 std::vector<std::vector<Tile>> *map,
                                 SDL_Texture *texture, Window *window)
    : Entity(posX, posY, width, height, velX, velY, texture, window), map(map) {
}

/**
 * Moves the entity, adjusting its position based on collisions with walls.
 */
void WallBoundEntity::move() {
    this->position.x += this->velocity.x;

    for (std::vector<Tile> row : *this->map) {
        for (Tile tile : row) {
            if (tile.getIsWall() && this->isCollidingWith(&tile)) {
                this->position.x -= this->velocity.x;
                this->velocity.x = 0;
                break;
            }
        }
    }

    this->position.y += this->velocity.y;

    for (std::vector<Tile> row : *this->map) {
        for (Tile tile : row) {
            if (tile.getIsWall() && this->isCollidingWith(&tile)) {
                this->position.y -= this->velocity.y;
                this->velocity.y = 0;
                break;
            }
        }
    }
}
