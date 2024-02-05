// Represents a given level in the game, encapsulating all required elements for
// a level like the map, player, and keys

#include "Game/Level.hpp"
#include "Entities/Follower.hpp"
#include "Maze/Key.hpp"
#include "Maze/Tile.hpp"
#include "Util/Constants.hpp"
#include "Util/Window.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Constructor for the Level class
Level::Level(const char *filePath, Window *window)
    : numKeys(0), player(Player(window)), follower(Follower(window)) {

    // Read the contents of the file into a string
    std::ifstream fileStream(filePath);
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    std::string contents = stringStream.str();

    int currRow = 0;
    int currCol = 0;

    // Initialize the map with an empty vector for the first row
    this->map.push_back(std::vector<Tile>());

    // Loop through the contents of the file to create the level map
    for (int i = 0; i < contents.length(); i++) {
        if (contents[i] == ' ') {
            continue; // Skip empty spaces
        } else if (contents[i] == '\n') {
            currRow++;
            currCol = 0;
            this->map.push_back(std::vector<Tile>()); // Move to the next row
            continue;
        }

        // Create Tile and Player objects based on the character in the file
        if (contents[i] == '0') {
            this->map[currRow].push_back(
                Tile(16 * currCol, 16 * currRow, false, window));
        } else if (contents[i] == '1') {
            this->map[currRow].push_back(
                Tile(16 * currCol, 16 * currRow, true, window));
        } else if (contents[i] == 'P') {
            this->player =
                Player(currCol * 16, currRow * 16, 0, 0, &this->map, window);
            this->map[currRow].push_back(
                Tile(16 * currCol, 16 * currRow, false, window));
        }

        currCol++;
    }

    // Reset row and column counters for the second pass
    currRow = 0;
    currCol = 0;

    int keyIndex = 0;

    // Second pass to create keys and follower
    for (int i = 0; i < contents.length(); i++) {
        if (contents[i] == ' ') {
            continue;
        } else if (contents[i] == '\n') {
            currRow++;
            currCol = 0;
            this->map.push_back(std::vector<Tile>());
            continue;
        }

        // Create Key and Follower objects based on the characters in the file
        if (contents[i] == 'K') {
            this->keys.push_back(Key(keyIndex, currCol * 16, currRow * 16,
                                     &this->player, &this->keys, window));
            this->map[currRow].push_back(
                Tile(16 * currCol, 16 * currRow, false, window));
            keyIndex++;
            this->numKeys++;
        } else if (contents[i] == 'F') {
            this->follower = Follower(currCol * 16, currRow * 16, 0, 0,
                                      &this->map, &this->player, window);
            this->map[currRow].push_back(
                Tile(16 * currCol, 16 * currRow, false, window));
        }

        currCol++;
    }
}

// Getter for the player object
Player *Level::getPlayer() { return &this->player; }

// Getter for the follower object
Follower *Level::getFollower() { return &this->follower; }

// Getter for the number of keys in the level
int Level::getNumKeys() { return this->numKeys; }

// Render the level by updating tiles, keys, player, and follower
void Level::render() {
    for (std::vector<Tile> row : this->map) {
        for (Tile tile : row) {
            tile.update();
        }
    }

    for (Key key : this->keys) {
        key.update();
    }

    this->player.update();

    this->follower.update();
}

// Update function for the level (calls the render function)
void Level::update() { this->render(); }
