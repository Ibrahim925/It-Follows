// Pathfinding implementation with A*

#include "Util/Pathfinding.hpp"
#include "Maze/Tile.hpp"
#include "Util/Constants.hpp"
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <vector>

// Direction vectors containing moves to explore all adjacent cells
const int xDirections[] = {1, -1, 0, 0};
const int yDirections[] = {0, 0, -1, 1};

/**
 * Calculates the heuristic value between two tiles for A* pathfinding.
 *
 * @param current The current tile.
 * @param goal The goal tile.
 * @return The heuristic value.
 */
int heuristic(Tile *current, Tile *goal) {
    /*
    Convert between pixel coordinates to tile coordinates. Each square tile
    has a length of 16 pixels. Divide each pixel coordinate by 16 to obtain
    the tile coordinate
    */
    int xCurr = int(current->getPosition()->x) / TILE_SIZE,
        yCurr = int(current->getPosition()->y) / TILE_SIZE;

    int xGoal = int(goal->getPosition()->x) / TILE_SIZE,
        yGoal = int(goal->getPosition()->y) / TILE_SIZE;

    // Calculate manhattan distance between current and goal
    return abs(xCurr - xGoal) + abs(yCurr - yGoal);
}

/**
 * Finds the path from the start tile to the goal tile on the given map using A*
 * algorithm.
 *
 * @param start The starting tile.
 * @param goal The goal tile.
 * @param map The 2D vector representing the map of tiles.
 * @return A map of tiles representing the calculated path.
 */
std::unordered_map<Tile *, Tile *>
findPath(Tile *start, Tile *goal, std::vector<std::vector<Tile>> *map) {

    // Initialize the gScore and fScore maps. Each tile should have an initial
    // cost of infinity
    std::unordered_map<Tile *, int> gScore;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            gScore[&(*map)[i][j]] = INFINITY;
        }
    }
    gScore[start] = 0; // Score of the starting tile is 0

    std::unordered_map<Tile *, int> fScore;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            fScore[&(*map)[i][j]] = INFINITY;
        }
    }
    fScore[start] = heuristic(start, goal);

    // Priority queue sorted by fScore in increasing order. Each element in the
    // queue is a tuple containing the fScore, heuristic, and corresponding Tile
    std::priority_queue<std::tuple<int, int, Tile *>,
                        std::vector<std::tuple<int, int, Tile *>>,
                        std::greater<std::tuple<int, int, Tile *>>>
        open;

    open.push({fScore[start], heuristic(start, goal), start});

    // Map to store the optimal path
    std::unordered_map<Tile *, Tile *> cameFrom;

    // A* algorithm main loop
    while (!open.empty()) {
        Tile *current = std::get<2>(open.top());
        open.pop();

        // Goal reached, exit loop
        if (current == goal) {
            break;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            // Once again, divide by the tile size to go from pixel coordinates
            // to tile coordinates
            int xCurr = int(current->getPosition()->x) / TILE_SIZE,
                yCurr = int(current->getPosition()->y) / TILE_SIZE;

            // Move to an adjacent cell using the direction vectors
            int xNew = xCurr + xDirections[i], yNew = yCurr + yDirections[i];

            Tile *neighbor = nullptr;

            // Check if the neighbor is within bounds and not a wall
            if (xNew >= 0 && xNew < MAP_SIZE && yNew >= 0 && yNew < MAP_SIZE &&
                !(*map)[yNew][xNew].getIsWall()) {
                neighbor = &(*map)[yNew][xNew];
            }

            if (neighbor == nullptr) {
                continue;
            }

            /*
            Calculate gScore and fScore for the neighbor

            The gScore (essentially the distance from the starting
            position) increases by 1 each move. The heuristic is the distance
            from a tile to the goal
            */
            int tentativeGScore = gScore[current] + 1;
            int tentativeFScore = tentativeGScore + heuristic(neighbor, goal);

            // Put neighbour on priority queue if it's gained a better fScore
            if (tentativeFScore < fScore[neighbor]) {
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = tentativeFScore;
                open.push(
                    {fScore[neighbor], heuristic(neighbor, goal), neighbor});
                cameFrom[neighbor] = current;
            }
        }
    }

    // Reconstruct the path from goal to start
    std::unordered_map<Tile *, Tile *> path;
    Tile *current = goal;

    while (current != start) {
        path[cameFrom[current]] = current;
        current = cameFrom[current];
    }

    return path;
}
