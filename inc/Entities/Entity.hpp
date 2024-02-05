// Base entity that represents all in-game objects

#pragma once

#include "UI/Sprite.hpp"
#include "Util/Vector2f.hpp"
#include "Util/Window.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

class Entity : public Sprite {
  protected:
    // Member variable to store the velocity of the entity
    Vector2f velocity;

    virtual void move(); // Can be overridden by subclasses

  public:
    Entity(float posX, float posY, float width, float height, float velX,
           float velY, SDL_Texture *texture, Window *window);

    Vector2f *getVelocity();
};
