// Defines the Game class for managing game logic, screens, and graphics.

#include "Game/Game.hpp"
#include "Entities/Entity.hpp"
#include "Game/Level.hpp"
#include "UI/Button.hpp"
#include "UI/Screen.hpp"
#include "UI/Sprite.hpp"
#include "UI/Text.hpp"
#include "Util/Constants.hpp"
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <iostream>
#include <string>

/**
 * Constructor for the Game class.
 * @param name The name of the game window.
 * @param fps The frames per second for the game.
 */
Game::Game(const char *name, unsigned int fps)
    : running(false), frameDelay(1000 / fps), inGame(false),
      window(Window(name, MAP_SIZE * 16, MAP_SIZE * 16)),
      currentScreen(nullptr), currentLevel(nullptr) {}

/**
 * Initialize the game, including SDL and game screens.
 */
void Game::init() {
    initSdl(); // Initialize SDL

    this->running = true; // Set the game to running state

    // Define button dimensions
    float buttonWidth = 200;
    float buttonHeight = 80;

    // Title screen
    auto onGoToLevelButtonClick = [this]() {
        this->currentScreen = screens["Levels"];
    };
    Text title("IT FOLLOWS", 25, MAP_PIXEL_SIZE / 2, (MAP_PIXEL_SIZE / 5),
               &this->window);
    Button goToLevelsButton(
        "Levels", 15, (MAP_PIXEL_SIZE / 2) - (buttonWidth / 2),
        (MAP_PIXEL_SIZE / 2) - (buttonHeight / 2), buttonWidth, buttonHeight,
        onGoToLevelButtonClick, &this->window);
    std::vector<Sprite *> titleScreenSprites = {&title, &goToLevelsButton};
    Screen titleScreen(&titleScreenSprites);
    screens["Title"] = &titleScreen;

    // Win screen
    auto onReturnToTitleClick = [this]() {
        this->currentScreen = screens["Title"];
    };
    Text winText("You escaped!", 25, (MAP_PIXEL_SIZE / 2), (MAP_PIXEL_SIZE / 5),
                 &this->window);
    Button goToTitleButton("Back", 15, (MAP_PIXEL_SIZE / 2) - (buttonWidth / 2),
                           (MAP_PIXEL_SIZE / 2) - (buttonHeight / 2),
                           buttonWidth, buttonHeight, onReturnToTitleClick,
                           &this->window);
    std::vector<Sprite *> winScreenSprites = {&goToTitleButton, &winText};
    Screen winScreen(&winScreenSprites);
    screens["Win"] = &winScreen;

    // Lose screen
    Text loseText("It got you :)", 25, (MAP_PIXEL_SIZE / 2),
                  (MAP_PIXEL_SIZE / 5), &this->window);
    std::vector<Sprite *> loseScreenSprites = {&goToTitleButton, &loseText};
    Screen loseScreen(&loseScreenSprites);
    screens["Lose"] = &loseScreen;

    // Level screen
    float gap = 15.0f;
    float columnHeight = NUM_LEVELS * (80 + gap);
    float startY = (MAP_PIXEL_SIZE / 2) - (columnHeight / 2);
    float centerX = (MAP_PIXEL_SIZE / 2) - (buttonWidth / 2);

    std::vector<Sprite *> levels;

    // Create buttons for each level
    for (int i = 1; i <= NUM_LEVELS; i++) {
        auto onGoToLevelButtonClick = [i, this]() {
            this->currentScreen = nullptr;
            this->currentLevel = nullptr;
            this->inGame = true;
            this->currentLevelIndex = i;
        };

        float buttonY = startY + (i - 1) * (buttonHeight + gap);

        std::string levelText = "Level " + std::to_string(i);

        Button *levelButton =
            new Button(levelText, 12, centerX, buttonY, buttonWidth,
                       buttonHeight, onGoToLevelButtonClick, &this->window);

        levels.push_back(levelButton);
    }

    Screen levelsScreen(&levels);
    this->screens["Levels"] = &levelsScreen;

    this->currentScreen = this->screens["Title"];

    Uint32 frameStart;
    int frameTime;

    // Main game loop
    while (this->running) {
        frameStart = SDL_GetTicks();

        handleEvents(); // Handle SDL events
        update();       // Update game state
        render();       // Render the game

        frameTime = SDL_GetTicks() - frameStart;

        // Cap the frame rate
        if (this->frameDelay > frameTime) {
            SDL_Delay(this->frameDelay - frameTime);
        }
    }
}

/**
 * Initialize SDL, SDL Image, and SDL TTF.
 */
void Game::initSdl() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
                  << "\n";

    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
                  << "\n";

    if (TTF_Init() != 0) {
        std::cout << "TTF_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
                  << "\n";
    }
}

/**
 * Handle SDL events such as quitting the game or returning to the title
 * screen.
 */
void Game::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: // Window closed
            this->running = false;
            break;
        }
    }
}

/**
 * Update the game state, including screens and levels.
 */
void Game::update() {
    this->window.clear(); // Clear the window

    if (this->inGame) {
        if (this->currentLevel == nullptr) {
            std::string levelPath = "res/levels/level" +
                                    std::to_string(this->currentLevelIndex) +
                                    ".txt";
            this->currentLevel =
                std::make_unique<Level>(levelPath.c_str(), &this->window);
        }

        this->currentLevel->update(); // Update the current level

        // Check win condition
        if (this->currentLevel->getPlayer()->getNumKeys() ==
            this->currentLevel->getNumKeys()) {
            this->currentScreen = this->screens["Win"];
            this->inGame = false;
        }

        // Check lose condition
        if (this->currentLevel->getPlayer()->isCollidingWith(
                this->currentLevel->getFollower())) {
            this->currentScreen = this->screens["Lose"];
            this->inGame = false;
        }
    } else {
        this->currentScreen->update(); // Update the current screen
    }
}

/**
 * Render the game.
 */
void Game::render() {
    this->window.display(); // Display the window
}

/**
 * Destructor for the Game class.
 */
Game::~Game() { SDL_Quit(); }
