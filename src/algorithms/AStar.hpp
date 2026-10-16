#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "IPathfinder.hpp"
#include <queue>
#include <vector>
#include <string>
#include <cmath>

class AStar : public IPathfinder {
public:
    void init(Grid& grid) override;
    bool step() override;
    bool foundPath() const override { return pathFound; }
    std::vector<Cell*> getPath() const override;
    std::string getName() const override { return "A* Search"; }

private:
    Grid* grid = nullptr;
    struct QueueEntry {
        Cell* cell;
        int fCost;
        int hCost;
        int gCost;
        bool operator>(const QueueEntry& other) const {
            if (fCost == other.fCost) {
                return hCost > other.hCost; // Tie-breaking: prefer lower hCost
            }
            return fCost > other.fCost;
        }
    };
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> frontier;
    bool pathFound = false;
    bool finished = false;

    int getHeuristic(Cell* a, Cell* b);
};

#endif // ASTAR_HPP
