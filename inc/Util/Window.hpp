// Holds an SDL2 window and renderer along with methods to render things to
// the screen

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window {
  private:
    // SDL window pointer
    SDL_Window *sdlWindow;

    // SDL renderer pointer
    SDL_Renderer *renderer;

  public:
    Window(const char *title, int width, int height);
    SDL_Renderer *getRenderer();
    SDL_Texture *loadTexture(const char *filePath);
    void clear();
    void display();
    ~Window();
};
