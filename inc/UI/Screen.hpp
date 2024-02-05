
// Screen class representing specific collections of sprites to display at a
// given time

#pragma once

#include "UI/Sprite.hpp"
#include <vector>

class Screen {
  private:
    // Pointer to a vector of Sprite objects representing sprites to display on
    // the screen
    std::vector<Sprite *> *sprites;

    void render();

  public:
    Screen(std::vector<Sprite *> *sprites);
    void update();
};
