// Code for Player movement and actions

#include "Entities/Player.hpp"
#include "Entities/WallBoundEntity.hpp"
#include "Game/Game.hpp"
#include "Util/Constants.hpp"
#include "Util/Window.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * Constructor for Player class with a Window pointer.
 *
 * @param window Pointer to the game window.
 */
Player::Player(Window *window)
    : WallBoundEntity(0, 0, 0, 0, 0, 0, NULL, NULL, window) {
    // Load player texture
    this->texture = window->loadTexture("res/img/MapPlayer16.png");
}

/**
 * Constructor for Player class with specific parameters.
 *
 * @param posX Initial X-coordinate.
 * @param posY Initial Y-coordinate.
 * @param velX Initial X velocity.
 * @param velY Initial Y velocity.
 * @param map Pointer to the game map.
 * @param window Pointer to the game window.
 */
Player::Player(float posX, float posY, float velX, float velY,
               std::vector<std::vector<Tile>> *map, Window *window)
    : WallBoundEntity(posX, posY, 16, 16, velX, velY, map, NULL, window),
      numKeys(0) {
    // Load player texture
    this->texture = window->loadTexture("res/img/MapPlayer16.png");
}

/**
 * Updates the player's position and handles keyboard input.
 */
void Player::update() {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    /*
     Calculate the angle in radians based on the player's current frame
     The player texture file is 512 pixels wide. Each frame is 16 pixels wide.
     We can get the angle by multiplying 2pi by the percentage of the texture
     file that has been traversed. We need to get the negative of this since
     the positive direction for angles is counter clockwise, but we need it to
     be clockwise for intuitive rotation
    */
    float theta = -(2 * M_PI) * this->getCurrentFrame()->x / float(512);

    float xVelocity = 0;
    float yVelocity = 0;

    /*
     To calculate xVelocity and yVelocity, we can use trigonometry. Our velocity
     vector has a magnitude PLAYER_BASE_VELOCITY and an angle of theta. Now, all
     we need are the component vectors for x and y. Multiplying the magnitude
     (aka the hypotenuse) by cos(theta) gives us the velocity in the x
     direction. Similarly, multiplying by sin(theta) gives us the velocity in
     the y direction.
    */

    // Move forward on W pressed
    if (keystate[SDL_SCANCODE_W]) {
        xVelocity = PLAYER_BASE_VELOCITY * cos(theta);
        yVelocity = PLAYER_BASE_VELOCITY * sin(theta);
    }

    // Move back on S pressed
    if (keystate[SDL_SCANCODE_S]) {
        xVelocity = -PLAYER_BASE_VELOCITY * cos(theta);
        yVelocity = -PLAYER_BASE_VELOCITY * sin(theta);
    }

    // Move right on D pressed
    if (keystate[SDL_SCANCODE_D]) {
        // Get normal angle to move horizontally
        theta += M_PI_2;
        xVelocity = PLAYER_BASE_VELOCITY * cos(theta);
        yVelocity = PLAYER_BASE_VELOCITY * sin(theta);
    }

    // Move left on A pressed
    if (keystate[SDL_SCANCODE_A]) {
        // Get normal angle to move horizontally
        theta -= M_PI_2;
        xVelocity = PLAYER_BASE_VELOCITY * cos(theta);
        yVelocity = PLAYER_BASE_VELOCITY * sin(theta);
    }

    // Rotate right on right arrow pressed
    if (keystate[SDL_SCANCODE_RIGHT]) {
        // Change the current frame from the texture file to rotate the Player
        this->getCurrentFrame()->x -= 16;
        if (this->getCurrentFrame()->x < 0) {
            this->getCurrentFrame()->x = 512 - 16;
        }
    }

    // Rotate left on left arrow pressed
    if (keystate[SDL_SCANCODE_LEFT]) {
        // Change the current frame from the texture file to rotate the Player
        this->getCurrentFrame()->x += 16;
        if (this->getCurrentFrame()->x + 16 > 512) {
            this->getCurrentFrame()->x = 0;
        }
    }

    // Set the player's velocity
    this->velocity.x = xVelocity;
    this->velocity.y = yVelocity;

    // Move the player
    this->move();

    // Render the player
    this->render();
}

/**
 * Get the number of keys the player has collected.
 *
 * @return Number of keys.
 */
int Player::getNumKeys() { return this->numKeys; }

/**
 * Set the number of keys the player has collected.
 *
 * @param numKeys New number of keys.
 */
void Player::setNumKeys(int numKeys) { this->numKeys = numKeys; }
