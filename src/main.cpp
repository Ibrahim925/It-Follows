// Main program entry point
#include "Game/Game.hpp"

int main(int argc, char **argv) {
    // Create a Game object with the title "It Follows" and a frame rate of 60
    // frames per second
    Game game("It Follows", 60);

    // Initialize the game instance, setting up necessary components and
    // resources
    game.init();

    return 0;
}
