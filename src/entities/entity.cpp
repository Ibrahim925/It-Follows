// Base entity that represents all in-game objects

#include "Entities/Entity.hpp"
#include "UI/Sprite.hpp"
#include "Util/Vector2f.hpp"
#include "Util/Window.hpp"
#include <iostream>

/**
 * Constructor for the Entity class.
 *
 * @param posX Initial X-coordinate.
 * @param posY Initial Y-coordinate.
 * @param width Width of the entity.
 * @param height Height of the entity.
 * @param velX Initial X velocity.
 * @param velY Initial Y velocity.
 * @param texture SDL_Texture pointer representing the entity's texture.
 * @param window Pointer to the game window.
 */
Entity::Entity(float posX, float posY, float width, float height, float velX,
               float velY, SDL_Texture *texture, Window *window)
    : Sprite(posX, posY, width, height, texture, window),
      velocity(Vector2f{.x = velX, .y = velY}) {}

/**
 * Move the entity based on its current velocity.
 */
void Entity::move() {
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
}

/**
 * Get the velocity vector of the entity.
 *
 * @return Pointer to the Vector2f representing the velocity.
 */
Vector2f *Entity::getVelocity() { return &this->velocity; }
