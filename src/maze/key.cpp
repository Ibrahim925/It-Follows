// Collectable keys scattered around the map

#include "Maze/Key.hpp"
#include <vector>

/**
 * Constructor for the Key class.
 *
 * @param index The index of the key.
 * @param posX The x-coordinate of the key.
 * @param posY The y-coordinate of the key.
 * @param player A pointer to the Player object associated with the key.
 * @param keys A pointer to a vector of Key objects representing all keys in the
 * maze.
 * @param window The Window object associated with the key.
 */
Key::Key(int index, float posX, float posY, Player *player,
         std::vector<Key> *keys, Window *window)
    : Entity(posX, posY, 16, 16, 0, 0, texture, window), index(index),
      player(player), keys(keys) {
    // Load the key texture
    this->texture = window->loadTexture("res/img/Key.png");
}

/**
 * Updates the key by checking for collision with the player and updating the
 * state accordingly.
 */
void Key::update() {
    // Check for collision with the player
    if (this->isCollidingWith(this->player)) {
        // Remove the key from the vector and update indices
        (*this->keys).erase(this->keys->begin() + this->index);
        for (int i = this->index; i < this->keys->size(); i++) {
            (*this->keys)[i].index = i;
        }
        // Increment the player's key count
        this->player->setNumKeys(this->player->getNumKeys() + 1);
    }

    this->render();
}
