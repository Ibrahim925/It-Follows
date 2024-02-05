// Pathfinding implementation with A*

#include "Maze/Tile.hpp"
#include "Util/Vector2f.hpp"
#include <map>
#include <vector>

int heuristic(Tile *current, Tile *goal);

std::unordered_map<Tile *, Tile *>
findPath(Tile *start, Tile *goal, std::vector<std::vector<Tile>> *map);
