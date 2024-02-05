// A clickable button class

#pragma once

#include "UI/Sprite.hpp"
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <string>

class Button : public Sprite {
  private:
    // Text displayed on the button
    std::string text;

    // Font used for rendering the text
    TTF_Font *font;

    // Function to be called when the button is clicked
    std::function<void()> onClick;

    void render() override;

  public:
    Button(std::string text, int fontSize, float posX, float posY, float width,
           float height, std::function<void()> onClick, Window *window);
    void update() override;
};

