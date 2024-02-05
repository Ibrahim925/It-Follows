// Screen class representing specific collections of sprites to display at a
// given time

#include "UI/Screen.hpp"
#include "UI/Sprite.hpp"
#include <iostream>
#include <vector>

/**
 * Constructor for the Screen class.
 *
 * @param sprites A pointer to a vector of Sprite pointers, representing the
 * sprites on the screen.
 */
Screen::Screen(std::vector<Sprite *> *sprites) : sprites(sprites) {}

/**
 * Renders all the sprites on the screen by calling their update method.
 */
void Screen::render() {
    // Iterate through each sprite in the sprites vector and call its update
    // method
    for (Sprite *sprite : *this->sprites) {
        sprite->update();
    }
}

/**
 * Updates the screen by calling the render method.
 */
void Screen::update() { this->render(); }
