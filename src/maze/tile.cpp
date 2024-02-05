// Tile class for spaces and walls on the map

#include "Maze/Tile.hpp"
#include "Entities/Entity.hpp"
#include "Util/Window.hpp"

/**
 * Constructor for the Tile class.
 *
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param isWall A boolean indicating whether the tile is a wall.
 * @param window The Window object associated with the tile.
 */
Tile::Tile(float x, float y, bool isWall, Window *window)
    : Entity(x, y, 16, 16, 0, 0, NULL, window), isWall(isWall) {
    // Load the texture based on whether the tile is a wall or not
    if (isWall) {
        this->texture = window->loadTexture("res/img/MapWall16.png");
    } else {
        this->texture = window->loadTexture("res/img/MapGridCell.png");
    }
}

/**
 * Getter function to check if the tile is a wall.
 *
 * @return True if the tile is a wall, false otherwise.
 */
bool Tile::getIsWall() { return this->isWall; }
