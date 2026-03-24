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
    struct CellComparator {
        bool operator()(const Cell* a, const Cell* b) const {
            if (a->fCost() == b->fCost()) {
                return a->hCost > b->hCost; // Tie-breaking: prefer lower hCost
            }
            return a->fCost() > b->fCost(); // Min-heap
        }
    };
    std::priority_queue<Cell*, std::vector<Cell*>, CellComparator> frontier;
    bool pathFound = false;
    bool finished = false;

    int getHeuristic(Cell* a, Cell* b);
};

#endif // ASTAR_HPP
