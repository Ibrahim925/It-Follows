// A clickable button class

#include "UI/Button.hpp"
#include "UI/Sprite.hpp"
#include "Util/Window.hpp"
#include <SDL2/SDL_events.h>
#include <string>

/**
 * Constructor for the Button class.
 *
 * @param text The string content of the button.
 * @param fontSize The font size for rendering the text on the button.
 * @param posX The x-coordinate of the button's position.
 * @param posY The y-coordinate of the button's position.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param onClick The callback function to be executed when the button is
 * clicked.
 * @param window The Window object associated with the button.
 */
Button::Button(std::string text, int fontSize, float posX, float posY,
               float width, float height, std::function<void()> onClick,
               Window *window)
    : Sprite(posX, posY, width, height, nullptr, window), text(text),
      font(nullptr), onClick(onClick) {
    // Open the specified font file and set font size
    this->font = TTF_OpenFont("res/fonts/PressStart2P-Regular.ttf", fontSize);
}

/**
 * Renders the button on the associated window's renderer.
 */
void Button::render() {
    SDL_Renderer *renderer = this->window->getRenderer();

    // Render the red background
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_Rect backgroundRect = {(int)this->position.x, (int)this->position.y,
                               (int)this->dimensions.x,
                               (int)this->dimensions.y};
    SDL_RenderFillRect(renderer, &backgroundRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color

    // Render text
    SDL_Color White = {255, 255, 255};
    SDL_Surface *surfaceMessage =
        TTF_RenderText_Solid(this->font, this->text.c_str(), White);

    SDL_Texture *Message =
        SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; // create a rect

    // Dynamically calculate the width and height of the rect based on the text
    // size
    SDL_QueryTexture(Message, NULL, NULL, &Message_rect.w, &Message_rect.h);

    // Calculate the centered position for the text
    Message_rect.x =
        this->position.x + (this->dimensions.x - Message_rect.w) / 2;
    Message_rect.y =
        this->position.y + (this->dimensions.y - Message_rect.h) / 2;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // Free the surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

/**
 * Updates the button by rendering it on the associated window's renderer and
 * handling button clicks.
 */
void Button::update() {
    this->render();

    static bool buttonClicked =
        false; // Static flag to track button click within a frame

    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
        // Left mouse button is not pressed, reset the flag
        buttonClicked = false;
    } else if (!buttonClicked && this->isCollidingWith(mouseX, mouseY, 5, 5)) {
        // Left mouse button is pressed, and the button is not clicked yet in
        // this frame
        this->onClick();
        buttonClicked =
            true; // Set the flag to prevent multiple clicks in the same frame
    }
}
