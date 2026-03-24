#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "IPathfinder.hpp"
#include <queue>
#include <vector>
#include <string>
#include <vector>

class Dijkstra : public IPathfinder {
public:
    void init(Grid& grid) override;
    bool step() override;
    bool foundPath() const override { return pathFound; }
    std::vector<Cell*> getPath() const override;
    std::string getName() const override { return "Dijkstra's Algorithm"; }

private:
    Grid* grid = nullptr;
    struct CellComparator {
        bool operator()(const Cell* a, const Cell* b) const {
            return a->gCost > b->gCost; // Min-heap
        }
    };
    std::priority_queue<Cell*, std::vector<Cell*>, CellComparator> frontier;
    bool pathFound = false;
    bool finished = false;
};

#endif // DIJKSTRA_HPP
