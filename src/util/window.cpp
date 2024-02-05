// Holds an SDL2 window and renderer along with methods to render things to
// the screen

#include "Util/Window.hpp"
#include <iostream>

/**
 * The Window class constructor
 */
Window::Window(const char *title, int width, int height)
    : sdlWindow(NULL), renderer(NULL) {
    /**
     * Creates an SDL window with the specified title, width, and height.
     *
     * @param title The title of the window.
     * @param width The width of the window.
     * @param height The height of the window.
     */

    this->sdlWindow =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         width, height, SDL_WINDOW_SHOWN);

    // Check if the window creation was successful
    if (this->sdlWindow == NULL) {
        std::cout << "WINDOW FAILED TO INIT. SDL_ERROR: " << SDL_GetError()
                  << "\n";
    }

    /**
     * Creates an SDL renderer for rendering graphics in the window.
     *
     * @param sdlWindow The SDL window to associate the renderer with.
     * @param index The index of the rendering driver to use, or -1 for the
     * first one supporting the requested flags.
     * @param flags The rendering options; SDL_RENDERER_ACCELERATED for hardware
     * acceleration.
     */
    this->renderer =
        SDL_CreateRenderer(this->sdlWindow, -1, SDL_RENDERER_ACCELERATED);

    // Check if the renderer creation was successful
    if (this->renderer == NULL) {
        std::cout << "RENDERER FAILED TO INIT. SDL_ERROR: " << SDL_GetError()
                  << "\n";
    }
}

/**
 * Gets the SDL renderer associated with the window.
 *
 * @return The SDL renderer.
 */
SDL_Renderer *Window::getRenderer() { return this->renderer; }

/**
 * Loads an SDL texture from a specified file path.
 *
 * @param filePath The path to the image file.
 * @return The loaded SDL texture.
 */
SDL_Texture *Window::loadTexture(const char *filePath) {
    SDL_Texture *texture = NULL;

    /**
     * Loads an SDL texture from the specified file path.
     *
     * @param renderer The SDL renderer to use for texture creation.
     * @param filePath The path to the image file.
     * @return The loaded SDL texture.
     */
    texture = IMG_LoadTexture(this->renderer, filePath);

    // Check if the texture loading was successful
    if (texture == NULL) {
        std::cout << "FAILED TO LOAD TEXTURE. SDL_ERROR: " << SDL_GetError()
                  << "\n";
    }

    return texture;
}

/**
 * Clears the renderer, preparing it for the next frame.
 */
void Window::clear() { SDL_RenderClear(this->renderer); }

/**
 * Presents the renderer, displaying the rendered content.
 */
void Window::display() { SDL_RenderPresent(this->renderer); }

/**
 * Destructor for the Window class, responsible for cleaning up SDL resources.
 */
Window::~Window() {
    SDL_DestroyWindow(this->sdlWindow);
    SDL_DestroyRenderer(this->renderer);
}
