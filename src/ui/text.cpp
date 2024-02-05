// Text rendered to the screen

#include "UI/Text.hpp"

/**
 * Constructor for the Text class.
 *
 * @param text The string content of the text.
 * @param fontSize The font size for rendering the text.
 * @param posX The x-coordinate of the text position.
 * @param posY The y-coordinate of the text position.
 * @param window The Window object associated with the text.
 */
Text::Text(std::string text, int fontSize, float posX, float posY,
           Window *window)
    : Sprite(posX, posY, 0, 0, nullptr, window), text(text), font(nullptr) {
    // Open the specified font file and set font size
    this->font = TTF_OpenFont("res/fonts/PressStart2P-Regular.ttf", fontSize);
}

/**
 * Renders the text on the associated window's renderer.
 */
void Text::render() {
    SDL_Renderer *renderer = this->window->getRenderer();

    // Render text
    SDL_Color White = {255, 255, 255};
    SDL_Surface *surfaceMessage =
        TTF_RenderText_Solid(this->font, this->text.c_str(), White);

    SDL_Texture *Message =
        SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; // Create a rect to hold the text's dimensions and
                           // position for the renderer

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
 * Updates the text by rendering it on the associated window's renderer.
 */
void Text::update() { this->render(); }
