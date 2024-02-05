// Text rendered to the screen

#pragma once

#include "UI/Sprite.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>

class Text : public Sprite {
  private:
    // Text content to be rendered
    std::string text;

    // Font used for rendering the text
    TTF_Font *font;

    void render() override;

  public:
    Text(std::string text, int fontSize, float posX, float posY,
         Window *window);
    void update() override;
};
