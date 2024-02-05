// Dimensions of the map in terms of tiles
#define MAP_SIZE 25

// Dimensions of the tiles in terms of pixels
#define TILE_SIZE 16

// Calculate the total pixel size of the map based on the number of tiles and
// tile size
#define MAP_PIXEL_SIZE (float(MAP_SIZE) * float(TILE_SIZE))

// Define the base velocity for the player's movement
#define PLAYER_BASE_VELOCITY 2

// Define the base velocity for the follower's movement
#define FOLLOWER_BASE_VELOCITY 1

// Define the total number of levels in the game
#define NUM_LEVELS 3
