// Sprite class representing everything that is rendered to the screen

#pragma once

#include "Util/Vector2f.hpp"
#include "Util/Window.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class Sprite {
  protected:
    // Pointer to the texture used for rendering the sprite
    SDL_Texture *texture;

    // Pointer to the Window object for rendering
    Window *window;

    // Position of the sprite in 2D space
    Vector2f position;

    // Dimensions (width and height) of the sprite
    Vector2f dimensions;

    // Rectangle representing the current frame of the sprite within the texture
    // file
    SDL_Rect currentFrame;

    virtual void render();

  public:
    Sprite(float posX, float posY, float width, float height,
           SDL_Texture *texture, Window *window);
    SDL_Texture *getTexture();
    Vector2f *getPosition();
    Vector2f *getDimensions();
    SDL_Rect *getCurrentFrame();
    bool isCollidingWith(Sprite *);
    bool isCollidingWith(float x, float y, float width, float height);
    virtual void update();
};
