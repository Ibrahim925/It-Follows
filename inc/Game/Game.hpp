// Defines the Game class for managing game logic, screens, and graphics.

#pragma once

#include "Game/Level.hpp"
#include "UI/Screen.hpp"
#include "Util/Window.hpp"
#include <map>
#include <string>
#include <vector>

class Game {
  private:
    // Member variable to track the running state of the game
    bool running;

    // Constant representing the frame delay for controlling the game's frame
    // rate
    const int frameDelay;

    // Boolean variable to indicate whether the player is in the main game
    bool inGame;

    // Window object for handling graphics
    Window window;

    // Pointer to the current screen being displayed
    Screen *currentScreen;

    // Map to store different screens using their unique names
    std::map<std::string, Screen *> screens;

    // Unique pointer to the current level being played
    std::unique_ptr<Level> currentLevel;

    // Index representing the current level being played
    int currentLevelIndex;

    void initSdl();
    void handleEvents();
    void update();
    void render();

  public:
    Game(const char *name, unsigned int fps);
    void init();
    ~Game();
};
