// Sprite class representing everything that is rendered to the screen

#include "UI/Sprite.hpp"

/**
 * Constructor for the Sprite class.
 *
 * @param posX The x-coordinate of the sprite's position.
 * @param posY The y-coordinate of the sprite's position.
 * @param width The width of the sprite.
 * @param height The height of the sprite.
 * @param texture The SDL texture for rendering the sprite.
 * @param window The Window object associated with the sprite.
 */
Sprite::Sprite(float posX, float posY, float width, float height,
               SDL_Texture *texture, Window *window)
    : texture(texture), window(window),
      position(Vector2f{.x = posX, .y = posY}),
      dimensions(Vector2f{.x = width, .y = height}) {
    // Initialize the sprite with a default frame size
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 16;
    currentFrame.h = 16;
}

/**
 * Renders the sprite on the associated window's renderer.
 */
void Sprite::render() {
    // Get the SDL renderer from the associated window
    SDL_Renderer *renderer = this->window->getRenderer();

    // Set up source and destination rectangles for rendering

    // src: holds the position and dimensions of the texture within the texture
    // file
    SDL_Rect src;
    src.x = this->currentFrame.x;
    src.y = this->currentFrame.y;
    src.w = this->currentFrame.w;
    src.h = this->currentFrame.h;

    // dst: holds the position and dimensions where the texture will be rendered
    // on the screen
    SDL_Rect dst;
    dst.x = this->position.x;
    dst.y = this->position.y;
    dst.w = this->dimensions.x;
    dst.h = this->dimensions.y;

    // Copy the texture to the renderer with the specified rectangles
    SDL_RenderCopy(renderer, this->texture, &src, &dst);
}

/**
 * Getter function to retrieve the SDL texture of the sprite.
 *
 * @return The SDL texture.
 */
SDL_Texture *Sprite::getTexture() { return this->texture; }

/**
 * Getter function to retrieve the position of the sprite.
 *
 * @return A pointer to the Vector2f representing the position.
 */
Vector2f *Sprite::getPosition() { return &this->position; }

/**
 * Getter function to retrieve the dimensions of the sprite.
 *
 * @return A pointer to the Vector2f representing the dimensions.
 */
Vector2f *Sprite::getDimensions() { return &this->dimensions; }

/**
 * Getter function to retrieve the current frame of the sprite.
 *
 * @return A pointer to the SDL_Rect representing the current frame.
 */
SDL_Rect *Sprite::getCurrentFrame() { return &this->currentFrame; }

/**
 * Checks if the sprite is colliding with another sprite.
 *
 * @param entity The other sprite to check for collision.
 * @return True if a collision is detected, false otherwise.
 */
bool Sprite::isCollidingWith(Sprite *entity) {
    // Calculate the boundaries of both sprites
    float leftA = this->position.x;
    float rightA = this->position.x + this->dimensions.x;
    float topA = this->position.y;
    float bottomA = this->position.y + this->dimensions.y;

    float leftB = entity->position.x;
    float rightB = entity->position.x + entity->dimensions.x;
    float topB = entity->position.y;
    float bottomB = entity->position.y + entity->dimensions.y;

    // Check for collision
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB ||
        leftA >= rightB) {
        return false; // No collision
    }

    return true; // Collision detected
}

/**
 * Checks if the sprite is colliding with a specified rectangle.
 *
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @return True if a collision is detected, false otherwise.
 */
bool Sprite::isCollidingWith(float x, float y, float width, float height) {
    // Calculate the boundaries of both the sprite and the specified rectangle
    float leftA = this->position.x;
    float rightA = this->position.x + this->dimensions.x;
    float topA = this->position.y;
    float bottomA = this->position.y + this->dimensions.y;

    float leftB = x;
    float rightB = x + width;
    float topB = y;
    float bottomB = y + height;

    // Check for collision
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB ||
        leftA >= rightB) {
        return false; // No collision
    }

    return true; // Collision detected
}

/**
 * Updates the sprite by rendering it on the associated window's renderer.
 */
void Sprite::update() { this->render(); }
